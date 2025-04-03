#include "allocate.h"

#include <iostream>
#include <vector>

/*Parameters required:
 * ------------------
 *  int         r   : Rows
 *  int         c   : Columns
 *  double**    grid    : 2D array of pointers for 2D grid
 */


void allocate2D(int r, int c, const std::vector<std::vector<double>>& grid)
{
    std::vector<std::vector<double>> grid(r, std::vector<double>(c, 0.0));
    
}
