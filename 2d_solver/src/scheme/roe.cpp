#include "roe.h"

#include <cmath>
#include <vector>
#include <iostream>

#include "consVar.h"
#include "primitiveVar.h"
#include "utils.h"

primitiveVar computeRoeAverage
(
    const primitiveVar& V_L, const primitiveVar& V_R,
    const double& gamma
)
{
    primitiveVar V_avg;
    
    double rho_L, rho_R;
    rho_L = std::sqrt(V_L.rho);
    rho_R = std::sqrt(V_R.rho);

    V_avg.rho = std::sqrt(V_L.rho * V_R.rho);
    V_avg.u   = (rho_L * V_L.u  + rho_R * V_R.u)  / (rho_L + rho_R);
    V_avg.v   = (rho_L * V_L.v  + rho_R * V_R.v)  / (rho_L + rho_R);
    V_avg.ht  = (rho_L * V_L.ht + rho_R * V_R.ht) / (rho_L + rho_R);
    V_avg.a   = (gamma - 1) * (V_avg.ht - 0.5 * (V_avg.u * V_avg.u + V_avg.v * V_avg.v));
    
    return V_avg;
}

RlamdaRinv buildRlamdaRinv
(
    const primitiveVar& V_avg,
    const double S_area,
    const double S_nx,
    const double S_ny
)
{
    RlamdaRinv RlRinv;

    double u    = V_avg.u;  
    double v    = V_avg.v;
    double ht   = V_avg.ht;
    double a    = V_avg.a;

    // 2. Building R column by column
    RlRinv.R<<
                1,                          1,                  1,                           0,
                u - a * S_nx,               u,                  u + a * S_nx,                S_ny,
                v - a * S_ny,               v,                  v + a * S_ny,                -1 * S_nx,
               ht - a * (u*S_nx + v*S_ny),  0.5 * (u*u + v*v),  ht + a * (u*S_nx + v*S_ny),  u*S_ny - v*S_nx;

    // 3. Building lamda
    double un = u*S_nx + v*S_ny;

    RlRinv.lamda = Eigen::Matrix4d::Zero();
    //Filling the diagonals
    RlRinv.lamda(0,0) = std::abs(un - a);
    RlRinv.lamda(1,1) = std::abs(  un  );
    RlRinv.lamda(2,2) = std::abs(un + a);
    RlRinv.lamda(3,3) = std::abs(  un  );
 
    // 4. The inverse of R
    RlRinv.Rinv = RlRinv.R.inverse();

    return RlRinv;

} 

