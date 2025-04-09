#include "debug.h"

#include <vector>
#include<iostream>


void D_GridConstructer(std::vector<std::vector<Point>>& n_2D, int d)
{

   if(d !=0)
    {
        std::cout<<"--[0,0] Grid Value x and y : "<<n_2D[0][0].x<<" "<<n_2D[0][0].y<<std::endl;
        std::cout<<"--[1,1] Grid Value x and y : "<<n_2D[0][1].x<<" "<<n_2D[0][1].y<<std::endl;
        std::cout<<"--[1,2] Grid Value x and y : "<<n_2D[0][2].x<<" "<<n_2D[0][2].y<<std::endl;
     }
}

void D_AddHaloCells(std::vector<std::vector<Point>>& n_g_2D, int d)
{

   if(d !=0)
    {
        std::cout<<"--[1,0] Ghost Grid value x and y : "<<n_g_2D[1][0].x<<" "<<n_g_2D[1][0].y<<std::endl;
        std::cout<<"--[1,1] Ghost Grid value x and y : "<<n_g_2D[1][1].x<<" "<<n_g_2D[1][1].y<<std::endl;
        std::cout<<"--[1,2] Ghost Grid value x and y : "<<n_g_2D[1][2].x<<" "<<n_g_2D[1][2].y<<std::endl;
        std::cout<<"--[1,3] Ghost Grid value x and y : "<<n_g_2D[1][3].x<<" "<<n_g_2D[1][3].y<<std::endl;
        
        std::cout<<"--n_g_2D sizes: "<<n_g_2D.size()<<" "<<n_g_2D[0].size()<<std::endl; 

     }
}
