//Include guard
#ifndef CFD_GRID_GRID_H
#define CFD_GRID_GRID_H

#include <vector>
#include <array>
#include <string>

// Grid Class
// 2D grid reader and additional fucntions

struct Point
{    
    double x;
    double y;
        
    Point(double x_ = 0.0, double y_ = 0.0 ) : x(x_), y(y_) {}
    
};
 
//Have to code it to output files to plot the halo cells, normal grid and  binary or .dat 
class Grid
{
    private:

        std::string fpath;
        bool write;
        int nx, ny;

        std::vector<std::vector<double>> coords_2D, cc_2D, cf_xi_2D, cf_eta_2D;
        
        std::vector<std::vector<Point>> n_2D, n_g_2D;// cc_2D, cf_xi_2D, cf_eta_2D; 

    public:
        //Constructor
        Grid(std::string file, bool write = false);

        //Functions
        void AddHaloCells_2D();
        void ComputeMetrics(int dim=2);
        void ComputeProjCellFaceArea(); 
         
        //Destructor
        //Initially implemented destructor, but read online that it is not necessary as the memor          y is deallocated once it goes out of scope. 
        // ~Grid();
};

#endif
