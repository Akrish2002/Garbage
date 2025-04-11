#include "read.h"
#include "allocate.h"
#include "grid.h"
#include "write.h"

#include <iostream>
#include <vector>

/* Main file for testing/running the case
 *
 *
 */

int main()
{

    std::string fpath = "data/g641x065uf";
	
    Grid grid(fpath);
    grid.addHaloCells_2D();

    grid.computeMetrics(2);
	
    return 0;
}
