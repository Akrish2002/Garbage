#include "solver.h"

#include <string>
#include <cmath>

#include "read.h"
#include "write.h"
#include "allocate.h"
#include "MUSCL.h"
#include "flux.h"

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





