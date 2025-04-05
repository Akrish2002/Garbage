#ifndef CFD_IO_READ_H
#define CFD_IO_READ_H

#include <iostream>
#include <vector>
#include <string>

void read(
	std::string fpath,
	std::vector<std::vector<double>>& coords_2D,
	int& nx,
	int& ny
);

#endif 
