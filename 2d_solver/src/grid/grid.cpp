#include "grid.h"

#include <vector>
#include <iostream>
#include <string>
#include <array>

//Including functions to perform read, write of grid files
#include "grid_read.cpp"
//#include "grid_write.cpp"
//#include "grid_metrics.cpp"

/* Constructor to read grid file
 *
 * Parameters:
 * -----------
 *  string cfpath : relative path + filename of grid file.
 *
 */

Grid:Grid(std::string file, int nhc, bool write)
{

    m_file = file;
    
    read_grid(m_file, m_coords, m_nx, m_ny);

    //Allocating memory
    allocate3D

} 
