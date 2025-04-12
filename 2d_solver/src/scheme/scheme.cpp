#include "scheme.h"

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <array>

#include "allocate.h"
#include "debug.h"
#include "stateVar.h"
#include "fluxlimiter.cpp"

void performMUSCL(
    
    int nx, int ny,
    double epsilon, double kappa,
    std::vector<std::vector<stateVar>>& Q,
    std::vector<std::vector<stateVar>>& Q_xi_L, std::vector<std::vector<stateVar>>& Q_xi_R,
    std::vector<std::vector<stateVar>>& Q_eta_L, std::vector<std::vector<stateVar>>& Q_eta_R

)
{
    //Memory allocation
    allocate(ny + 1, nx + 1, Q); //Including Halo cells

    allocate(ny + 1, nx + 1, Q_xi_L);
    allocate(ny + 1, nx + 1, Q_xi_R);

    allocate(ny + 1, nx + 1, Q_eta_L);
    allocate(ny + 1, nx + 1, Q_eta_R);

    std::vector<std::vector<stateVar>> r_R, r_L;
    

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
            r_L = (Q[i][j] - Q[i][j - 1]) / (Q[i][j - 1] - Q[i][j - 2]); 
            r_R = (Q[i][j] - Q[i][j - 1]) / (Q[i][j + 1] - Q[i][  j  ]); 


            // U(^L)_(i+1/2) = U_i   + ε/4 * (U_i   - U_i-1) * [(1 - k) * Φ(r_L) + (1 + k) * r_L * Φ(1/r_L)]
            // U(^R)_(i+1/2) = U_i+1 + ε/4 * (U_i+2 - U_i+1) * [(1 - k) * Φ(r_R) + (1 + k) * r_R * Φ(1/r_R)]  
            Q_xi_L[i][j] = Q[i][j - 1]  + 0.25 * epsilon * ( 
                                           (Q[i][j - 1] - Q[i][j - 2]) * (1.0 - kappa) * fluxlimiter(r_L, "minmod") 
                                        +  (Q[i][  j  ] - Q[i][j - 1]) * (1.0 + kappa) * fluxlimiter(1.0/r_L, "minmod")); 
                
            Q_xi_R[i][j] = Q[i][  j  ]  + 0.25 * epsilon * (
                                           (Q[i][j + 1] - Q[i][  j  ]) * (1.0 - kappa) * fluxlimiter(r_R, "minmod") 
                                        +  (Q[i][  j  ] - Q[i][j - 1]) * (1.0 + kappa) * fluxlimiter(1.0/r_L, "minmod")); 
            
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
    }


    //eta direction
    //1. Second order in the interior cells
    for(size_t i = 1; i < nx; i++)
    {
        for(size_t j = 2; j < ny; j++)
        {
            /*Shifted the state vectors by -1 to maintain consistency with grid notation for half indices for faces*/

            // r_L = (U_i+1 - U_i) / (U_i - U_i-1)
            // r_R = (U_i+1 - U_i) / (U_i+2 - U_i+1)
            r_L = (Q[j][i] - Q[j - 1][i]) / (Q[j - 1][i] - Q[j - 2][i]); 
            r_R = (Q[j][i] - Q[j - 1][i]) / (Q[j + 1][i] - Q[  j  ][i]); 


            // U(^L)_(i+1/2) = U_i   + ε/4 * (U_i   - U_i-1) * [(1 - k) * Φ(r_L) + (1 + k) * r_L * Φ(1/r_L)]
            // U(^R)_(i+1/2) = U_i+1 + ε/4 * (U_i+2 - U_i+1) * [(1 - k) * Φ(r_R) + (1 + k) * r_R * Φ(1/r_R)]  
            Q_eta_L[j][i] = Q[j - 1][i]  + 0.25 * epsilon * ( 
                                           (Q[j - 1][i] - Q[j - 2][i]) * (1.0 - kappa) * fluxlimiter(r_L, "minmod") 
                                        +  (Q[  j  ][i] - Q[j - 1][i]) * (1.0 + kappa) * fluxlimiter(1.0/r_L, "minmod")); 
                
            Q_eta_R[j][i] = Q[  j  ][i]  + 0.25 * epsilon * (
                                           (Q[j + 1][i] - Q[  j  ][i]) * (1.0 - kappa) * fluxlimiter(r_R, "minmod") 
                                        +  (Q[  j  ][i] - Q[j - 1][i]) * (1.0 + kappa) * fluxlimiter(1.0/r_L, "minmod")); 
            
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

}

