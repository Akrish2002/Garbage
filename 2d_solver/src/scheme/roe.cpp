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
    
    double rho_L, rho_R;
    rho_L = std::sqrt(V_L.rho);
    rho_R = std::sqrt(V_R.rho);

    V_avg.rho = std::sqrt(V_L.rho * V_R.rho);
   
    V_avg.u   = (rho_L * V_L.u + rho_R * V_R.u) / (rho_L + rho_R);

    V_avg.v   = (rho_L * V_L.v + rho_R * V_R.v) / (rho_L + rho_R);

    V_avg.h   = (rho_L * V_L.h + rho_R * V_R.h) /(rho_L + rho_R);

    V_avg.a   = (gamma - 1) * (V_avg.h - 0.5 * (V_avg.u * V_avg.u + V_avg.v * V_avg.v))
    
    return V_avg;
}

RlamdaRinv buildRlamdaRinv(const primitiveVar& V_avg)
{
    RlamdaRinv RlRinv;

    double u    = V_avg.u;  
    double v    = V_avg.v;
    double ht   = V_avg.ht;
    double a    = V_avg.a;

    double nx  
    double nx  



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
        
            //eta
            computeRoeAverage(V
        }
    }

}
