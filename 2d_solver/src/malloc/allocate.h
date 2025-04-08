#ifndef CFD_MALLOC_ALLOCATE_H
#define CFD_MALLOC_ALLOCATE_H

#include "grid.h"

#include <vector>

/*Parameters required:
 * ------------------
 *  int         r       : Rows
 *  int         c       : Columns
 *  double**    grid    : 2D array of pointers for 2D grid
 *
 *  Capable of handling both Point and double
 */

template <typename T>
void allocate_2D(int r, int c, std::vector<std::vector<T>>& pt, const T& init_val = T())
{
   	//Resizing grid to r and c and initializing with zero values
	pt.assign(r, std::vector<T>(c, init_val));
}

#endif

