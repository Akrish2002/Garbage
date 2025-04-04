#include "grid_read.h"
#include "allocate.h"
#include "grid.h"

#include <vector>
#include <iostream>
#include <string>
#include <array>


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
    std::cout<<grid_2D[1][1]<<std::endl;
}


void addHaloCells()
{
    



} 
