#include "write.h"

#include <iostream>
#include <fstream>
#include <string>

#include "grid.h"

void exportGridToCSV(const std::vector<std::vector<Point>>& grid, std::string fpath) 
{
    std::ofstream file(std::string("output/CSV/") + fpath);
    if (!file.is_open()) 
        {
            std::cerr << "Error opening file: " << fpath << std::endl;
            return;
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
    std::cout << "--CSV export done for: " << fpath << std::endl;
}

void exportScalarFieldToCSV(const std::vector<std::vector<double>>& field, const std::string& fpath) 
{
    std::ofstream file(std::string("output/CSV/") + fpath);
    if (!file.is_open()) 
    {
        std::cerr << "Error opening file: " << fpath << std::endl;
        return;
    }

    for (const auto& row : field) 
    {
        for (size_t j = 0; j < row.size(); ++j) 
        {
            file << row[j];
            //if (j < row.size() - 1) file << ",";
            file << "\n";
        }
        //file << "\n";
    }

    file.close();
    std::cout << "--CSV export done for: " << fpath << std::endl;
}


void exportprimitiveVartoCSV(const std::vector<std::vector<primitiveVar>>& field, const std::string& fpath, int nx, int ny, int BC)
{
    std::ofstream file(std::string("output/CSV/") + fpath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fpath << '\n';
        return;
    }

    if(BC == 0)
    {
        const size_t rows = ny ;
        const size_t cols = nx ;

        //file << "rho,u,v,T,P\n";
        for (size_t i = 1; i < rows; ++i) {
            for (size_t j = 1; j < cols; ++j) {
                const primitiveVar& V = field[i][j];
                file << V.rho << ','
                     << V.u   << ','
                     << V.v   << ','
                     << V.T   << ','
                     << V.P   << '\n';
            }
        }
    }

    if(BC == 1)
    {
        const size_t rows = ny + 1 ;
        const size_t cols = nx + 1;

        //file << "rho,u,v,T,P\n";
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                const primitiveVar& V = field[i][j];
                file << V.rho << ','
                     << V.u   << ','
                     << V.v   << ','
                     << V.T   << ','
                     << V.P   << '\n';
            }
        }
    }

    file.close();
    std::cout << "--CSV export done for: " << fpath << '\n';
}
