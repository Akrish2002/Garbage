#include "read.h"
#include "allocate.h"
#include "grid.h"

#include <iostream>
#include <vector>

/* Main file for testing/running the case
 *
 *
 */

int main()
{
    
	std::string fpath = "g641x065uf";
	
    Grid grid(fpath);
    grid.addHaloCells_2D();
	return 0;
}
