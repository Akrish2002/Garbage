#include "utils.h"

#include <cmath>
#include <cstddef>

primitiveVar convertConstoPrim
(
    const consVar& Q,
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


consVar convertPrimtoCons
(
    const primitiveVar& V,
    const double gamma
)
{
    consVar Q;
    
    Q.rho       =   V.rho;
    Q.rho_u     =   V.rho * V.u;    
    Q.rho_v     =   V.rho * V.v;    
    Q.rho_et    =   V.rho * V.et;    

    return Q;

}
        


void computeXiFlux
(
    Grid& grid_,

    std::vector<std::vector<fluxVar>>& E_LorR,
    const std::vector<std::vector<consVar>>& Q_xi,

    int nx,
    int ny,
    double gamma
)
{
    for(size_t i = 1; i < ny; i++)
    {
        for(size_t j = 1; j < nx + 1; j++)
        {

            primitiveVar V;
            V = convertConstoPrim(Q_xi[i][j], gamma);
           
            double S_xi_x       =   grid_.getnxXi(i - 1, j - 1); 
            double S_xi_y       =   grid_.getnyXi(i - 1, j - 1); 
            double S_xi_area    =   grid_.getareaXi(i - 1, j - 1); 

            double U_ = (S_xi_x * V.u + S_xi_y * V.v) / S_xi_area;
        
            E_LorR[i][j].rho_flux      = V.rho * U_;
            E_LorR[i][j].rho_u_flux    = V.rho * V.u  * U_ + (S_xi_x / S_xi_area) * V.P;
            E_LorR[i][j].rho_v_flux    = V.rho * V.v  * U_ + (S_xi_y / S_xi_area) * V.P;
            E_LorR[i][j].rho_ht_flux   = V.rho * V.ht * U_;
       }
    } 
}    


void computeEtaFlux
(
    Grid& grid_,

    std::vector<std::vector<fluxVar>>& F_LorR,
    const std::vector<std::vector<consVar>>& Q_eta,

    int nx,
    int ny,
    double gamma
)
{

    for(size_t i = 1; i < nx; i++)
    {
        for(size_t j = 1; j < ny + 1 ; j++)
        {

            primitiveVar V;
            V = convertConstoPrim(Q_eta[j][i], gamma);
            
            double S_eta_x       =   grid_.getnxEta(j - 1, i - 1); 
            double S_eta_y       =   grid_.getnyEta(j - 1, i - 1); 
            double S_eta_area    =   grid_.getareaEta(j - 1, i - 1); 
            
            double V_ = (S_eta_x * V.u + S_eta_y * V.v) / S_eta_area;
        
            F_LorR[j][i].rho_flux      = V.rho * V_;
            F_LorR[j][i].rho_u_flux    = V.rho * V.u  * V_ + (S_eta_x / S_eta_area) * V.P;
            F_LorR[j][i].rho_v_flux    = V.rho * V.v  * V_ + (S_eta_y / S_eta_area) * V.P;
            F_LorR[j][i].rho_ht_flux   = V.rho * V.ht * V_;
       }
    }
 
}






