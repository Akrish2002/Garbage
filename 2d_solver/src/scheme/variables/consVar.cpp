#include "consVar.h"

#include <vector>
#include <string>
#include <iostream>
#include <array>

//Performing operation overloading

//------------------------------------------------------------------------------
//Addition overloading
//1. consVar + consVar
consVar operator+(const consVar& a, const consVar& b)
{
    return consVar 
    {
        a.rho + b.rho,
        a.rho_u + b.rho_u,
        a.rho_v + b.rho_v,
        a.rho_et + b.rho_et
   };
} 

//------------------------------------------------------------------------------
//Subtraction overloading
//1. consVar - consVar
consVar operator-(const consVar& a, const consVar& b)
{
    return consVar 
    {
        a.rho - b.rho,
        a.rho_u - b.rho_u,
        a.rho_v - b.rho_v,
        a.rho_et - b.rho_et
   };
} 

//------------------------------------------------------------------------------
//Equalto  overloading
//1. consVar = consVar
consVar consVar::operator=(const consVar& b)
{

    rho    = b.rho;
    rho_u  = b.rho_u;
    rho_v  = b.rho_v;
    rho_et = b.rho_et;

    return *this;
} 

//------------------------------------------------------------------------------
//Multiplication overload
//1. double * consVar
consVar operator*(double a, const consVar& b)
{

    return consVar
    {
        a * b.rho,
        a * b.rho_u,
        a * b.rho_v,
        a * b.rho_et
    };
} 

//2. consVar * consVar
consVar operator*(const consVar& a, const consVar& b)
{

    return consVar
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
//1. consVar / consVar
consVar operator/(const consVar& a, const consVar& b)
{

    if (b.rho == 0.0) std::cout<<"rho division by zero";
    if (b.rho_u == 0.0) std::cout<<"rho division by zero";
    if (b.rho_v == 0.0) std::cout<<"rho division by zero";
    if (b.rho_et == 0.0) std::cout<<"rho division by zero";
     
    return consVar 
    {
        a.rho /  b.rho,
        a.rho_u / b.rho_u,
        a.rho_v / b.rho_v,
        a.rho_et / b.rho_et
   };
} 

//2. double / consVar
consVar operator/(double a, const consVar& b)
{

    if (b.rho == 0.0) std::cout<<"rho division by zero";
    if (b.rho_u == 0.0) std::cout<<"rho division by zero";
    if (b.rho_v == 0.0) std::cout<<"rho division by zero";
    if (b.rho_et == 0.0) std::cout<<"rho division by zero";
     
    return consVar 
    {
        a /  b.rho,
        a / b.rho_u,
        a / b.rho_v,
        a / b.rho_et
   };
}

//3. consVar/double
consVar operator/(const consVar& a, double b)
{

    if (b == 0.0) std::cout<<"rho division by zero";

    return consVar 
    {
        a.rho  / b ,
        a.rho_u / b ,
        a.rho_v / b ,
        a.rho_et / b
   };
} 
