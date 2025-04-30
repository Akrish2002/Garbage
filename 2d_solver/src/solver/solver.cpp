#include "solver.h"

#include <string>
#include <cmath>
#include <cstddef>
#include <iostream>

#include "read.h"
#include "write.h"

#include "allocate.h"

#include "utils.h"

#include "MUSCL.h"
#include "central.h"
#include "roe.h"

//Constructor
Solver::Solver(
                    const std::string &gridpath, 

                    const double gamma, const double Cp, const double R, 
                    
                    const double P, const double T, const double c, const double M,                    

                    const double rho, const double u, const double v,
                                   
                    const double epsilon, const double kappa,
                    const double N, 
                    const double CFL,
                    const double dt,
                    const std::string t

                ):grid_(gridpath)
{

//-------------------------------------------------------------------------------------------------------------

    //Transport properties and initial conditions
    gamma_  =   gamma;
    Cp_     =   Cp;
    R_      =   R;
    
    P_      =   P;
    T_      =   T;
    c_      =   c;
    M_      =   M;
    
    rho_    =   rho;
    u_      =   u;
    v_      =   v;
    et_     =   P_ /(rho * (gamma_ - 1)) + 0.5 * ((u_ * u_ + v_ * v_));
    ht_     =   et_ + P_ / rho_;    

    epsilon_    = epsilon;
    kappa_      = kappa;
    N_          = N;
    CFL_        = CFL;
    dt_         = dt;
    t_          = t;    

//-------------------------------------------------------------------------------------------------------------

    grid_.addHaloCells_2D();
    grid_.computeMetrics(2); //Change this to not take in "2" since halocells addition is for 2D
    
    //Getting size of grid, this is not including halocells
    nx_ = grid_.getnx();
    ny_ = grid_.getny();

//-------------------------------------------------------------------------------------------------------------

    //Initialize the sizes of; 

    //dtv
    allocate_2D(ny_ + 1, nx_ + 1, dtv_); //For local time step

    //Q
    allocate_2D(ny_ + 1, nx_ + 1, Q_); //Including Halo cells
    allocate_2D(ny_ + 1, nx_ + 1, Q_1); 

    allocate_2D(ny_ + 1, nx_ + 1, Q_xi_L);
    allocate_2D(ny_ + 1, nx_ + 1, Q_xi_R);

    allocate_2D(ny_ + 1, nx_ + 1, Q_eta_L);
    allocate_2D(ny_ + 1, nx_ + 1, Q_eta_R);
   
    //V
    allocate_2D(ny_ + 1, nx_ + 1, V_inf_); 
    allocate_2D(ny_ + 1, nx_ + 1, V_); 

    //E
    allocate_2D(ny_ + 1, nx_ + 1, E_);

    allocate_2D(ny_ + 1, nx_ + 1, E_L);
    allocate_2D(ny_ + 1, nx_ + 1, E_R);
    
    //F
    allocate_2D(ny_ + 1, nx_ + 1, F_);

    allocate_2D(ny_ + 1, nx_ + 1, F_L);
    allocate_2D(ny_ + 1, nx_ + 1, F_R);
    
    std::cout<<"--Allocated memory for Q, V, E and F \n";
}


void Solver::applyICs()
{
    
    bool debug_garbage = false;

    for(int i = 0; i < ny_ + 1; i++)
    {
        for(int j = 0; j < nx_ + 1; j++)
        {
            V_inf_[i][j].rho    =   rho_;
            V_inf_[i][j].u      =   u_;
            V_inf_[i][j].v      =   v_;
            V_inf_[i][j].et     =   et_;
            V_inf_[i][j].ht     =   ht_;
            V_inf_[i][j].P      =   P_;
            V_inf_[i][j].T      =   T_;
            V_inf_[i][j].a      =   c_;

            V_[i][j].rho    =   rho_;
            V_[i][j].u      =   u_;
            V_[i][j].v      =   v_;
            V_[i][j].et     =   et_;
            V_[i][j].ht     =   ht_;
            V_[i][j].P      =   P_;
            V_[i][j].T      =   T_;
            V_[i][j].a      =   c_;

            Q_[i][j].rho     =   rho_;
            Q_[i][j].rho_u   =   rho_ * u_;
            Q_[i][j].rho_v   =   rho_ * v_;
            Q_[i][j].rho_et  =   rho_ * et_;
        }
    }
    
    if(debug_garbage)
    {
        std::cout<<"--Applied initial conditions\n";
    }

}


