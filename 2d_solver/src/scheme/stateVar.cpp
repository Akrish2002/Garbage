#include "stateVar.h"

#include <vector>
#include <string>
#include <iostream>
#include <array>

//Performing operation overloading

//------------------------------------------------------------------------------
//Addition overloading
//1. stateVar + stateVar
stateVar operator+(const stateVar& a, const stateVar& b)
{
    return 
    {
        a.rho + b.rho,
        a.rho_u + b.rho_u,
        a.rho_v + b.rho_v,
        a.rho_et + b.rho_et
   };
} 

//------------------------------------------------------------------------------
//Multiplication overload
//1. double * stateVar
stateVar operator*(double a, const stateVar& b)
{

    return
    {
        a * b.rho,
        a * b.rho_u,
        a * b.rho_v,
        a * b.rho_et
    };
} 

//------------------------------------------------------------------------------
//Division overload
//Use assert to check for dividing by zeros
//1. stateVar / stateVar
stateVar operator/(const stateVar& a, const stateVar& b)
{

    if (b.rho == 0.0) std::cout<<"rho division by zero";
    if (b.rho_u == 0.0) std::cout<<"rho division by zero";
    if (b.rho_v == 0.0) std::cout<<"rho division by zero";
    if (b.rho_et == 0.0) std::cout<<"rho division by zero";
     
    return 
    {
        a.rho /  b.rho,
        a.rho_u / b.rho_u,
        a.rho_v / b.rho_v,
        a.rho_et / b.rho_et
   };
} 

//2. double / stateVar
stateVar operator/(double a, const stateVar& b)
{

    if (b.rho == 0.0) std::cout<<"rho division by zero";
    if (b.rho_u == 0.0) std::cout<<"rho division by zero";
    if (b.rho_v == 0.0) std::cout<<"rho division by zero";
    if (b.rho_et == 0.0) std::cout<<"rho division by zero";
     
    return 
    {
        a /  b.rho,
        a / b.rho_u,
        a / b.rho_v,
        a / b.rho_et
   };
}

//3. stateVar/double
stateVar operator/(const stateVar& b, double a)
{

    if (a == 0.0) std::cout<<"rho division by zero";

    return 
    {
        b.rho  / a ,
        b.rho_u / a ,
        b.rho_v / a ,
        b.rho_et / a
   };
} 
