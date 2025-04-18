#ifndef CFD_SCHEMES_CENTRAL_H
#define CFD_SCHEMES_CENTRAL_H

#include "consVar.h"

consVar computeCentralFlux
(
    std::vector<std::vector<consVar>>& Q_xi_L, std::vector<std::vector<consVar>>& Q_xi_R,
    std::vector<std::vector<consVar>>& Q_eta_L, std::vector<std::vector<consVar>>& Q_eta_R,
    
    std::vector<std::vector<fluxVar>>& E_f,
    std::vector<std::vector<fluxVar>>& F_f,

    const double& gamma,
    Grid grid
);

#endif
