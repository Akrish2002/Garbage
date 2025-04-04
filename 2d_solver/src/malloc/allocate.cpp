#include "allocate.h"

#include <iostream>
#include <vector>

/*Parameters required:
 * ------------------
 *  int         r       : Rows
 *  int         c       : Columns
 *  double**    grid    : 2D array of pointers for 2D grid
 */


//Maybe add a std::cout for error in allocation and/or initialization

void allocate2D(int r, int c, std::vector<std::vector<double>>& grid)
{
    	//Resizing grid to r and c and initializing with zero values
	grid.assign(r, std::vector<double>(c, 0.0));
    
}
