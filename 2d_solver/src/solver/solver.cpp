#include "solver.h"

#include <string>
#include <cmath>

#include "read.h"
#include "write.h"
#include "allocate.h"
#include "MUSCL.h"
#include "utils.h"
#include "central.h"

//Constructor
Solver::Solver(const std::string &gridpath, const double gamma, double CFL)
{
    grid_(gridpath);
    grid_.addHaloCells_2D();
    grid_.computeMetrics(2); //Change this to not take in "2" since halocells addition is for 2D
    
    //Getting size of grid, this is not including halocells
    nx_ = grid_.getnx();
    ny_ = grid_.getny();

    //Initialize the sizes of; 

    //Q
    allocate_2D(ny + 1, nx + 1, Q_); //Including Halo cells

    allocate_2D(ny + 1, nx + 1, Q_xi_L);
    allocate_2D(ny + 1, nx + 1, Q_xi_R);

    allocate_2D(ny + 1, nx + 1, Q_eta_L);
    allocate_2D(ny + 1, nx + 1, Q_eta_R);
   
    //E
    allocate2D(ny + 1, nx + 1, E_);

    allocate2D(ny + 1, nx + 1, E_L);
    allocate2D(ny + 1, nx + 1, E_R);
    
    //F
    allocate2D(ny + 1, nx + 1, F_);

    allocate2D(ny + 1, nx + 1, F_L);
    allocate2D(ny + 1, nx + 1, F_R);

}


void Solver::applyICs()
{
    for(size_t i = 0; i < nx + 2    



}


void Solver::applyBCs()
{
    


}

void Solver::computeFlux()
{

         computeXiFlux
         (
            grid_,

            E_L,
            Q_xi_L,

            nx,
            ny,
            gamma
         );  

         computeXiFlux
         (

            grid_,

            E_R,
            Q_xi_R,

            nx,
            ny,
            gamma
        ); 

         computeEtaFlux
         (
            grid_,

            F_L,
            Q_eta_L,

            nx,
            ny,
            gamma
         ); 

         computeEtaFlux
         (
            grid_,

            F_R,
            Q_eta_R,

            nx,
            ny,
            gamma
         ); 


}

double Solver::computedt();
{



}


//-----------------------------------------------------------
//1. Read grid
//   Construct halo cells
//   Compute metrics
//   Initialize field and BCs
void Solver::setup()
{

    applyICs();
    applyBCs();

}


void Solver::run(int iter)
{

    for()
    {
        //1. Interpolate flux values from center to face
        //Not including limiter, since default is minmod
        performMUSCL
        (
            nx, ny,
            epsilon, kappa,

            Q,
            Q_xi_L,  Q_xi_R,
            Q_eta_L, Q_eta_R,
        );
        

        //2.
        
        //2.1 
        //Function that calls computeXiFlux and computeEtaFlux twice each to compute flux on each 
        //side in each direction
        computeFlux();
       
        //2.2 
        //Perform Roe
        performRoe
        (
            grid_,
        
            Q_xi_L, Q_xi_R,
            Q_eta_L, Q_eta_R,
            
            E_, 
            E_L, E_R,
                        
            F_, 
            F_L, F_R,

            gamma
        );
        
        

}