void Solver::applyBCs()
{
    
    //Supersonic Inlet
    for(int i = 0; i < ny_ + 1; i++)
    {
        V_[i][0] = V_inf_[i][0];
        Q_[i][0] = convertPrimtoCons(V_inf_[i][0]);
    }
   
    //Supersonic Outlet 
    for(int i = 0; i < ny_ + 1; i++)
    {
        V_[i][nx_] = V_inf_[i][nx_ - 1];
        Q_[i][nx_] = convertPrimtoCons(V_inf_[i][nx_ - 1]);
    }

    //Slip Wall + Adiabatic
    for(int i = 1; i < nx_; i++) 
    {
        double S_eta_x;
        double S_eta_y;
        double S_eta_x_2;
        double S_eta_y_2;

        bool debug_garbage = false;

        //Lower
        S_eta_x = grid_.getnxEta(0, i - 1);
        S_eta_y = grid_.getnyEta(0, i - 1);
       
        S_eta_x_2 = S_eta_x * S_eta_x;
        S_eta_y_2 = S_eta_y * S_eta_y;
 
        V_[0][i].u = ((S_eta_x_2 - S_eta_y_2) * V_[1][i].u - (2 * S_eta_x * S_eta_y) * V_[1][i].v)
                     / (S_eta_x_2 + S_eta_y_2);

        V_[0][i].v = ((-2 * S_eta_x * S_eta_y) * V_[1][i].u + (S_eta_x_2 - S_eta_y_2) * V_[1][i].v)
                     / (S_eta_x_2 + S_eta_y_2);

        V_[0][i].T = V_[1][i].T;

        Q_[0][i] = convertPrimtoCons(V_[0][i]); 
        
        //Upper
        S_eta_x = grid_.getnxEta(ny_ - 1, i - 1);
        S_eta_y = grid_.getnyEta(ny_ - 1, i - 1);
       
        S_eta_x_2 = S_eta_x * S_eta_x;
        S_eta_y_2 = S_eta_y * S_eta_y;

        //Debugging 
        if(debug_garbage && i == nx_ - 1)
        {
            std::cout<<"--Upper BCs\n";
            std::cout<<"--S_eta_x[ny - 1, i - 1]: "<<S_eta_x<<std::endl;
            std::cout<<"--S_eta_y[ny - 1, i - 1]: "<<S_eta_y<<std::endl;
            
        }

        V_[ny_][i].u = ((S_eta_x_2 - S_eta_y_2) * V_[ny_ - 1][i].u - (2 * S_eta_x * S_eta_y) * V_[ny_ - 1][i].v)
                     / (S_eta_x_2 + S_eta_y_2);

        V_[ny_][i].v = ((-2 * S_eta_x * S_eta_y) * V_[ny_ - 1][i].u + (S_eta_x_2 - S_eta_y_2) * V_[ny_ - 1][i].v)
                     / (S_eta_x_2 + S_eta_y_2);

        V_[ny_][i].T = V_[ny_ - 1][i].T;
                     
        //Debugging 
        if(debug_garbage && i == nx_ - 1)
        {
            std::cout<<"--V_[ny_ - 1][i].u: "<<V_[ny_ - 1][i].u<<std::endl;
            std::cout<<"--V_[ny_ - 1][i].v: "<<V_[ny_ - 1][i].v<<std::endl;

            std::cout<<"--V_[ny_ - 1][i].T: "<<V_[ny_ - 1][i].T<<std::endl;
            
            exit(0);
        }

        Q_[ny_][i] = convertPrimtoCons(V_[ny_ - 1][i]); 

    } 
    
    
}

