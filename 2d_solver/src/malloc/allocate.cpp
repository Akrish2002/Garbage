#include "allocate.h"

#include <iostream>
#include <vector>

//Maybe add a std::cout for error in allocation and/or initialization

/*Parameters required:
 * ------------------
 *  int         r       : Rows
 *  int         c       : Columns
 *  double**    grid    : 2D array of pointers for 2D grid
 */
void allocate_2D(int r, int c, std::vector<std::vector<Point>>& grid_2D)
{
   	//Resizing grid to r and c and initializing with zero values
	grid_2D.assign(r, std::vector<Point>(c, {0.0, 0.0}));
}

