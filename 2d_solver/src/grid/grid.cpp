#include "grid.h"

#include <vector>
#include <iostream>
#include <string>
#include <array>
#include <cstddef> //For size_t
#include <cmath>

#include "read.h"
#include "allocate.h"
#include "write.h"
#include "debug.h"

/* Constructor to read grid file
 *
 * Parameters:
 * -----------
 *  string cfpath : relative path + filename of grid file.
 *
 */

Grid::Grid(std::string fpath, bool write)
{

    //Reading grid coords
    //Passed by refernce, so I get back the right nx and ny values
    read(fpath, coords_2D, nx, ny);
    
    //Allocating memory
    allocate_2D(ny, nx, n_2D);
    
    //Assigning coords value to allocated grid
    for(int i = 0; i < ny; i++)    
    {
       for(int j = 0; j < nx; j++)
       {
           n_2D[i][j].x = coords_2D[i * nx + j][0];
           n_2D[i][j].y = coords_2D[i * nx + j][1];
        }
    }

    std::cout<<"--2D coords have been transformed and assigned to n_2D"<<"\n\n";
    exportGridToCSV(n_2D, "n_2D.csv");
    std::cout<<std::endl;
    
    D_GridConstructer(n_2D);

}


/*Parameters required:
 * ------------------
 * None, calls values from the object of Grid class 
 *
 * Add halo cells
 */

void Grid::addHaloCells_2D()
{
        //Recommended practice to use size_t instead of int
        size_t rows = n_2D.size(); 
        if(rows == 0) std::cout<<"--Empty grid!"<<std::endl;
        size_t cols = n_2D[0].size(); 
        if(cols < 2)  std::cout<<"--Need at least two columns for halo cells!"<<std::endl;
        
        size_t cols_g = cols + 2; //Increased by two for ghost cells
        size_t rows_g = rows + 2;
//       std::cout<<"--Rows_ghost: "<<rows_g<<std::endl;        
//       std::cout<<"--Columns_ghost: "<<cols_g<<std::endl;        

        //Allocating memory for ghost grid 
        allocate_2D(rows_g, cols_g, n_g_2D);
        std::cout<<"--Allocation for ghost grid is fine!"<<std::endl; 

        //Assigning column values
        for(size_t i = 0; i < rows; i++)
        {

            n_g_2D[i+1][0].x = 2*n_2D[i][0].x - n_2D[i][1].x;
            n_g_2D[i+1][cols_g - 1].x = 2*n_2D[i][cols - 1].x - n_2D[i][cols - 2].x;

            n_g_2D[i+1][0].y = 2*n_2D[i][0].y - n_2D[i][1].y;
            n_g_2D[i+1][cols_g - 1].y = 2*n_2D[i][cols - 1].y - n_2D[i][cols - 2].y;

        }
        std::cout<<"--Column value assignment is done!"<<std::endl;
   
       //Assigning row values
        for(size_t j = 0; j < cols; j++)
        {
            
            n_g_2D[0][j+1].y = 2*n_2D[0][j].y - n_2D[1][j].y;
            n_g_2D[rows_g - 1][j + 1].y = 2*n_2D[rows - 1][j].y - n_2D[rows - 2][j].y; 

            n_g_2D[0][j+1].x = 2*n_2D[0][j].x - n_2D[1][j].x;
            n_g_2D[rows_g - 1][j + 1].x = 2*n_2D[rows - 1][j].x - n_2D[rows - 2][j].x; 

        }
        std::cout<<"--Row value assignment is done!"<<std::endl;

        //Assigning interior values
        for (size_t i = 0; i < rows; ++i) 
        {
            for (size_t j = 0; j < cols; ++j) 
            {
                n_g_2D[i+1][j+1] = n_2D[i][j];
            }
        }
        
        
        //Top Left 
        n_g_2D[0][0].x = 2*n_g_2D[0][1].x - n_g_2D[0][2].x;
        n_g_2D[0][0].y = 2*n_g_2D[0][1].y - n_g_2D[0][2].y;

        //Top Right 
        n_g_2D[0][cols_g - 1].x = 2*n_g_2D[0][cols_g - 2].x - n_g_2D[0][cols_g - 3].x;
        n_g_2D[0][cols_g - 1].y = 2*n_g_2D[0][cols_g - 2].y - n_g_2D[0][cols_g - 3].y;
        
        //Bottom Left
        n_g_2D[rows_g - 1][0].x = 2*n_g_2D[rows_g - 1][1].x - n_g_2D[rows_g - 1][2].x;
        n_g_2D[rows_g - 1][0].y = 2*n_g_2D[rows_g - 1][1].y - n_g_2D[rows_g - 1][2].y;
        
        //Bottom Right
        n_g_2D[rows_g - 1][cols_g - 1].x = 2*n_g_2D[rows_g - 1][cols_g - 2].x - n_g_2D[rows_g - 1][cols_g - 3].x;
        n_g_2D[rows_g - 1][cols_g - 1].y = 2*n_g_2D[rows_g - 1][cols_g - 2].y - n_g_2D[rows_g - 1][cols_g - 3].y;

        std::cout<<"--Interior and Corner value assignment done!"<<std::endl; 

        D_AddHaloCells(n_g_2D);

        exportGridToCSV(n_g_2D, "n_g_2D.csv");
        std::cout<<std::endl;
}