void performRoe
(
    Grid& grid_,

    std::vector<std::vector<consVar>>& Q_xi_L,  std::vector<std::vector<consVar>>& Q_xi_R,
    std::vector<std::vector<consVar>>& Q_eta_L, std::vector<std::vector<consVar>>& Q_eta_R,

    std::vector<std::vector<fluxVar>>& E_,
    std::vector<std::vector<fluxVar>>& E_L,
    std::vector<std::vector<fluxVar>>& E_R,

    std::vector<std::vector<fluxVar>>& F_,
    std::vector<std::vector<fluxVar>>& F_L,
    std::vector<std::vector<fluxVar>>& F_R,

    const double& gamma
)
{
    int nx = grid_.getnx();
    int ny = grid_.getny();
   
    bool debug_garbage = false;
    
    //Running the loop to perform flux reconstruction at the faces
    
    //xi direction
    for(int i = 1; i < ny; i++)
    {
        for(int j = 1; j < nx + 1; j++)
        {

            double S_xi_nx; 
            double S_xi_ny; 
            double S_xi_area; 

            RlamdaRinv RlRinv;

            S_xi_nx     = grid_.getnxXi(i - 1, j - 1);
            S_xi_ny     = grid_.getnyXi(i - 1, j - 1);
            S_xi_area   = grid_.getareaXi(i - 1, j - 1);

            //xi                 
            primitiveVar V_xi_L = convertConstoPrim(Q_xi_L[i][j], gamma);
            primitiveVar V_xi_R = convertConstoPrim(Q_xi_R[i][j], gamma);
             
            //xi
            primitiveVar V_xi_avg = computeRoeAverage(V_xi_L, V_xi_R, gamma);
           
            //1. Computing R * lamda * Rinv * ΔQ 
            //1.1
            RlRinv = buildRlamdaRinv    (
                                            V_xi_avg,

                                            S_xi_nx,
                                            S_xi_ny,
                                            S_xi_area
                                        );

            //1.2 Convert Q_L and Q_R to vector form           
            Vec4 qL = convertconsVartoVec(Q_xi_L[i][j]);
            Vec4 qR = convertconsVartoVec(Q_xi_R[i][j]);      
            
            //1.3 Compute the second "dissipiation" term
            Vec4 D = RlRinv.R * RlRinv.lamda * (RlRinv.Rinv * (qR - qL));
            
            //1.4 Converting E_L and E_R to vector form
            Vec4 E_L_vec = convertfluxVartoVec(E_L[i][j]);
            Vec4 E_R_vec = convertfluxVartoVec(E_R[i][j]);


            //2
            //2.1 Assemble the Roe flux in Vec4 form
            Vec4 E_vec = 0.5 * (E_L_vec + E_R_vec) - 0.5 * D;
            
            //2.2 Converting column vector back to struct form
            E_[i][j] = convertVectofluxVar(E_vec);
            
            //Debugging
            if(debug_garbage)
            {
                if(i == 10 && j == 10)
                {

                    std::cout<<"--E_[10][10].rho_u_flux: "<<E_[i][j].rho_u_flux<<std::endl;
                
                }
            }
        
        }
    }

    
    //eta direction
    for(int i = 1; i < nx; i++)
    {
        for(int j = 1; j < ny + 1; j++)
        {

            double S_eta_nx; 
            double S_eta_ny; 
            double S_eta_area; 

            RlamdaRinv RlRinv;

            S_eta_nx     = grid_.getnxEta(j - 1, i - 1);
            S_eta_ny     = grid_.getnyEta(j - 1, i - 1);
            S_eta_area   = grid_.getareaEta(j - 1, i - 1);

            //eta                 
            primitiveVar V_eta_L = convertConstoPrim(Q_eta_L[j][i], gamma);
            primitiveVar V_eta_R = convertConstoPrim(Q_eta_R[j][i], gamma);
             
            //eta
            primitiveVar V_eta_avg = computeRoeAverage(V_eta_L, V_eta_R, gamma);
           
            //1. Computing R * lamda * Rinv * ΔQ 
            //1.1
            RlRinv = buildRlamdaRinv    (
                                            V_eta_avg,

                                            S_eta_nx,
                                            S_eta_ny,
                                            S_eta_area
                                        );

            //1.2 Convert Q_L and Q_R to vector form           
            Vec4 qL = convertconsVartoVec(Q_eta_L[j][i]);
            Vec4 qR = convertconsVartoVec(Q_eta_R[j][i]);      
            
            //1.3 Compute the second "dissipiation" term
            Vec4 D = RlRinv.R * RlRinv.lamda * (RlRinv.Rinv * (qR - qL));
            
            //1.4 Converting F_L and F_R to vector form
            Vec4 F_L_vec = convertfluxVartoVec(F_L[j][i]);
            Vec4 F_R_vec = convertfluxVartoVec(F_R[j][i]);


            //2
            //2.1 Assemble the Roe flux in Vec4 form
            Vec4 F_vec = 0.5 * (F_L_vec + F_R_vec) - 0.5 * D;
            
            //2.2 Converting column vector back to struct form
            F_[j][i] = convertVectofluxVar(F_vec);
        
            //Debugging
            if(debug_garbage)
            {
                if(i == 10 && j == 10)
                {

                    std::cout<<"--F_[10][10].rho_u_flux: "<<F_[i][j].rho_u_flux<<std::endl;
                } 
            }
        }
    }
}
