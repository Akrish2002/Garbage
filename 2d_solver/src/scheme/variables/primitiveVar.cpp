#include "primitiveVar.h"

#include <vector>
#include <string>
#include <iostream>
#include <array>

//Performing operation overloading

//------------------------------------------------------------------------------
//Addition overloading
//1. primitiveVar + primitiveVar
primitiveVar operator+(const primitiveVar& a, const primitiveVar& b)
{
    return primitiveVar 
    {
        a.rho + b.rho,
        a.u + b.u,
        a.v + b.v,
        a.et + b.et
        a.h + b.h,
        a.P + b.P,
   };
} 

//------------------------------------------------------------------------------
//Subtraction overloading
//1. primitiveVar - primitiveVar
primitiveVar operator-(const primitiveVar& a, const primitiveVar& b)
{
    return primitiveVar 
    {
        a.rho - b.rho,
        a.rho_u - b.rho_u,
        a.rho_v - b.rho_v,
        a.rho_et - b.rho_et
   };
} 

//------------------------------------------------------------------------------
//Equalto  overloading
//1. primitiveVar = primitiveVar
primitiveVar primitiveVar::operator=(const primitiveVar& b)
{

    rho    = b.rho;
    rho_u  = b.rho_u;
    rho_v  = b.rho_v;
    rho_et = b.rho_et;

    return *this;
} 

//------------------------------------------------------------------------------
//Multiplication overload
//1. double * primitiveVar
primitiveVar operator*(double a, const primitiveVar& b)
{

    return primitiveVar
    {
        a * b.rho,
        a * b.rho_u,
        a * b.rho_v,
        a * b.rho_et
    };
} 

//2. primitiveVar * primitiveVar
primitiveVar operator*(const primitiveVar& a, const primitiveVar& b)
{

    return primitiveVar
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
//1. primitiveVar / primitiveVar
primitiveVar operator/(const primitiveVar& a, const primitiveVar& b)
{

    if (b.rho == 0.0) std::cout<<"rho division by zero";
    if (b.rho_u == 0.0) std::cout<<"rho division by zero";
    if (b.rho_v == 0.0) std::cout<<"rho division by zero";
    if (b.rho_et == 0.0) std::cout<<"rho division by zero";
     
    return primitiveVar 
    {
        a.rho /  b.rho,
        a.rho_u / b.rho_u,
        a.rho_v / b.rho_v,
        a.rho_et / b.rho_et
   };
} 

//2. double / primitiveVar
primitiveVar operator/(double a, const primitiveVar& b)
{

    if (b.rho == 0.0) std::cout<<"rho division by zero";
    if (b.rho_u == 0.0) std::cout<<"rho division by zero";
    if (b.rho_v == 0.0) std::cout<<"rho division by zero";
    if (b.rho_et == 0.0) std::cout<<"rho division by zero";
     
    return primitiveVar 
    {
        a /  b.rho,
        a / b.rho_u,
        a / b.rho_v,
        a / b.rho_et
   };
}

//3. primitiveVar/double
primitiveVar operator/(const primitiveVar& a, double b)
{

    if (b == 0.0) std::cout<<"rho division by zero";

    return primitiveVar 
    {
        a.rho  / b ,
        a.rho_u / b ,
        a.rho_v / b ,
        a.rho_et / b
   };
} 