void Solver::computeFlux()
{
        bool debug_garbage = false;

         computeXiFlux
         (
            grid_,

            E_L,
            Q_xi_L,

            nx_,
            ny_,
            
            gamma_
         );  

         computeXiFlux
         (

            grid_,

            E_R,
            Q_xi_R,

            nx_,
            ny_,
            
            gamma_
          ); 

         computeEtaFlux
         (
            grid_,

            F_L,
            Q_eta_L,

            nx_,
            ny_,
            
            gamma_
         ); 

         computeEtaFlux
         (
            grid_,

            F_R,
            Q_eta_R,

            nx_,
            ny_,
            
            gamma_
         ); 

        if(debug_garbage)
        {   
            std::cout<<"--E_R[10][nx_ - 1].rho_u_flux: "<<E_R[10][nx_ - 1].rho_u_flux<<std::endl;
            std::cout<<"--E_R[10][nx_ - 1].rho_u_flux: "<<E_R[10][nx_ - 1].rho_u_flux<<std::endl;
            std::cout<<"--E_L[10][nx_].rho_u_flux: "<<E_L[10][nx_].rho_u_flux<<std::endl;
            std::cout<<"--E_L[10][nx_].rho_u_flux: "<<E_L[10][nx_].rho_u_flux<<std::endl;

            std::cout<<"--F_R[10][nx_ - 1].rho_u_flux: "<<F_R[10][nx_ - 1].rho_u_flux<<std::endl;
            std::cout<<"--F_R[10][nx_ - 1].rho_u_flux: "<<F_R[10][nx_ - 1].rho_u_flux<<std::endl;
            std::cout<<"--F_L[10][nx_].rho_u_flux: "<<F_L[10][nx_].rho_u_flux<<std::endl;
            std::cout<<"--F_L[10][nx_].rho_u_flux: "<<F_L[10][nx_].rho_u_flux<<std::endl;
        }
}

void Solver::computedt()
{

    bool debug_garbage_x = true;

    if(t_ == "LOCAL")
    {
        for(int i = 0; i < ny_ - 1; i++)
        {
            for(int j = 0; j < nx_ - 1; j++)
            {
                double rho_xi;       
                double c;
                
                //S_xi_x --> S_xi_x / | S_xi |  
                //S_xi_y --> S_xi_y / | S_xi |  
                double S_xi_x = 0.5 * (grid_.getnxXi(i, j) * grid_.getareaXi(i, j) + grid_.getnxXi(i, j + 1) 
                                                                                 * grid_.getareaXi(i, j + 1));
                double S_xi_y = 0.5 * (grid_.getnyXi(i, j) * grid_.getareaXi(i, j) + grid_.getnyXi(i, j + 1)  
                                                                                 * grid_.getareaXi(i, j + 1));
                double S_xi   = std::sqrt(S_xi_x * S_xi_x + S_xi_y * S_xi_y);
                c = std::sqrt(gamma_ * R_ * V_[i + 1][j + 1].T);

                rho_xi = std::fabs((S_xi_x * V_[i + 1][j + 1].u) / S_xi + (S_xi_y * V_[i + 1][j + 1].v) / S_xi) + c;

                dtv_[i + 1][j + 1].x = (CFL_ * grid_.getVol(i + 1, j + 1)) / (rho_xi * S_xi);
                    
                if(debug_garbage_x && i == ny_ - 2 && j == nx_ - 2)
                {
                    std::cout<<"--dtv_[ny_ - 2].x: "<<dtv_[i][j].x<<std::endl;
                }
                
             }
        }
                
        bool debug_garbage_y = false;           

        for(int i = 0; i < nx_ - 1; i++)
        {
            for(int j = 0; j < ny_ - 1; j++)
            {
                 
                double rho_eta;       
                double c;

                double S_eta_x = 0.5 * (grid_.getnxEta(j, i) * grid_.getareaEta(j, i) + grid_.getnxEta(j + 1, i) 
                                                                                    * grid_.getareaEta(j + 1, i));
                double S_eta_y = 0.5 * (grid_.getnyEta(j, i) * grid_.getareaEta(j, i) + grid_.getnyEta(j + 1, i) 
                                                                                    * grid_.getareaEta(j + 1, i));
                double S_eta   = std::sqrt(S_eta_x * S_eta_x + S_eta_y * S_eta_y);
                c = std::sqrt(gamma_ * R_ * V_[j + 1][i + 1].T);

                rho_eta = std::fabs((S_eta_x * V_[j + 1][i + 1].u) / S_eta + (S_eta_y * V_[j + 1][i + 1].v) / S_eta) + c;

                dtv_[j + 1][i + 1].y = (CFL_ * grid_.getVol(j + 1, i + 1)) / (rho_eta * S_eta);

                if(debug_garbage_y && i == nx_ - 2) 
                {
                    std::cout<<"dtv_.y: "<<dtv_[j][i].y<<std::endl;
                }
            }
        }
    }

    else if(t_ == "GLOBAL")
    {
        std::cout<<"--Integrating through time globally \n";
    }
    
}


