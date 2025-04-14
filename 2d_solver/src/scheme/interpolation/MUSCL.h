#ifndef CFD_SCHEMES_MUSCL_H
#define CFD_SCHEMES_MUSCL_H

#include "grid.h"
#include "consVar.h"

#include <vector>

/* Parmeters required
 * ------------------
 *
 *  int     nx              :   Number of columns    --> Size of xi  
 *  int     ny              :   Number of rows       --> Size of eta
 *  double  epsilon         :   MUSCL parameter 1
 *  double  kappa           :   MUSCL parameter 2
 *  consVar Q              :   State variables at cell centers   
 *  consVar Q_xi_L and     :   State variables on the left and right faces along each direction
 *  consVar Q_xi_R 
 *  consVar Q_eta_L 
 *  consVar Q_eta_R 
 *
 * MUSCL Scheme --> Uses high order extrapolation of state variables to approximate fluxes at respective cell face
 */
void performMUSCL(
    
    int nx, int ny,
    double epsilon, double kappa,
    std::vector<std::vector<consVar>>& Q,
    std::vector<std::vector<consVar>>& Q_xi_L, std::vector<std::vector<consVar>>& Q_xi_R,
    std::vector<std::vector<consVar>>& Q_eta_L, std::vector<std::vector<consVar>>& Q_eta_R,
    const std::string& FL

);


#endif



