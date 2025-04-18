#ifndef CFD_SOLVER_SOLVER_H
#define CFD_SOLVER_SOLVER_H

#include "grid.h"

#include "consVar.h"
#include "fluxVar.h"

class Solver 
{

    private:
    
        Grid grid_;
        double gamma_, CFL_;

        std::vector<std::vector<consVar>> Q_;
        std::vector<std::vector<fluxVar>> E_, F_;

        //Initialize conditions
        void inititalize();
        void applyBCs();
        double compute_dt();
        void computeResiduals();
        void stepSolution(double dt);


    public:
    
        Solver(const std::string &gridPath, const double gamma, double CFL);
        
        //Read grid, build halo and compute metrics
        void setup();
        
        void run(int iter);
        
        void writeResults();

}; 
