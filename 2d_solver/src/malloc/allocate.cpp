#include "allocate.h"

#include <iostream>
#include <vector>

/*Parameters required:
 * ------------------
 *  int         nrows   : Rows
 *  int         ncols   : Columns
 *  double**    grid    : 2D array of pointers for 2D grid
 */


int main(int &r, int &c, const std::vector<std::vector<double>> &grid)
{
    int r, c;
    r = 5;
    c = 5;
    std::vector<std::vector<double>> grid(r, std::vector<double>(c, 0.0));
    
    return 0;
}
