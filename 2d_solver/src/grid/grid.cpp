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
    read(fpath, coords_2D, nx, ny);
    int coords_nx = coords_2D.size();
    int coords_ny = coords_2D[0].size();

    //Allocating memory
    allocate_2D(nx, ny, n_2D);
    
    //Assigning coords value to allocated grid
    for(int j = 0; j < ny; j++)    
    {
       for(int i = 0; i < nx; i++)
       {
           n_2D[i][j].x = coords_2D[j * nx + i][0];
           n_2D[i][j].y = coords_2D[j * nx + i][1];
        }
    }

    std::cout<<"--2D coords have been transformed and assigned to n_2D"<<"\n\n";
//   std::cout<<"--[0,0] Grid Value x and y : "<<n_2D[0][0].x<<" "<<n_2D[0][0].y<<std::endl;
//   std::cout<<"--[1,1] Grid Value x and y : "<<n_2D[0][1].x<<" "<<n_2D[0][1].y<<std::endl;
//   std::cout<<"--[1,2] Grid Value x and y : "<<n_2D[0][2].x<<" "<<n_2D[0][2].y<<std::endl;
}

/* Parameters required:
 * -------------------
 *  None
 *
 *  Adds halo cells and computes all metrics
 */

void Grid::ComputeMetrics(int dim)
{
    if(dim == 2)
    {
         AddHaloCells_2D(); 
         //ComputeCellVol();
         ComputeProjCellFaceArea();
    }

}


/*Parameters required:
 * ------------------
 * None, calls values from the object of Grid class 
 *
 * Add halo cells
 */

void Grid::AddHaloCells_2D()
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
        std::cout<<"--Column value assignment is fine!"<<std::endl;
   
//       //Assigning row values
        for(size_t j = 0; j < cols; j++)
        {
            
            n_g_2D[0][j+1].y = 2*n_2D[0][j].y - n_2D[1][j].y;
            n_g_2D[rows_g - 1][j + 1].y = 2*n_2D[rows - 1][j].y - 
                                                       n_2D[rows - 2][j].y; 

            n_g_2D[0][j+1].x = 2*n_2D[0][j].x - n_2D[1][j].x;
            n_g_2D[rows_g - 1][j + 1].x = 2*n_2D[rows - 1][j].x - 
                                                       n_2D[rows - 2][j].x; 
        }
        std::cout<<"--Row value assignment is fine!"<<std::endl;

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
        n_g_2D[0][cols_g - 1].x = 2*n_g_2D[0][cols_g - 2].x 
                                           - n_g_2D[0][cols_g - 3].x;
        n_g_2D[0][cols_g - 1].y = 2*n_g_2D[0][cols_g - 2].y 
                                           - n_g_2D[0][cols_g - 3].y;
        
        //Bottom Left
        n_g_2D[rows_g - 1][0].x = 2*n_g_2D[rows_g - 1][1].x - n_g_2D[rows_g - 1][2].x;
        n_g_2D[rows_g - 1][0].y = 2*n_g_2D[rows_g - 1][1].y - n_g_2D[rows_g - 1][2].y;
        
        //Bottom Right
        n_g_2D[rows_g - 1][cols_g - 1].x = 2*n_g_2D[rows_g - 1][cols_g - 2].x - n_g_2D[rows_g - 1][cols_g - 3].x;
        n_g_2D[rows_g - 1][cols_g - 1].y = 2*n_g_2D[rows_g - 1][cols_g - 2].y - n_g_2D[rows_g - 1][cols_g - 3].y;


//       std::cout<<"--[1,0] Ghost Grid value x and y : "<<n_g_2D[1][0].x<<" "<<n_g_2D[1][0].y<<std::endl;
//       std::cout<<"--[1,1] Ghost Grid value x and y : "<<n_g_2D[1][1].x<<" "<<n_g_2D[1][1].y<<std::endl;
//       std::cout<<"--[1,2] Ghost Grid value x and y : "<<n_g_2D[1][2].x<<" "<<n_g_2D[1][2].y<<std::endl;
        std::cout<<"--Ghost cells have been added"<<"\n\n"; 
        
        exportGridToCSV(n_g_2D, "n_g_2D.csv");
        exportGridToCSV(n_2D, "n_2D.csv");
        std::cout<<std::endl;
}

/*Parameters Required:
 * ------------------
 *
 *Computes the projected cell face area
 */

void Grid::ComputeProjCellFaceArea()
{
    allocate_2D(nx + 2, ny + 2, cc_2D);
    std::cout<<"--CC allocation has been done!"<<std::endl;

    //Cell face allocation for face perpendicular to ξ
    allocate_2D(nx, ny - 1, cf_xi_2D);
    std::cout<<"--CF allocation perpendicular to ξ has been done!"<<std::endl;
    
    //Cell face allocation for face perpendicular to η
    allocate_2D(nx - 1, ny, cf_eta_2D);
    std::cout<<"--CF allocation perpendicular to η has been done!"<<std::endl;

//   std::cout<<"--Size of n_2D: "<<n_2D.size()<<" "<<n_2D[0].size();
//   std::cout<<"\n--Size of cf_xi_2D: "<<cf_xi_2D.size()<<" "<<cf_xi_2D[0].size()<<std::endl;

    double x_eta, y_eta;
    for(size_t i = 0; i < cf_xi_2D.size(); i++)
    {
        for(size_t j = 0; j < cf_xi_2D[0].size(); j++)
        {
            x_eta = n_2D[i + 1][j].x - n_2D[i][j].x;     
            y_eta = n_2D[i + 1][j].y - n_2D[i][j].y;      
            
            cf_xi_2D[i][j] = std::sqrt(x_eta * x_eta + y_eta * y_eta);
        }
  
    }  
  
    std::cout<<"--Projected Cell face areas have been computed!"<<std::endl;
        
    double x_xi, y_xi;
    for(size_t j = 0; j < cf_eta_2D[0].size(); j++)
    {
        for(size_t i = 0; i < cf_eta_2D.size(); i++)
        {
            x_xi = n_2D[i][j + 1].x - n_2D[i][j].x;     
            y_xi = n_2D[i][j + 1].y - n_2D[i][j].y;      
            
            cf_eta_2D[i][j] = std::sqrt(x_xi * x_xi + y_xi * y_xi);
        }
  
    }  
    
    std::cout<<"--Projected Cell face areas have been computed!"<<std::endl;

}
