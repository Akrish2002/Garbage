#ifndef CFD_SCHEMES_CONVERSION_H
#define CFD_SCHEMES_CONVERSION_H

#include "consVar.h"
#include "primitiveVar.h"
#include "fluxVar.h"

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
    consVar& Q,
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
inline Vec4 converttoVec(const consVar& q)
{
    Vec4 v;
    v << q.rho,
         q.rho_u,
         q.rho_v,
         q.rho_et;

    return v;

};


fluxVar computeFlux
(
    const consVar &Q,
    double Sx,
    double Sy,
    double Smag,
    double gamma
);

#endif
