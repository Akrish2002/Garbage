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
        a.u   + b.u,
        a.v   + b.v,
        a.et  + b.et,
        a.ht  + b.ht,

        a.P   + b.P,
        a.T   + b.T,
        a.a   + b.a 
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
        a.u   - b.u,
        a.v   - b.v,
        a.et  - b.et,
        a.ht  - b.ht,

        a.P   - b.P,
        a.T   - b.T,
        a.a   - b.a 
   };
} 

//------------------------------------------------------------------------------
//Equalto  overloading
//1. primitiveVar = primitiveVar
primitiveVar primitiveVar::operator=(const primitiveVar& b)
{

        rho = b.rho,
        u   = b.u,
        v   = b.v,
        et  = b.et,
        ht  = b.ht,

        P   = b.P,
        T   = b.T,
        a   = b.a;

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
        a * b.u,
        a * b.v,
        a * b.et,
        a * b.ht,

        a * b.P,
        a * b.T,
        a * b.a 

    };
} 

primitiveVar operator*(const primitiveVar& b, double a)
{

    return primitiveVar
    {
        a * b.rho,
        a * b.u,
        a * b.v,
        a * b.et,
        a * b.ht,

        a * b.P,
        a * b.T,
        a * b.a 

    };
} 

//2. primitiveVar * primitiveVar
primitiveVar operator*(const primitiveVar& a, const primitiveVar& b)
{

    return primitiveVar
    {
        a.rho * b.rho,
        a.u   * b.u,
        a.v   * b.v,
        a.et  * b.et,
        a.ht  * b.ht,

        a.P   * b.P,
        a.T   * b.T,
        a.a   * b.a
    };
} 

//------------------------------------------------------------------------------
//Division overload
//Use assert to check for dividing by zeros
//1. primitiveVar / primitiveVar
primitiveVar operator/(const primitiveVar& a, const primitiveVar& b)
{

    if (b.rho == 0.0) std::cout<<"Primitive var division by zero";
    if (b.u   == 0.0) std::cout<<"Primitive var division by zero";
    if (b.v   == 0.0) std::cout<<"Primitive var division by zero";
    if (b.et  == 0.0) std::cout<<"Primitive var division by zero";
    if (b.ht  == 0.0) std::cout<<"Primitive var division by zero";

    if (b.P   == 0.0) std::cout<<"Primitive var division by zero";
    if (b.T   == 0.0) std::cout<<"Primitive var division by zero";
    if (b.a   == 0.0) std::cout<<"Primitive var division by zero";
     
    return primitiveVar 
    {
        a.rho /  b.rho,
        a.u   /  b.u,
        a.v   /  b.v,
        a.et  /  b.et,
        a.ht  /  b.ht,

        a.P   /  b.P,
        a.T   /  b.T,
        a.a   /  b.a
   };
} 

//2. double / primitiveVar
primitiveVar operator/(double a, const primitiveVar& b)
{

    if (b.rho == 0.0) std::cout<<"Primitive var is zero!";
    if (b.u   == 0.0) std::cout<<"Primitive var is zero!";
    if (b.v   == 0.0) std::cout<<"Primitive var is zero!";
    if (b.et  == 0.0) std::cout<<"Primitive var is zero!";
    if (b.ht  == 0.0) std::cout<<"Primitive var is zero!";

    if (b.P   == 0.0) std::cout<<"Primitive var is zero!";
    if (b.T   == 0.0) std::cout<<"Primitive var is zero!";
    if (b.a   == 0.0) std::cout<<"Primitive var is zero!";
     
    return primitiveVar 
    {
        a / b.rho,
        a / b.u,
        a / b.v,
        a / b.et,
        a / b.ht,

        a / b.P,
        a / b.T,
        a / b.a
   };
}

//3. primitiveVar/double
primitiveVar operator/(const primitiveVar& a, double b)
{

    if (b == 0.0) std::cout<<"Primitive Var being divided by zero";

    return primitiveVar 
    {
        a.rho  / b,
        a.u    / b,
        a.v    / b,
        a.et   / b,
        a.ht   / b,

        a.P    / b,
        a.T    / b,
        a.a    / b
   };
} 
