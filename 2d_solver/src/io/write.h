#ifndef CFD_IO_WRITE_H
#define CFD_IO_WRITE_H

#include <iostream>
#include <fstream>
#include <string>

#include "grid.h"
#include "primitiveVar.h"

void exportGridToCSV(const std::vector<std::vector<Point>>& pt, std::string fpath);
void exportScalarFieldToCSV(const std::vector<std::vector<double>>& field, const std::string& fpath);
void exportprimitiveVartoCSV(const std::vector<std::vector<primitiveVar>>& field, const std::string& fpath);

#endif
