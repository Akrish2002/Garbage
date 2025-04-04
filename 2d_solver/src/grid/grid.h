//Include guard
#ifndef CFD_GRID_GRID_H
#define CFD_GRID_GRID_H

#include <vector>
#include <array>
#include <string>


// Grid Class
// 2D grid reader and additional fucntions

//Have to code it to output files to plot the halo cells, normal grid and  binary or .dat 
class Grid
{
    private:
        std::string file;
        bool write;
        std::vector<std::vector<double>> coords_2D;
        int nx, ny;
        
        std::vector<std::vector<double>> grid_2D;        

    public:
        //Constructor
        Grid(std::string file, bool write = false);

        //Functions
        void addHaloCells();
        void computeMetrics();

        //Destructor
        //Initially implemented destructor, but read online that it is not necessary as the memor          y is deallocated once it goes out of scope. 
        // ~Grid();
};

#endif
