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
#include "grid.h"


void Grid::computeMetrics(int dim)
{
    if(dim == 2)
    {
        computeProjCellFaceArea();
        avgtoCellCenter();
        computeCellVol();
    }

}


/*Parameters Required:
 * ------------------
 *
 *Computes the projected cell face area
 */
void Grid::computeProjCellFaceArea()
{

    //Cell face allocation for face perpendicular to ξ
    allocate_2D(ny - 1, nx, S_xi_2D);
    allocate_2D(ny - 1, nx, S_xi_x_2D);
    allocate_2D(ny - 1, nx, S_xi_y_2D);
    std::cout<<"--CF allocation perpendicular to ξ is done!"<<std::endl;
    
    //Cell face allocation for face perpendicular to η
    allocate_2D(ny, nx - 1, S_eta_2D);
    allocate_2D(ny, nx - 1, S_eta_x_2D);
    allocate_2D(ny, nx - 1, S_eta_y_2D);
    std::cout<<"--CF allocation perpendicular to η is done!"<<std::endl;

//    std::cout<<"--Size of n_2D: "<<n_2D.size()<<" "<<n_2D[0].size();
//    std::cout<<"\n--Size of S_xi_2D: "<<S_xi_2D.size()<<" "<<S_xi_2D[0].size()<<std::endl;

    double x_eta, y_eta;
    for(size_t i = 0; i < S_xi_2D.size() - 1; i++)
    {
        for(size_t j = 0; j < S_xi_2D[0].size(); j++)
        {
            x_eta = n_2D[i + 1][j].x - n_2D[i][j].x;     
            y_eta = n_2D[i + 1][j].y - n_2D[i][j].y;      
            
            S_xi_x_2D[i][j] =  1 * y_eta;
            S_xi_y_2D[i][j] = -1 * x_eta;
            S_xi_2D[i][j] = std::sqrt(x_eta * x_eta + y_eta * y_eta);
        }
  
    }  
  
    double x_xi, y_xi;
    for(size_t j = 0; j < S_eta_2D[0].size() - 1; j++)
    {
        for(size_t i = 0; i < S_eta_2D.size(); i++)
        {
            x_xi = n_2D[i][j + 1].x - n_2D[i][j].x;     
            y_xi = n_2D[i][j + 1].y - n_2D[i][j].y;      

            S_eta_x_2D[i][j] = -1 * y_xi;
            S_eta_y_2D[i][j] =  1 * x_xi;
            S_eta_2D[i][j] = std::sqrt(x_xi * x_xi + y_xi * y_xi);
        }
  
    }  
    
    std::cout<<"--Projected Cell face areas have been computed!"<<std::endl;
    //exportScalarFieldToCSV(S_xi_2D, "S_xi_2D.csv");
    //exportScalarFieldToCSV(S_eta_2D, "S_eta_2D.csv");
    std::cout<<std::endl;
}


void Grid::avgtoCellCenter()
{
    //Should give me struct point initialized with zeros
    //Allocating -1 since centered values 
    allocate_2D(ny - 1, nx - 1, cc_xi_eta_2D);
    std::cout<<"--CC allocation has been done!"<<std::endl;

    //To compute x and y center values
    allocate_2D(ny - 1, nx - 1, nc_2D);
    std::cout<<"--NC allocation has been done!"<<std::endl;

    //To compute x_g and y_g center values
    allocate_2D(ny + 1, nx + 1, nc_g_2D);
    std::cout<<"--NC_G allocation has been done!"<<std::endl;

//   std::cout<<"--Nx and Ny values: "<<nx<<" "<<ny<<std::endl; 
//   std::cout<<"--n_2D sizes: "<<n_2D.size()<<" "<<n_2D[0].size()<<std::endl; 
//   std::cout<<"--CC sizes: "<<cc_xi_eta_2D.size()<<" "<<cc_xi_eta_2D[0].size()<<std::endl; 
//   std::cout<<"--CF xi sizes: "<<S_xi_2D.size()<<" "<<S_xi_2D[0].size()<<std::endl; 
//   std::cout<<"--CF eta sizes: "<<S_eta_2D.size()<<" "<<S_eta_2D[0].size()<<std::endl; 

    //S_xi avg
    for(size_t i = 0; i < S_xi_2D.size(); i++)
    {
        for(size_t j = 0; j < S_xi_2D[0].size() - 1; j++)
        {
            cc_xi_eta_2D[i][j].x = (S_xi_2D[i][j + 1] + S_xi_2D[i][j]) * 0.5;
            nc_2D[i][j].x = (n_2D[i][j + 1].x + n_2D[i][j].x) * 0.5;
        }
    }


    //S_eta avg
    for(size_t j = 0; j < S_eta_2D[0].size(); j++)
    {
        for(size_t i = 0; i < S_eta_2D.size() - 1; i++)
        {
            cc_xi_eta_2D[i][j].y = (S_eta_2D[i + 1][j] + S_eta_2D[i][j]) * 0.5;
            nc_2D[i][j].y = (n_2D[i + 1][j].y + n_2D[i][j].y) * 0.5;
        }
    }
   

    //Centered x ghost values
    for(size_t i = 0; i < nc_g_2D.size(); i++)
    {
        for(size_t j = 0; j < nc_g_2D[0].size(); j++)
        {
            nc_g_2D[i][j].x = (n_g_2D[i][j + 1].x + n_g_2D[i][j].x) * 0.5;
        }
    }
    

    //Centered y ghost values
    for(size_t j = 0; j < nc_g_2D[0].size(); j++)
    {
        for(size_t i = 0; i < nc_g_2D.size(); i++)
        {
            nc_g_2D[i][j].y = (n_g_2D[i + 1][j].y + n_g_2D[i][j].y) * 0.5;
        }
    }

    exportGridToCSV(nc_2D, "CellCenteredNodes.csv");
    exportGridToCSV(nc_g_2D, "CellCenteredGhostNodes.csv");
    exportGridToCSV(cc_xi_eta_2D, "AvgCellCentered.csv");

    std::cout<<std::endl;
}


/*Parameters required
 * ------------------
 *  None
 *
 *  Computes cell vol
 */
void Grid::computeCellVol()
{
    //Allocating memory for vol storage at cell centers
    allocate_2D(ny + 1, nx + 1, cc_vol_2D);

    std::cout<<"--Allocation done for volume storage!"<<std::endl;
       
    for(size_t i = 0; i < ny + 1; i++)
    {
        for(size_t j = 0; j < nx + 1; j++)
        {
            double a = (n_g_2D[i + 1][j + 1].x - n_g_2D[i][  j  ].x);
            double b = (n_g_2D[i + 1][j + 1].y - n_g_2D[i][  j  ].y);
            double c = (n_g_2D[i + 1][  j  ].x - n_g_2D[i][j + 1].x);
            double d = (n_g_2D[i + 1][  j  ].y - n_g_2D[i][j + 1].y);

            cc_vol_2D[i][j] = 0.5 * std::abs(a * d - c * b);
        }
    }

    std::cout<<"--Computed cell volume!"<<std::endl;
    exportScalarFieldToCSV(cc_vol_2D, "CellVol_2D.csv");
    
    std::cout<<std::endl;
} 
