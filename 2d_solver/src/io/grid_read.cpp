#include <fstream> //To read and write from files
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

void read_grid(   
    std::string fpath, 
    std::vector<std::vector<double>>& twoD_grid_coords, 
    int& nx, 
    int& ny)
{

    std::string row;
    std::string item;
    char seperator = ',';
    std::vector<double> grid_coords; //Dynamic to append value
    
    std::string fname = fpath + ".dat"; 
    std::ifstream grid_file(fname);
    std::cout<<"Reading file"<<std::endl;

    if(!grid_file.is_open()){
        std::cerr<<"Error opening file"<<std::endl;
    }

    //Reading first line
    std::getline(grid_file, row);
    std::stringstream ss(row);

    while(std::getline(ss, item, seperator)){
        grid_coords.push_back(stof(item));
    }

    //std::cout<<grid_coords[0]<<std::endl<<grid_coords[1]<<std::endl;
    
    nx = (int) grid_coords[0];
    ny = (int) grid_coords[1];   
    
    //Running through all coordinates
    while(std::getline(grid_file, row))
    {
        std::vector<double> grid_coords;
        std::stringstream ss(row);
        while(std::getline(ss, item, seperator)) grid_coords.push_back(stof(item));

        //Add it to the 2D vector  
        twoD_grid_coords.push_back(grid_coords);

    }   
    
    grid_file.close();
    std::cout<<"Finished reading file "<<std::endl;

}
