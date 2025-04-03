#include <fstream> //To read and write from files
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main(){

    std::string row;
    std::string item;
    char seperator = ',';
    std::vector<double> grid_coords; //Dynamic to append value

    std::ifstream grid_file("g641x065uf.dat");
    std::cout<<"Reading file";

    if(!grid_file.is_open()){
        std::cerr<<"Error opening file"<<std::endl;
        return 1;
    }

    //Reading first line
    std::getline(grid_file, row);
    std::stringstream ss(row);

    while(std::getline(ss, item, seperator)){
        grid_coords.push_back(std::stod(item));
    }

    //std::cout<<grid_coords<<std::endl;

    return 0;
}