void Solver::integratethroughTime()
{
    double S_xi_L, S_xi_R;
    double S_eta_L, S_eta_R;
    double S_vol;

    bool debug_garbage = false;

    for(int i = 1; i < ny_; i++)
    {
        for(int j = 1; j < nx_; j++)
        {
            Vec4 Q, Q1;
            Vec4 E_L, E_R;
            Vec4 F_L, F_R;

            S_vol   = grid_.getVol(i, j);
            S_xi_L  = grid_.getareaXi( i - 1, j - 1);
            S_xi_R  = grid_.getareaXi( i - 1,   j  );
            S_eta_L = grid_.getareaEta(i - 1, j - 1);
            S_eta_R = grid_.getareaEta(  i  , j - 1);

            //Debugging
            if (debug_garbage) 
            {
                if(i == 10 && j == 10)
                {
                    std::cout<<"--S_vol: "<<S_vol<<std::endl;
                    std::cout<<"--S_xi_L: "<<S_xi_L<<std::endl;
                    std::cout<<"--S_xi_R: "<<S_xi_R<<std::endl;
                    std::cout<<"--S_eta_L: "<<S_eta_L<<std::endl;
                    std::cout<<"--S_eta_R: "<<S_eta_R<<std::endl;
                    
                }
            }

            E_L = convertfluxVartoVec(E_[i][  j  ]); //* S_xi_L);
            E_R = convertfluxVartoVec(E_[i][j + 1]); // * S_xi_R);

            F_L = convertfluxVartoVec(F_[  i  ][  j  ]); //* S_eta_L);
            F_R = convertfluxVartoVec(F_[i + 1][  j  ]); //* S_eta_R);

            Q = convertconsVartoVec(Q_[i][j]);
            
            //Debugging
            if (debug_garbage) {
                if(i == 10 && j == 10)
                {
                    std::cout<<"--E_L[10][10].rho_u_flux bfr update: "<<E_L(1)<<std::endl;
                    std::cout<<"--E_R[10][10].rho_u_flux bfr update: "<<E_R(1)<<std::endl;

                    std::cout<<"--F_L[10][10].rho_u_flux bfr update: "<<F_L(1)<<std::endl;
                    std::cout<<"--F_R[10][10].rho_u_flux bfr update: "<<F_R(1)<<std::endl;

                    std::cout<<"--Q_[10][10].rho_u bfr update: "<<Q(1)<<std::endl;
                }
            }

            if(t_ == "LOCAL")
            {
                double dtv = std::fmin(dtv_[i][j].x, dtv_[i][j].y);
                Q1 = Q - dtv * ((E_R*S_xi_R - E_L*S_xi_L) + (F_R*S_eta_R - F_L*S_eta_L)) / S_vol; 
            }

            else if(t_ == "GLOBAL")
            {
                Q1 = Q - dt_ * ((E_R*S_xi_R - E_L*S_xi_L) + (F_R*S_eta_R - F_L*S_eta_L)) / S_vol; 
            }

            //Debugging
            if (debug_garbage) {
                if(i == 10 && j == 10)
                {
                    std::cout<<"--asdf: \n"<<E_R*S_xi_R<<std::endl;
                }
            }

            //Debugging
            if (debug_garbage) 
            {
                if(i == 10 && j == 10)
                {
                    std::cout<<"--Q_[10][10].rho_u after update: "<<Q1(1)<<std::endl;
                    
                    //exit(0);
                }
            }

            // Compute residual here:

            // Update next iteration
            Q_[i][j] = convertVectoconsVar(Q1);
            V_[i][j] = convertConstoPrim(Q_[i][j], gamma_);
            
            //Debugging
            if (debug_garbage) 
            {
                if(i == 10 && j == 10)
                {
                    std::cout<<"--Q_[10][10].rho_u: "<<Q_[i][j].rho_u<<std::endl;
                    std::cout<<"--V_[10][10].u: "<<V_[i][j].u<<std::endl;

                    //exit(0);
                }
            }


        }
    }

}

