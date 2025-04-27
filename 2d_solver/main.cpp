#include "read.h"
#include "allocate.h"
#include "write.h"

#include "grid.h"
#include "solver.h"

#include <iostream>
#include <vector>

/* Main file for testing/running the case
 *
 *
 */

int main()
{

//------------------------------------------------------------------------//
    //Thermodynamic properties
    double R        =   287.0;  //  J / (kg-K)
    double Cp       =   1005.0; //  J / (kg-K)  
    double gamma    =   1.400;  //  Dimensionless

    //Initial conditions
    double P = 11664;
    double T = 216.7;
    double c = 295.0;    
    double M = 3.0;
    
    double rho;
    rho = P / (R * T);
    
    double u;
    u = M * c;
     
    double v;
    v = 0;

    //MUSCL parameters
    double epsilon  = 0;
    double kappa    = 0;
 
    //Iterations
    double N = 13600;
    double CFL = 0.5;
    
//------------------------------------------------------------------------//

    std::string gridpath = "data/g641x065uf";

    //Initializing Solver object
        //Initializing Grid object
        //Reading Grid
        //Adding Halo cells
        //Computing Metrics
    Solver Case(
                    gridpath, 

                    gamma, Cp, R,
                    
                    P, T, c, M,
        
                    rho, u, v, 

                    epsilon, kappa,
                    N,
                    CFL
                );
    //Applying initial and boundary conditions
    //Iterating till convergence
    Case.setup();     

    Case.run(N);    


    return 0;
}
