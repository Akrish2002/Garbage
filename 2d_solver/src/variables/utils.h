#ifndef CFD_SCHEMES_CONVERSION_H
#define CFD_SCHEMES_CONVERSION_H

#include "consVar.h"
#include "primitiveVar.h"
#include "fluxVar.h"
#include "grid.h"

#include <Eigen/Dense>

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
 *  consVar Q   : Conservative variable structure 
 *
 *  This function converts the struct consVar to a vector for matrix operations
 */
using Vec4 = Eigen::Matrix<double,4,1>;
inline Vec4 convertconsVartoVec(const consVar& q)
{
    Vec4 v;
    v << q.rho,
         q.rho_u,
         q.rho_v,
         q.rho_et;

    return v;

};


/* Parameters required
 * -------------------
 *  
 *  fluxVar Q   : Flux variable structure 
 *
 *  This function converts the struct fluxVar to a vector for matrix operations
 */
using Vec4 = Eigen::Matrix<double,4,1>;
inline Vec4 convertfluxVartoVec(const fluxVar& q)
{
    Vec4 f;
    f << q.rho_flux,
         q.rho_u_flux,
         q.rho_v_flux,
         q.rho_ht_flux;

    return f;

};


/* Parameters required
 * -------------------
 *  
 *  Vec4   : Column vector of size 4x1 (Check inline defn below)
 *
 *  This function converts the column flux vector to the struct fluxVar
 */
using Vec4 = Eigen::Matrix<double,4,1>;
inline fluxVar convertVectofluxVar(const Vec4 &v) 
{
    fluxVar f;
    f.rho_flux      = v(0);
    f.rho_u_flux    = v(1);
    f.rho_v_flux    = v(2);
    f.rho_ht_flux   = v(3);
    return f;
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
    double gamma
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
