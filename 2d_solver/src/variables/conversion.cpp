#include "conversion.h"

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
