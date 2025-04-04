#ifndef CFD_IO_READ_GRID_H
#define CFD_IO_READ_GRID_H

#include <iostream>
#include <vector>
#include <string>

void read_grid(
	std::string fpath,
	std::vector<std::vector<double>>& twoD_grid_coords,
	int& nx,
	int& ny
);

#endif 
