#include "roe.h"

#include <cmath>
#include <vector>
#include <iostream>

#include "consVar.h"
#include "primitiveVar.h"
#include "conversion.h"


primitiveVar computeRoeAverage
(
    const primitiveVar& V_L, const primitiveVar& V_R,
    const double& gamma
)
{
    primitiveVar V_avg;
    
    //Rho avg
    V_avg.rho = std::sqrt(V_L.rho * V_R.rho);
   
    V_avg.u   = (std::sqrt(V_L.rho) * V_L.u + std::sqrt(V_R.rho) * V_R.u) /
                (std::sqrt(V_L.rho) + std::sqrt(V_R.rho));

    V_avg.h   = (std::sqrt(V_L.rho) * V_L.h + std::sqrt(V_R.rho) * V_R.h) /
                (std::sqrt(V_L.rho) + std::sqrt(V_R.rho));

    V_avg.a   = (gamma - 1) * [V_avg.h - 0.5 * V_avg.u * V_avg

    
    
}


void computeRoeFluxes
(
    std::vector<std::vector<consVar>>& Q_xi_L, std::vector<std::vector<consVar>>& Q_xi_R,
    std::vector<std::vector<consVar>>& Q_eta_L, std::vector<std::vector<consVar>>& Q_eta_R
    const double& gamma
)
{
    //Converting QLs and QRs to primitives
    for(size_t )
    {
        for(size_t)
        {

            //xi direction
            primitiveVar V_xi_L = convertConstoPrim(Q_xi_L[][], gamma);
            primitiveVar V_xi_R = convertConstoPrim(Q_xi_R[][], gamma);
             
            //eta direction
            primitiveVar V_eta_L = convertConstoPrim(Q_eta_L[][], gamma);
            primitiveVar V_eta_R = convertConstoPrim(Q_eta_R[][], gamma);
            
            //Computing roe averages
        
            //xi
            computeRoeAverage(V
            computeRoeAverage(V
        
            //eta
            computeRoeAverage(V
            computeRoeAverage(V
        }
    }

}
