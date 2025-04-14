#ifndef CFD_SCHEMES_ROE
#define CFD_SCHEMES_ROE

#include "consVar.h"

void computeRoeFluxes
(
    std::vector<std::vector<consVar>>& Q_xi_L, std::vector<std::vector<consVar>>& Q_xi_R,
    std::vector<std::vector<consVar>>& Q_eta_L, std::vector<std::vector<consVar>>& Q_eta_R

);


#endif
