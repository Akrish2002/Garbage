#ifndef CFD_SOLVER_SOLVER_H
#define CFD_SOLVER_SOLVER_H

#include "grid.h"
#include "consVar.h"
#include "fluxVar.h"
#include "primitiveVar.h"

class Solver 
{

    private:
    
        double gamma_, Cp_, R_;
        double P_, T_, c_, M_;
        
        double rho_, u_, v_, et_, ht_;

        double epsilon_, kappa_;
        double N_;
        double CFL_;
        double dt_;

        Grid grid_;
        int nx_, ny_;

        std::vector<std::vector<consVar>> Q_;
        std::vector<std::vector<consVar>> Q_1;
        std::vector<std::vector<consVar>> Q_xi_L, Q_xi_R;
        std::vector<std::vector<consVar>> Q_eta_L, Q_eta_R;

        std::vector<std::vector<primitiveVar>> V_inf_;
        std::vector<std::vector<primitiveVar>> V_;

        std::vector<std::vector<fluxVar>> E_;
        std::vector<std::vector<fluxVar>> E_L, E_R;

        std::vector<std::vector<fluxVar>> F_;
        std::vector<std::vector<fluxVar>> F_L, F_R;

        //Initialize conditions
        void    applyICs();
        void    applyBCs();
        void    computeFlux();
        double  computedt();
        void    computeResiduals();
        void    integratethroughTime();

    public:
    
        Solver(
                    const std::string &gridpath, 

                    const double gamma, const double Cp, const double R, 
                    
                    const double P, const double T, const double c, const double M,                    

                    const double rho, const double u, const double v,
                                   
                    const double epsilon, const double kappa,
                    const double N, 
                    const double CFL
                );
        
        //Read grid, build halo and compute metrics
        void setup();
        
        void run(int iter);
        
        void writeResults();

}; 


#endif
