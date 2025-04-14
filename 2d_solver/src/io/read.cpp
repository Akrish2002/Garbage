#include "read.h"

#include <fstream> //To read and write from files
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

void read(   
    std::string fpath, 
    std::vector<std::vector<double>>& coords_2D, 
    int& nx, 
    int& ny)
{

    std::string row;
    std::string item;
    char seperator = ',';
    std::vector<double> grid_size; //Dynamic to append value

    double L = 15.0e-3; //0.015 m
    
    std::string fname = fpath + ".dat"; 
    std::ifstream grid_file(fname);
    std::cout<<"\n--Reading file"<<std::endl;

    if(!grid_file.is_open()){
        std::cerr<<"Error opening file"<<std::endl;
    }

    //Reading first line
    std::getline(grid_file, row);
    std::stringstream ss(row);

    while(std::getline(ss, item, seperator)){
        grid_size.push_back(stof(item));
    }

    //std::cout<<grid_coords[0]<<std::endl<<grid_coords[1]<<std::endl;
    
    nx = (int) grid_size[0];
    ny = (int) grid_size[1];   
    
    //Running through all coordinates
    //Dimensionalizing them by *L
    while(std::getline(grid_file, row))
    {
        std::vector<double> coords_1D;
        std::stringstream ss(row);
        while(std::getline(ss, item, seperator)) coords_1D.push_back(stof(item)*L);

        //Add it to the 2D vector  
        coords_2D.push_back(coords_1D);

    }   
    
    grid_file.close();
//   std::cout<<"--Coord_2D size: "<<coords_2D.size()<<" "<<coords_2D[0].size()<<std::endl;
//   std::cout<<"--Grid_2D size: "<<nx<<" "<<ny<<std::endl;
    std::cout<<"--Finished reading file "<<"\n\n";

}
