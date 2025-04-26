#include "MUSCL.h"

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <array>
#include <iostream>

#include "allocate.h"
#include "debug.h"
#include "consVar.h"
#include "fluxlimiter.h"

void performMUSCL(
    
    int nx, int ny,

    double epsilon, double kappa,

    std::vector<std::vector<consVar>>& Q,
    std::vector<std::vector<consVar>>& Q_xi_L, std::vector<std::vector<consVar>>& Q_xi_R,
    std::vector<std::vector<consVar>>& Q_eta_L, std::vector<std::vector<consVar>>& Q_eta_R,

    const std::string& FL

)
{

    //xi direction
    //1. Second order in the interior cells
    for(size_t i = 1; i < ny; i++)
    {
        //Reasoning for nx - 1 in README, point 3
        for(size_t j = 2; j < nx; j++)
        {
            /*Shifted the state vectors by -1 to maintain consistency with grid notation for half indices for faces*/

            // r_L = (U_i+1 - U_i) / (U_i - U_i-1)
            // r_R = (U_i+1 - U_i) / (U_i+2 - U_i+1)
            consVar r_L = (Q[i][j] - Q[i][j - 1]) / (Q[i][j - 1] - Q[i][j - 2]); 
            consVar r_R = (Q[i][j] - Q[i][j - 1]) / (Q[i][j + 1] - Q[i][  j  ]); 


            // U(^L)_(i+1/2) = U_i   + ε/4 * (U_i   - U_i-1) * [(1 - k) * Φ(r_L) + (1 + k) * r_L * Φ(1/r_L)]
            // U(^R)_(i+1/2) = U_i+1 + ε/4 * (U_i+2 - U_i+1) * [(1 - k) * Φ(r_R) + (1 + k) * r_R * Φ(1/r_R)]  
            Q_xi_L[i][j] = Q[i][j - 1]  + 0.25 * epsilon * ( 
                                           (Q[i][j - 1] - Q[i][j - 2]) * (1.0 - kappa) * fluxlimiter(r_L, FL) 
                                        +  (Q[i][  j  ] - Q[i][j - 1]) * (1.0 + kappa) * fluxlimiter(1.0/r_L, FL)); 
            Q_xi_L[i][j] = Q[i][j - 1];

            Q_xi_R[i][j] = Q[i][  j  ]  + 0.25 * epsilon * (
                                           (Q[i][j + 1] - Q[i][  j  ]) * (1.0 - kappa) * fluxlimiter(r_R, FL) 
                                        +  (Q[i][  j  ] - Q[i][j - 1]) * (1.0 + kappa) * fluxlimiter(1.0/r_L, FL)); 
            Q_xi_R[i][j] = Q[i][  j  ];
        }
    }
    
    
    //2. For the boundary faces
    for(size_t i = 1; i < ny; i++)
    {
        //West Boundary
        Q_xi_L[i][1] = 0.5*(Q[i][0] + Q[i][1]);
        Q_xi_R[i][1] = 0.5*(Q[i][0] + Q[i][1]);
                
        //East Boundary
        Q_xi_L[i][nx] = 0.5*(Q[i][nx - 1] + Q[i][nx]);
        Q_xi_R[i][nx] = 0.5*(Q[i][nx - 1] + Q[i][nx]);

        //Q_xi_R[i][nx].rho_u = 0.5*(Q[i][nx - 2].rho_u + Q[i][nx - 1].rho_u);
    }

    std::cout<<"--Q[10][nx].rho_u: "<<Q[10][nx].rho_u<<std::endl;
    std::cout<<"--Q_xi_L[10][nx].rho_u: "<<Q_xi_L[10][nx].rho_u<<std::endl;
    std::cout<<"--Q_xi_R[10][nx].rho_u: "<<Q_xi_R[10][nx].rho_u<<std::endl;

    //eta direction
    //1. Second order in the interior cells
    for(size_t i = 1; i < nx; i++)
    {
        for(size_t j = 2; j < ny; j++)
        {
            /*Shifted the state vectors by -1 to maintain consistency with grid notation for half indices for faces*/

            // r_L = (U_i+1 - U_i) / (U_i - U_i-1)
            // r_R = (U_i+1 - U_i) / (U_i+2 - U_i+1)
            consVar r_L = (Q[j][i] - Q[j - 1][i]) / (Q[j - 1][i] - Q[j - 2][i]); 
            consVar r_R = (Q[j][i] - Q[j - 1][i]) / (Q[j + 1][i] - Q[  j  ][i]); 


            // U(^L)_(i+1/2) = U_i   + ε/4 * (U_i   - U_i-1) * [(1 - k) * Φ(r_L) + (1 + k) * r_L * Φ(1/r_L)]
            // U(^R)_(i+1/2) = U_i+1 + ε/4 * (U_i+2 - U_i+1) * [(1 - k) * Φ(r_R) + (1 + k) * r_R * Φ(1/r_R)]  
            Q_eta_L[j][i] = Q[j - 1][i]  + 0.25 * epsilon * ( 
                                           (Q[j - 1][i] - Q[j - 2][i]) * (1.0 - kappa) * fluxlimiter(r_L, FL) 
                                        +  (Q[  j  ][i] - Q[j - 1][i]) * (1.0 + kappa) * fluxlimiter(1.0/r_L, FL)); 
                
            Q_eta_L[j][i] = Q[j - 1][i];

            Q_eta_R[j][i] = Q[  j  ][i]  + 0.25 * epsilon * (
                                           (Q[j + 1][i] - Q[  j  ][i]) * (1.0 - kappa) * fluxlimiter(r_R, FL) 
                                        +  (Q[  j  ][i] - Q[j - 1][i]) * (1.0 + kappa) * fluxlimiter(1.0/r_L, FL)); 
            
            Q_eta_R[j][i] = Q[j][i];
        }
    }

    //2. For the boundary faces
    for(size_t i = 1; i < nx; i++)
    {
        //South Boundary
        Q_eta_L[1][i] = 0.5*(Q[0][i] + Q[1][i]);
        Q_eta_R[1][i] = 0.5*(Q[0][i] + Q[1][i]);
                
        //North Boundary
        Q_eta_L[ny][i] = 0.5*(Q[ny - 1][i] + Q[ny][i]);
        Q_eta_R[ny][i] = 0.5*(Q[ny - 1][i] + Q[ny][i]);
    }

    std::cout<<"--Q_eta_L[10][nx].rho_u: "<<Q_eta_L[10][nx].rho_u<<std::endl;
    std::cout<<"--Q_eta_R[10][nx].rho_u: "<<Q_eta_R[10][nx].rho_u<<std::endl;
}

