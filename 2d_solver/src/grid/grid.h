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

        std::vector<std::vector<double>> coords_2D;
        std::vector<std::vector<double>> S_xi_2D,  S_xi_x_2D,  S_xi_y_2D;
        std::vector<std::vector<double>> S_eta_2D, S_eta_x_2D, S_eta_y_2D; 
        std::vector<std::vector<double>> cc_vol_2D;
        
        std::vector<std::vector<Point>> n_2D, n_g_2D, nc_2D, nc_g_2D, cc_xi_eta_2D;// cc_2D, cf_xi_2D, cf_eta_2D; 

    public:
        //Constructor
        Grid(std::string file, bool write = false);

        //Functions
        void addHaloCells_2D();

        void computeMetrics(int dim=2);
        void computeProjCellFaceArea(); 
        void avgtoCellCenter();
        void computeCellVol();
        
        //Getter functions for computing nx and ny
        int Grid::getnx() const { return nx; }
        int Grid::getny() const { return ny; }

        //Getter functions for computing nx and ny in Roe scheme buildRlamdaRinv
        double Grid::getareaXi(int i,int j) const {            return S_xi_2D[i][j];        }
        double Grid::getnxXi  (int i,int j) const { return S_xi_x_2D[i][j] / S_xi_2D[i][j]; }
        double Grid::getnyXi  (int i,int j) const { return S_xi_y_2D[i][j] / S_xi_2D[i][j]; }
        
        double Grid::getareaEta(int i,int j) const {           return S_eta_2D[i][j];          }
        double Grid::getnxEta  (int i,int j) const { return S_eta_x_2D[i][j] / S_eta_2D[i][j]; }
        double Grid::getnyEta  (int i,int j) const { return S_eta_y_2D[i][j] / S_eta_2D[i][j]; }

        //Destructor
        //Initially implemented destructor, but read online that it is not necessary as the memor          y is deallocated once it goes out of scope. 
        // ~Grid();
};


#endif