//-----------------------------------------------------------
//0. 
//Read grid
//Construct halo cells
//Compute metrics
//Initialize field and BCs
void Solver::setup()
{

    bool debug_garbage = false;

    applyICs();
    std::cout<<"--Applied initial conditions\n";

    applyBCs();
    std::cout<<"--Applied boundary conditions\n\n";

    if(debug_garbage)
    {

        std::cout<<"--V_.u: "<<V_[10][10].u<<std::endl;
        std::cout<<"--Q_.u: "<<Q_[10][10].rho_u<<std::endl<<std::endl;

        exportprimitiveVartoCSV(V_, "primitiveVar.csv", nx_, ny_, 1);
        exit(0);
    }

}


void Solver::run(int iter, const std::string& file_name)
{
    
    bool debug_garbage = true;
    int  print_iter = N_;

    for(int i = 1; i < iter; i++)
    {
    
        std::cout<<"--Iter: "<<i<<"\n";

        //1. 
        //Interpolate flux values from center to face
        //Not including limiter, since default is minmod

        std::cout<<"////////////////////////////////////\n";

        std::cout<<"--Starting MUSCL interpolation \n";
        performMUSCL
        (
            nx_, ny_,
            epsilon_, kappa_,

            Q_,
            Q_xi_L,  Q_xi_R,
            Q_eta_L, Q_eta_R
        );
        

        std::cout<<"-----------------------------------------------------\n";

        //2.
        
        //2.1 
        //Function that calls computeXiFlux and computeEtaFlux twice each to compute flux on each 
        //side in each direction
        std::cout<<"--Computing flux on all faces from interpolated Q \n";
        computeFlux();
       
        std::cout<<"-----------------------------------------------------\n";

        //2.2 
        //Perform Roe
        std::cout<<"--Perfoming roe flux reconstruction \n";
        performRoe
        (
            grid_,
        
            Q_xi_L, Q_xi_R,
            Q_eta_L, Q_eta_R,
            
            E_, 
            E_L, E_R,
                        
            F_, 
            F_L, F_R,

            gamma_
        );
        
        std::cout<<"-----------------------------------------------------\n";
        
        //3.
        //3.0
        if(t_ == "LOCAL")
        {
            std::cout<<"--Computing local time step \n";
            computedt();

            std::cout<<"-----------------------------------------------------\n";

            std::cout<<"--Integrating through time locally \n";
            
        }
       
        else
        {
            computedt();
            //Returns print statement
        } 

        //3.1
        integratethroughTime();

        std::cout<<"-----------------------------------------------------\n";
        
        //4.
        std::cout<<"--Reapplying BCs \n";
        applyBCs();
        
        std::cout<<"-----------------------------------------------------\n";

        std::cout<<"--V[0][nx - 1].u: "<<V_[0][nx_ - 1].u<<std::endl;
        std::cout<<"--V[0][nx].u: "<<V_[0][nx_].u<<std::endl;

        std::cout<<"-----------------------------------------------------\n";

        if(i % 25 == 0 || i == 1)
        {
            std::string file_name_iteration = file_name + "_" + std::to_string(i) + ".csv";
            exportprimitiveVartoCSV(V_, file_name_iteration, nx_, ny_, 1);


            if(i == print_iter && debug_garbage) 
            {
                std::exit(0);
            }
        }

        std::cout<<std::endl;        

    }

}


