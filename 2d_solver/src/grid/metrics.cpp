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
        //ComputeCellVol();
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
    allocate_2D(ny - 1, nx, cf_xi_2D);
    std::cout<<"--CF allocation perpendicular to ξ is done!"<<std::endl;
    
    //Cell face allocation for face perpendicular to η
    allocate_2D(ny, nx - 1, cf_eta_2D);
    std::cout<<"--CF allocation perpendicular to η is done!"<<std::endl;

//    std::cout<<"--Size of n_2D: "<<n_2D.size()<<" "<<n_2D[0].size();
//    std::cout<<"\n--Size of cf_xi_2D: "<<cf_xi_2D.size()<<" "<<cf_xi_2D[0].size()<<std::endl;

    double x_eta, y_eta;
    for(size_t i = 0; i < cf_xi_2D.size() - 1; i++)
    {
        for(size_t j = 0; j < cf_xi_2D[0].size(); j++)
        {
            x_eta = n_2D[i + 1][j].x - n_2D[i][j].x;     
            y_eta = n_2D[i + 1][j].y - n_2D[i][j].y;      
            
            cf_xi_2D[i][j] = std::sqrt(x_eta * x_eta + y_eta * y_eta);
        }
  
    }  
  
    double x_xi, y_xi;
    for(size_t j = 0; j < cf_eta_2D[0].size() - 1; j++)
    {
        for(size_t i = 0; i < cf_eta_2D.size(); i++)
        {
            x_xi = n_2D[i][j + 1].x - n_2D[i][j].x;     
            y_xi = n_2D[i][j + 1].y - n_2D[i][j].y;      
            
            cf_eta_2D[i][j] = std::sqrt(x_xi * x_xi + y_xi * y_xi);
        }
  
    }  
    
    std::cout<<"--Projected Cell face areas have been computed!\n"<<std::endl;
    //exportScalarFieldToCSV(cf_xi_2D, "cf_xi_2D.csv");
    //exportScalarFieldToCSV(cf_eta_2D, "cf_eta_2D.csv");
    std::cout<<std::endl;
}


void Grid::avgtoCellCenter()
{
    //Should give me struct point initialized with zeros
    //Allocating -1 since centered values 
    allocate_2D(ny - 1, nx - 1, cc_2D);
    std::cout<<"--CC allocation has been done!"<<std::endl;

    //To compute x and y center values
    allocate_2D(ny - 1, nx - 1, nc_2D);
    std::cout<<"--NC allocation has been done!"<<std::endl;

//   std::cout<<"--Nx and Ny values: "<<nx<<" "<<ny<<std::endl; 
//   std::cout<<"--n_2D sizes: "<<n_2D.size()<<" "<<n_2D[0].size()<<std::endl; 
//   std::cout<<"--CC sizes: "<<cc_2D.size()<<" "<<cc_2D[0].size()<<std::endl; 
//   std::cout<<"--CF xi sizes: "<<cf_xi_2D.size()<<" "<<cf_xi_2D[0].size()<<std::endl; 
//   std::cout<<"--CF eta sizes: "<<cf_eta_2D.size()<<" "<<cf_eta_2D[0].size()<<std::endl; 

    //S_xi avg
    for(size_t i = 0; i < cf_xi_2D.size(); i++)
    {
        for(size_t j = 0; j < cf_xi_2D[0].size() - 1; j++)
        {
            cc_2D[i][j].x = (cf_xi_2D[i][j + 1] + cf_xi_2D[i][j]) * 0.5;
            nc_2D[i][j].x = (n_2D[i][j + 1].x + n_2D[i][j].x) * 0.5;
        }
    }


    //S_eta avg
    for(size_t j = 0; j < cf_eta_2D[0].size(); j++)
    {
        for(size_t i = 0; i < cf_eta_2D.size() - 1; i++)
        {
            cc_2D[i][j].y = (cf_eta_2D[i + 1][j] + cf_xi_2D[i][j]) * 0.5;
            nc_2D[i][j].y = (n_2D[i + 1][j].y + n_2D[i][j].y) * 0.5;
        }
    }
    
    exportGridToCSV(nc_2D, "CellCenteredNodes.csv");
    exportGridToCSV(cc_2D, "AvgCellCentered.csv");
    std::cout<<std::endl;
}
