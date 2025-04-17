#include "roe.h"

#include <cmath>
#include <vector>
#include <iostream>

#include "consVar.h"
#include "primitiveVar.h"
#include "conversion.h"

primitiveVar computeRoeAverage
(
    const primitiveVar& V_L, const primitiveVar& V_R,
    const double& gamma
)
{
    primitiveVar V_avg;
    
    double rho_L, rho_R;
    rho_L = std::sqrt(V_L.rho);
    rho_R = std::sqrt(V_R.rho);

    V_avg.rho = std::sqrt(V_L.rho * V_R.rho);
   
    V_avg.u   = (rho_L * V_L.u + rho_R * V_R.u) / (rho_L + rho_R);

    V_avg.v   = (rho_L * V_L.v + rho_R * V_R.v) / (rho_L + rho_R);

    V_avg.h   = (rho_L * V_L.h + rho_R * V_R.h) /(rho_L + rho_R);

    V_avg.a   = (gamma - 1) * (V_avg.h - 0.5 * (V_avg.u * V_avg.u + V_avg.v * V_avg.v))
    
    return V_avg;
}

RlamdaRinv buildRlamdaRinv
(
    const primitiveVar& V_avg
    const double S_area,
    const double S_nx,
    const double S_ny
)
{
    RlamdaRinv RlRinv;

    double u    = V_avg.u;  
    double v    = V_avg.v;
    double ht   = V_avg.ht;
    double a    = V_avg.a;

    // 2. Building R column by column
    RlRinv.R<<
                1,                      1,                  1,                      0
                u - a * S_nx,           u,                  u + a * S_nx,           S_ny
                v - a * S_ny,           v,                  v + a * S_ny,           -1 * S_nx
               ht - a * (u*nx + v*ny)   0.5 * (u*u + v*v)   ht + a * (u*nx + v*ny)  u*ny - v*nx

    // 3. Building lamda
    double un = u*S_nx + v*S_ny;

    RlRinv.lamda = Eigen::Matrix4d::Zero();
    //Filling the diagonals
    RlRinv.lamda(0,0) = std::abs(un - a);
    RlRinv.lamda(1,1) = std::abs(  un  );
    RlRinv.lamda(2,2) = std::abs(un + a);
    RlRinv.lamda(3,3) = std::abs(  un  );
 
    // 4. The inverse of R
    RlRinv.Rinv = RlRinv.R.inverse();

    return RlRinv;

} 

void computeRoeFluxes
(
    std::vector<std::vector<consVar>>& Q_xi_L, std::vector<std::vector<consVar>>& Q_xi_R,
    std::vector<std::vector<consVar>>& Q_eta_L, std::vector<std::vector<consVar>>& Q_eta_R
    const double& gamma
    Grid grid
)
{
    int nx = grid.getnx();
    int ny = grid.getny();
    
    //Running the loop to perform flux reconstruction at the faces
    for(int i = 1; i < ny; i++)
    {
        for(int j = 0; j < nx; j++)
        {

            //xi direction
            primitiveVar V_xi_L = convertConstoPrim(Q_xi_L[][], gamma);
            primitiveVar V_xi_R = convertConstoPrim(Q_xi_R[][], gamma);
             
            //eta direction
            primitiveVar V_eta_L = convertConstoPrim(Q_eta_L[][], gamma);
            primitiveVar V_eta_R = convertConstoPrim(Q_eta_R[][], gamma);
            
            //Computing roe averages
        
            //xi
            computeRoeAverage(V
        
            //eta
            computeRoeAverage(V
        }
    }

}
