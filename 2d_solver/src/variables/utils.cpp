#include "utils.h"

#include <cmath>

primitiveVar convertConstoPrim
(
    consVar& Q,
    const double gamma
)
{
    primitiveVar V;

    V.rho = Q.rho;

    //Velocities
    V.u = Q.rho_u / Q.rho;         
    V.v = Q.rho_v / Q.rho;         

    //Pressure
    V.P = (gamma - 1) * (Q.rho_et - 0.5 * ((Q.rho_u * Q.rho_u + Q.rho_v * Q.rho_v)/Q.rho));
    
    //Energy
    V.et = Q.rho_et/Q.rho;
    V.ht = V.et + V.P/V.rho;      
   
    return V; 

}


fluxVar computeFlux
(
    const primitiveVar &V,
    double S_x,
    double S_y,
    double S_mag,
    double gamma
)
{

    double U_ = (S_x * V.u + S_y * V.v) / S_mag;

    fluxVar f;
    f.rho_flux      = V.rho * U_;
    f.rho_u_flux    = V.rho * V.u  * U_ + (S_x / S_mag) * V.P;
    f.rho_v_flux    = V.rho * V.v  * U_ + (S_y / S_mag) * V.P;
    f.rho_ht_flux   = V.rho * V.ht * U_;
        
}    








