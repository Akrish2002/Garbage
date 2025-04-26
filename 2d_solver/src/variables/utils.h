#ifndef CFD_SCHEMES_CONVERSION_H
#define CFD_SCHEMES_CONVERSION_H

#include "consVar.h"
#include "primitiveVar.h"
#include "fluxVar.h"
#include "grid.h"

#include <Eigen/Dense>
using Vec4 = Eigen::Matrix<double,4,1>;

/* Parameters required
 * -------------------
 *
 *  consVar& Q       : Conservative variable Q is passed by reference
 *  double gamma     : Specific heat
 *
 *  Function converts conservative variables to primitive variables using definitions provided in the lecture notes
 */
primitiveVar convertConstoPrim
(
    const consVar& Q,
    const double gamma

);


/* Parameters required
 * -------------------
 *
 *  primitiveVar& V     : Primitive variable V is passed by reference
 *  double gamma        : Specific heat
 *
 *  Function converts primitive variables to conservative variables using definitions provided in the lecture notes
 */
consVar convertPrimtoCons
(
    const primitiveVar& V
);


/* Parameters required
 * -------------------
 *  
 *  consVar Q   : Conservative variable structure 
 *
 *  This function converts the struct consVar to a vector for matrix operations
 */
inline Vec4 convertconsVartoVec(const consVar& Q)
{
    Vec4 q;
    q << Q.rho,
         Q.rho_u,
         Q.rho_v,
         Q.rho_et;

    return q;

}


/* Parameters required
 * -------------------
 *  
 *  fluxVar F   : Flux variable structure 
 *
 *  This function converts the struct fluxVar to a vector for matrix operations
 */
inline Vec4 convertfluxVartoVec(const fluxVar& F)
{
    Vec4 f;
    f << F.rho_flux,
         F.rho_u_flux,
         F.rho_v_flux,
         F.rho_ht_flux;

    return f;

}


/* Parameters required
 * -------------------
 *  
 *  Vec4   : Column vector of size 4x1 (Check inline defn below)
 *
 *  This function converts the column conservative vector to the struct consVar
 */
inline consVar convertVectoconsVar(const Vec4 &v) 
{
    consVar Q;

    Q.rho           = v(0);
    Q.rho_u         = v(1);
    Q.rho_v         = v(2);
    Q.rho_et        = v(3);

    return Q;
}


/* Parameters required
 * -------------------
 *  
 *  Vec4   : Column vector of size 4x1 (Check inline defn below)
 *
 *  This function converts the column flux vector to the struct fluxVar
 */
inline fluxVar convertVectofluxVar(const Vec4 &v) 
{
    fluxVar F;

    F.rho_flux      = v(0);
    F.rho_u_flux    = v(1);
    F.rho_v_flux    = v(2);
    F.rho_ht_flux   = v(3);

    return F;
}


/* Parameters Required:
 * -------------------
 *
 * This computes the Left and Right directional based fluxes for the entire grid and returns the value
 */
void computeXiFlux
(
    Grid& grid_,

    std::vector<std::vector<fluxVar>>& E_LorR,
    const std::vector<std::vector<consVar>>& Q_xi,
    
    int nx,
    int ny,
    double gamma,

    bool debug_garbage = false
);


void computeEtaFlux
(
    Grid& grid_,

    std::vector<std::vector<fluxVar>>& F_LorR,
    const std::vector<std::vector<consVar>>& Q_eta,

    int nx,
    int ny,
    double gamma
);


#endif
