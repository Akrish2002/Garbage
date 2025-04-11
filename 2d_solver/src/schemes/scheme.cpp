#include "scheme.h"

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <array>

#include "allocate.h"
#include "debug.h"
#include "stateVar.h"

void performMUSCL(
    
    int nx, int ny,
    double epsilon, double kappa,
    std::vector<std::vector<stateVar>>& Q,
    std::vector<std::vector<stateVar>>& Q_xi_L, std::vector<std::vector<stateVar>>& Q_xi_R,
    std::vector<std::vector<stateVar>>& Q_eta_L, std::vector<std::vector<stateVar>>& Q_eta_R

)
{
    //Memory allocation
    allocate(ny - 1, nx - 1, Q);

    allocate(ny - 1, nx, Q_xi_L);
    allocate(ny - 1, nx, Q_xi_R);

    allocate(ny, nx - 1, Q_eta_L);
    allocate(ny, nx - 1, Q_eta_R);

    std::vector<std::vector<stateVar>> r_R, r_L;

    //xi direction
    //1. First order in the interior cells, since looping from 1 to nx - 1 in xi direction
    for(size_t i = 0; i < Q[0].size(); i++)
    {
        for(size_t j = 1; j < Q.size() - 1; j++)
        {
            r_R = (Q[i][j + 1] - Q[i][j]) / (Q[i][j + 2] - Q[i][j + 1]); 
            r_L = (Q[i][j + 1] - Q[i][j]) / (Q[i][j] - Q[i][j - 1]); 

            Q_xi_L = Q[i][j] + 0.25 * epsilon * (Q[i][j] - Q[i][j - 1]) 
                     * ((1 - kappa) * fluxlimiter(r_L) + (1 + kappa) * r_L * fluxlimiter(1/r_L)); 
                
            Q_xi_R = Q[i][j] + 0.25 * epsilon * (Q[i][j] - Q[i][j - 1]) 
                     * ((1 - kappa) * fluxlimiter(r_L) + (1 + kappa) * r_L * fluxlimiter(1/r_L));

        }
    }
                 


}
