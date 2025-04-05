#ifndef CFD_IO_WRITE_H
#define CFD_IO_WRITE_H

#include <iostream>
#include <fstream>
#include <string>

#include "grid.h"

void exportGridToCSV(const std::vector<std::vector<Point>>& grid, std::string fpath);

#endif
