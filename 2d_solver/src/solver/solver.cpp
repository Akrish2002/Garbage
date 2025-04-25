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
                    const double CFL

                ):grid_(gridpath)
{

//-------------------------------------------------------------------------------------------------------------

    //Transport properties and initial conditions
    gamma_  =   gamma;
    Cp_     =   Cp;
    R_      =   R;
    
    P_ = P;
    T_ = T;
    c_ = c;
    M_ = M;
    
    rho_    =   rho;
    u_      =   u;
    v_      =   v;
    et_     =   P_ /(rho * (gamma_ - 1)) + 0.5 * ((u_ * u_ + v_ * v_));
    ht_     =   et_ + P_ / rho_;    

    epsilon_    = epsilon;
    kappa_      = kappa;
    N_          = N;
    CFL_        = CFL;

//-------------------------------------------------------------------------------------------------------------

    grid_.addHaloCells_2D();
    grid_.computeMetrics(2); //Change this to not take in "2" since halocells addition is for 2D
    
    //Getting size of grid, this is not including halocells
    nx_ = grid_.getnx();
    ny_ = grid_.getny();

//-------------------------------------------------------------------------------------------------------------

    //Initialize the sizes of; 

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
    
    for(size_t i = 0; i < ny_ + 1; i++)
    {
        for(size_t j = 0; j < nx_ + 1; j++)
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
    
    std::cout<<"--Applied initial conditions\n";

}


void Solver::applyBCs()
{
    
    //Supersonic Inlet
    for(size_t i = 0; i < ny_ + 1; i++)
    {
        V_[i][0] = V_inf_[i][0];
        Q_[i][0] = convertPrimtoCons(V_inf_[i][0]);
    }
   
    //Supersonic Outlet 
    for(size_t i = 0; i < ny_ + 1; i++)
    {
        V_[i][ny_] = V_inf_[i][ny_ - 1];
        Q_[i][ny_] = convertPrimtoCons(V_inf_[i][ny_ - 1]);
    }

    //Slip Wall + Adiabatic
    for(size_t i = 1; i < nx_; i++) 
    {
        double S_eta_x;
        double S_eta_y;
        double S_eta_x_2;
        double S_eta_y_2;

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

        V_[ny_][i].u = ((S_eta_x_2 - S_eta_y_2) * V_[ny_ - 1][i].u - (2 * S_eta_x * S_eta_y) * V_[ny_ - 1][i].v)
                     / (S_eta_x_2 + S_eta_y_2);

        V_[ny_][i].v = ((-2 * S_eta_x * S_eta_y) * V_[ny_ - 1][i].u + (S_eta_x_2 - S_eta_y_2) * V_[ny_ - 1][i].v)
                     / (S_eta_x_2 + S_eta_y_2);

        V_[ny_][i].T = V_[ny_ - 1][i].T;
                     
        Q_[ny_][i] = convertPrimtoCons(V_[ny_ - 1][i]); 

    } 
    
    
}

void Solver::computeFlux()
{

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


}

double Solver::computedt()
{

    return dt_ = 1e-8;

}

void Solver::integratethroughTime()
{
    double S_xi_L, S_xi_R;
    double S_eta_L, S_eta_R;
    double S_vol;

    for(size_t i = 1; i < ny_; i++)
    {
        for(size_t j = 1; j < nx_; j++)
        {
            Vec4 Q, Q1;
            Vec4 E_L, E_R;
            Vec4 F_L, F_R;

            S_vol   = grid_.getVol(i, j);
            S_xi_L  = grid_.getareaXi( i - 1, j - 1);
            S_xi_R  = grid_.getareaXi( i - 1,   j  );
            S_eta_L = grid_.getareaEta(i - 1, j - 1);
            S_eta_R = grid_.getareaEta(  i  , j - 1);

            E_L = convertfluxVartoVec(E_[i][  j  ] * S_xi_L);
            E_R = convertfluxVartoVec(E_[i][j + 1] * S_xi_R);

            F_L = convertfluxVartoVec(F_[  i  ][  j  ] * S_eta_L);
            F_R = convertfluxVartoVec(F_[i + 1][  j  ] * S_eta_R);

            Q = convertconsVartoVec(Q_[i][j]);
            
            Q1 = Q - dt_ * ((E_R - E_L) + (F_R - F_L)) / S_vol; 

            Q_[i][j] = convertVectoconsVar(Q1);

            //Q1[i][j] = Q_[i][j] 

        }
    }

}

//-----------------------------------------------------------
//1. Read grid
//   Construct halo cells
//   Compute metrics
//   Initialize field and BCs
void Solver::setup()
{

    applyICs();
    applyBCs();

}


void Solver::run(int iter)
{

    for(int i = 1; i < iter; i++)
    {
        //1. Interpolate flux values from center to face
        //Not including limiter, since default is minmod

        std::cout<<"--Starting MUSCL interpolation \n";
        performMUSCL
        (
            nx_, ny_,
            epsilon_, kappa_,

            Q_,
            Q_xi_L,  Q_xi_R,
            Q_eta_L, Q_eta_R
        );
        

        //2.
        
        //2.1 
        //Function that calls computeXiFlux and computeEtaFlux twice each to compute flux on each 
        //side in each direction
        std::cout<<"--Computing flux on all faces from interpolated Q \n";
        computeFlux();
       
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
        
        
        //3.
        std::cout<<"--Integrating through time \n";
        integratethroughTime();

        
        //4.
        std::cout<<"--Reapplying BCs \n";
        applyBCs();
        
        std::cout<<"--Iter: "<<i<<"\n\n";
        if(i == 20)
            std::exit(0);
    }

}


