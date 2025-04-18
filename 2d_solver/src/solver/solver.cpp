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
Solver::Solver(const std::string &gridPath, const double gamma, double CFL)
{
    grid_(gridPath);


}


void Solver::initialize()
{
    




}


void Solver::applyBCs()
{



}


double compute_dt()
{



}


//-----------------------------------------------------------
//1. Read grid
//   Construct halo cells
//   Compute metrics
//   Initialize field and BCs
void Solver::setup()
{
    grid_.addHaloCells_2D();
    grid_.computeMetrics(2);

    int nx = grid_.getnx();
    int ny = grid_.getny();

    allocate_2D(ny + 1, nx + 1, Q_);

    initialize();
    applyBCs();

}


void run(int iter)
{

    int nx = grid_.getnx();
    int ny = grid_.getny();

    allocate_2D(ny + 1, nx + 1, E);
    allocate_2D(nx + 1, ny + 1, F);

    for(
    {

        //Extrapolate consVar to the faces
        performMUSCL
        (
            nx, ny,
            epsilon, kappa,
            Q,
            Q_xi_L,  Q_xi_R,
            Q_eta_L, Q_eta_R,
            "minmod"
        )
        
        //Pass computed Q_L and Q_R to compute the fluxes
        //eta
        E = computeFlux
            (
                Q,
                grid.getnxXi(
            


}


