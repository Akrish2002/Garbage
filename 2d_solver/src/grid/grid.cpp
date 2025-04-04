#include "grid_read.h"
#include "allocate.h"
#include "grid.h"

#include <vector>
#include <iostream>
#include <string>
#include <array>
#include <cstddef> //For size_t

/* Constructor to read grid file
 *
 * Parameters:
 * -----------
 *  string cfpath : relative path + filename of grid file.
 *
 */

Grid::Grid(std::string file, bool write)
{

    //Reading grid coords
    grid_read(file, coords_2D, nx, ny);

    //Allocating memory
    allocate_2D(nx, ny, grid_2D);

    //Assigning coords value to allocated grid
    grid_2D = coords_2D;
    
    std::cout<<"--2D array of coordinates have been assigned"<<std::endl;
    //std::cout<<grid_2D[1][1]<<std::endl;
}

/*Parameters required:
 * ------------------
 *  vector<<vector<double>>     : grid of 2D points
 */
void addHaloCells_2D(std::vector<std::vector<double>>& grid_2D)
{
        //Recommended practice to use size_t instead of int
        size_t rows = grid_2D.size(); 
        if(rows == 0) return std::cout<<"--Empty grid!"<<std::endl;
        size_t cols = grid_2D[0].size(); 
        if(cols < 2) return std::cout<<"--Need at least two columns for halo cells!"<<std::endl;
        
        int cols_ghost = cols + 2; //Increased by two for ghost cells
        int rows_ghost = rows + 2;
        std::vector<std::vector<double>> grid_2D_ghost;
        
        //Allocating memory for ghost grid 
        allocate_2D(rows_ghost, cols_ghost, grid_2D_ghost);
        
        //Assigning column values
        for(int i = 0; i < rows_ghost; i++)
        {
            grid_2D_ghost[i][0] = grid_2D[i][0] - grid_2D[i][1];
            grid_2D_ghost[i][cols_ghost - 1] = grid_2D[i][cols - 1] - grid_2D[i][cols - 2];
        }

        //Assigning row values
        for(int j = 0; j < cols_ghost; j++)
        {
            grid_2D_ghost[0][j] = grid_2D[0][j] - grid_2D[1][j];
            grid_2D_ghost[rows_ghost - 1][j] = grid_2D[rows_ghost - 1][j] - 
                                               grid_2D[rows_ghost - 2][j]; 
        }
        
        std::cout<<"--Ghost cells have been added"<<std::endl; 
} 
