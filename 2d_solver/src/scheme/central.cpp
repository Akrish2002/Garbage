#include "central.h"

#include <vector>
#include <string>

#include "fluxVar.h"
#include "utils.h"


consVar computeCentralFlux
(
    std::vector<std::vector<consVar>>& Q_xi_L, std::vector<std::vector<consVar>>& Q_xi_R,
    std::vector<std::vector<consVar>>& Q_eta_L, std::vector<std::vector<consVar>>& Q_eta_R,
    
    std::vector<std::vector<fluxVar>>& E_f,
    std::vector<std::vector<fluxVar>>& F_f,

    const double& gamma,
    Grid grid
)
{
    int nx = grid.getnx(); 
    int ny = grid.getny(); 

    for(int i = 1; i < ny; i++)
    {
        for(int j = 1; j < nx + 1; j++)
        { 
             






}
