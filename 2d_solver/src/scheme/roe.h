#ifndef CFD_SCHEMES_ROE
#define CFD_SCHEMES_ROE

#include "consVar.h"

/* Parameters required
 * -------------------
 *
 *  struct primitiveVar V_L     : Primitive Variable on the left side of any direction
 *  struct primitiveVar V_R     : Primitive Variable on the right side of any direction
 *
 * Computes the required average values for the Roe scheme
 */
primitiveVar computeRoeAverage
(
    const primitiveVar& V_L, const primitiveVar& V_R,
    const double& gamma
);


/* Parameters required
 * -------------------
 *
 *  2D vector consVar Q_xi_L     : Conservative variables on the left along xi direction
 *  2D vector consVar Q_xi_R     : Conservative variables on the right along xi direction
 *  2D vector consVar Q_eta_L    : Conservative variables on the left along eta direction
 *  2D vector consVar Q_eta_R    : Conservative variables on the right along eta direction
 *
 * Performs all operations to compute roe on the faces
 */
void computeRoeFluxes
(
    std::vector<std::vector<consVar>>& Q_xi_L, std::vector<std::vector<consVar>>& Q_xi_R,
    std::vector<std::vector<consVar>>& Q_eta_L, std::vector<std::vector<consVar>>& Q_eta_R

);


#endif
