#ifndef CFD_IO_READ_GRID_H
#define CFD_IO_READ_GRID_H

#include <iostream>
#include <vector>
#include <string>

void grid_read(
	std::string fpath,
	std::vector<std::vector<double>>& coords_2D,
	int& nx,
	int& ny
);

#endif 
