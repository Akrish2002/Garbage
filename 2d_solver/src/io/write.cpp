#include "write.h"

#include <iostream>
#include <fstream>
#include <string>

#include "grid.h"

void exportGridToCSV(std::vector<std::vector<Point>> grid, std::string fpath) 
{
    std::string fname = fpath + ".dat";
    std::ofstream file(fname);
    if (!file.is_open()) 
        {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }
}

    size_t rows = grid.size();
    size_t cols = grid[0].size();
   
    for (size_t i = 0; i < rows; ++i) 
    {
        for (size_t j = 0; j < cols; ++j) 
        {
            file << grid[i][j].x << "," << grid[i][j].y << "\n";
        }
    }

    file.close();
    std::cout << "--CSV export complete: " << filename << std::endl;
}

