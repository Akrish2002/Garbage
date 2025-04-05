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
    int coords_nx = coords_2D.size();
    int coords_ny = coords_2D[0].size();

    //Allocating memory
    allocate_2D(nx, ny, grid_2D);
    
    //grid_2D = coords_2D;

    //Assigning coords value to allocated grid
    for(int j = 0; j < ny; j++)    
    {
       for(int i = 0; i < nx; i++)
       {
           grid_2D[i][j].x = coords_2D[j * nx + i][0];
           grid_2D[i][j].y = coords_2D[j * nx + i][1];
        }
    }

    std::cout<<"--2D coords have been transformed and assigned to grid_2D"<<"\n\n";
    std::cout<<"--[1,1] Grid Value x and y : "<<grid_2D[1][1].x<<" "<<grid_2D[1][1].y<<std::endl;
    std::cout<<"--[1,2] Grid Value x and y : "<<grid_2D[1][2].x<<" "<<grid_2D[1][2].y<<std::endl;
}

/*Parameters required:
 * ------------------
 *  vector<<vector<double>>     : grid of 2D points
 */
void Grid::addHaloCells_2D()
{
        //Recommended practice to use size_t instead of int
        size_t rows = grid_2D.size(); 
        if(rows == 0) std::cout<<"--Empty grid!"<<std::endl;
        size_t cols = grid_2D[0].size(); 
        if(cols < 2)  std::cout<<"--Need at least two columns for halo cells!"<<std::endl;
        
        size_t cols_ghost = cols + 2; //Increased by two for ghost cells
        size_t rows_ghost = rows + 2;
        std::cout<<"--Rows_ghost: "<<rows_ghost<<std::endl;        
        std::cout<<"--Columns_ghost: "<<cols_ghost<<std::endl;        

        //Allocating memory for ghost grid 
        allocate_2D(rows_ghost, cols_ghost, grid_ghost_2D);
        std::cout<<"--Allocation for ghost grid is fine!"<<std::endl; 

        //Assigning column values
        for(size_t i = 0; i < rows; i++)
        {
            
            grid_ghost_2D[i+1][0].x = 2*grid_2D[i][0].x - grid_2D[i][1].x;
            grid_ghost_2D[i+1][cols_ghost - 1].x = 2*grid_2D[i][cols - 1].x - grid_2D[i][cols - 2].x;
            grid_ghost_2D[i+1][0].y = 2*grid_2D[i][0].y - grid_2D[i][1].y;
            grid_ghost_2D[i+1][cols_ghost - 1].y = 2*grid_2D[i][cols - 1].y - grid_2D[i][cols - 2].y;
        }
        std::cout<<"--Column value assignment is fine!"<<std::endl;
   
//       //Assigning row values
        for(size_t j = 0; j < cols; j++)
        {
            
            grid_ghost_2D[0][j+1].y = 2*grid_2D[0][j].y - grid_2D[1][j].y;
            grid_ghost_2D[rows_ghost - 1][j + 1].y = 2*grid_2D[rows - 1][j].y - 
                                                       grid_2D[rows - 2][j].y; 

            grid_ghost_2D[0][j+1].x = 2*grid_2D[0][j].x - grid_2D[1][j].x;
            grid_ghost_2D[rows_ghost - 1][j + 1].x = 2*grid_2D[rows - 1][j].x - 
                                                       grid_2D[rows - 2][j].x; 
        }
   
        //Assigning interior values
        for (size_t i = 0; i < rows; ++i) 
        {
            for (size_t j = 0; j < cols; ++j) 
            {
                grid_ghost_2D[i+1][j+1] = grid_2D[i][j];
            }
        }
        
        //Assigning corner x values
        grid_ghost_2D[0][0].x = 2*grid_ghost_2D[0][1].x - grid_ghost_2D[0][2].x;
        grid_ghost_2D[0][cols_ghost - 1].x = 2*grid_ghost_2D[0][cols_ghost - 2].x 
                                           - grid_ghost_2D[0][cols_ghost - 3].x;
        grid_ghost_2D[rows_ghost - 1][0].x = 2*grid_ghost_2D[0][1].x - grid_ghost_2D[0][2].x;
        grid_ghost_2D[rows_ghost - 1][cols_ghost - 1].x = 2*grid_ghost_2D[0][cols_ghost - 2].x
                                                          - grid_ghost_2D[0][2].x;
        
        //Assigning corner y values
        grid_ghost_2D[0][0].y = 2*grid_ghost_2D[0][1].y - grid_ghost_2D[0][2].y;
        grid_ghost_2D[0][cols_ghost - 1].y = 2*grid_ghost_2D[0][cols_ghost - 2].y 
                                           - grid_ghost_2D[0][cols_ghost - 3].y;
        grid_ghost_2D[rows_ghost - 1][0].y = 2*grid_ghost_2D[0][1].y - grid_ghost_2D[0][2].y;
        grid_ghost_2D[rows_ghost - 1][cols_ghost - 1].y = 2*grid_ghost_2D[0][cols_ghost - 2].y
                                                          - grid_ghost_2D[0][2].x;

        
        std::cout<<"--[1,0] Ghost Grid value x and y : "<<grid_ghost_2D[1][0].x<<" "<<2*grid_ghost_2D[1][0].y<<std::endl;
        std::cout<<"--[1,1] Ghost Grid value x and y : "<<grid_ghost_2D[1][1].x<<" "<<2*grid_ghost_2D[1][1].y<<std::endl;
        std::cout<<"--[1,2] Ghost Grid value x and y : "<<grid_ghost_2D[1][2].x<<" "<<2*grid_ghost_2D[1][2].y<<std::endl;
        std::cout<<"\n\n--Ghost cells have been added"<<std::endl; 
} 
