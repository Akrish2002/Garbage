#include "grid_read.h"
#include "allocate.h"

#include <iostream>
#include <vector>

/* Main file for testing/running the case
 *
 *
 */

int main()
{
	std::vector<std::vector<double>> twoD_grid_coords;
	std::vector<std::vector<double>> grid; 	
	int nx, ny;

	std::string fpath = "g641x065uf";
	
	read_grid(fpath, twoD_grid_coords, nx, ny);
	std::cout<<"nx: "<<nx<<std::endl<<"ny: "<<ny<<std::endl;
	
	allocate2D(nx, ny, grid);
	std::cout<<"Grid[0][0]: "<<grid[0][0]<<std::endl;	
	
	return 0;
}
