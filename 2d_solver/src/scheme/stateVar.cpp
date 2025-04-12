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
    return stateVar 
    {
        a.rho + b.rho,
        a.rho_u + b.rho_u,
        a.rho_v + b.rho_v,
        a.rho_et + b.rho_et
   };
} 

//------------------------------------------------------------------------------
//Subtraction overloading
//1. stateVar - stateVar
stateVar operator-(const stateVar& a, const stateVar& b)
{
    return stateVar 
    {
        a.rho - b.rho,
        a.rho_u - b.rho_u,
        a.rho_v - b.rho_v,
        a.rho_et - b.rho_et
   };
} 

//------------------------------------------------------------------------------
//Equalto  overloading
//1. stateVar = stateVar
stateVar stateVar::operator=(const stateVar& b)
{

    rho    = b.rho;
    rho_u  = b.rho_u;
    rho_v  = b.rho_v;
    rho_et = b.rho_et;

    return *this;
} 

//------------------------------------------------------------------------------
//Multiplication overload
//1. double * stateVar
stateVar operator*(double a, const stateVar& b)
{

    return stateVar
    {
        a * b.rho,
        a * b.rho_u,
        a * b.rho_v,
        a * b.rho_et
    };
} 

//2. stateVar * stateVar
stateVar operator*(const stateVar& a, const stateVar& b)
{

    return stateVar
    {
        a.rho * b.rho,
        a.rho_u * b.rho_u,
        a.rho_v * b.rho_v,
        a.rho_et * b.rho_et
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
     
    return stateVar 
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
     
    return stateVar 
    {
        a /  b.rho,
        a / b.rho_u,
        a / b.rho_v,
        a / b.rho_et
   };
}

//3. stateVar/double
stateVar operator/(const stateVar& a, double b)
{

    if (b == 0.0) std::cout<<"rho division by zero";

    return stateVar 
    {
        a.rho  / b ,
        a.rho_u / b ,
        a.rho_v / b ,
        a.rho_et / b
   };
} 
