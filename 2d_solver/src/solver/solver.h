#ifndef CFD_SOLVER_SOLVER_H
#define CFD_SOLVER_SOLVER_H

#include "grid.h"

#include "consVar.h"
#include "fluxVar.h"

class Solver 
{

    private:
    
        double gamma_, CFL_;

        Grid grid_;
        int nx_, ny_;

        std::vector<std::vector<consVar>> Q_;
        std::vector<std::vector<consVar>> Q_xi_L, Q_xi_R;
        std::vector<std::vector<consVar>> Q_eta_L, Q_eta_R;

        std::vector<std::vector<fluxVar>> E_;
        std::vector<std::vector<fluxVar>> E_L, E_R;

        std::vector<std::vector<fluxVar>> F_;
        std::vector<std::vector<fluxVar>> F_L, F_R;

        //Initialize conditions
        void applyICs();
        void applyBCs();

        void computeFlux();

        double computedt();
        void computeResiduals();
        void stepSolution(double dt);


    public:
    
        Solver(const std::string &gridPath, const double gamma, double CFL);
        
        //Read grid, build halo and compute metrics
        void setup();
        
        void run(int iter);
        
        void writeResults();

}; 
