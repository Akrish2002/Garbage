#include "consVar.h"

#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <cmath>

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

    rho    = b.rho,
    rho_u  = b.rho_u,
    rho_v  = b.rho_v,
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
    double err = 1e-12;    

    auto ratiocheck = [err](double n, double d) -> double
    {
        if(std::fabs(n) < err && std::fabs(d) < err)
            return 0.0;
    
        if(std::fabs(d) < err)
            return (n > 0.0 ? 1e6 : -1e6); 

        else return n/d;
    };
 
    return consVar 
    {
        ratiocheck(a.rho    ,   b.rho),
        ratiocheck(a.rho_u  ,   b.rho_u),
        ratiocheck(a.rho_v  ,   b.rho_v),
        ratiocheck(a.rho_et ,   b.rho_et)
   };

    if (b.rho == 0.0)    
        {
            std::cout<<"--rho division by zero \n"; 
            std::exit(0);
        }

    if (b.rho_u == 0.0)  
        {
            std::cout<<"--rho_u  division by zero \n"; 
            std::exit(0);
        }

    if (b.rho_v == 0.0)  
        {
            std::cout<<"--rho_v  division by zero \n"; 
            std::exit(0);
        }

    if (b.rho_et == 0.0) 
        {
            std::cout<<"--rho_et division by zero \n"; 
            std::exit(0);
        }
} 

//2. double / consVar
consVar operator/(double a, const consVar& b)
{
    
    double err = 1e-12;
    
    auto ratiocheck = [a, err](double d) -> double
    {
        if(std::fabs(d) < err)
            return (a > 0.0 ? 1e6 : -1e6);
        
        else return a/d;


    };
         
    return consVar 
    {
          ratiocheck(b.rho),
          ratiocheck(b.rho_u),
          ratiocheck(b.rho_v),
          ratiocheck(b.rho_et)
   };

    if (b.rho == 0.0)       
        {
            std::cout<<"--Constant division by zero consVar rho \n"; 
            std::exit(0);
        }

    if (b.rho_u == 0.0)     
        {
            std::cout<<"--Constant division by zero consVar rho_u \n"; 
            std::exit(0);
        }

    if (b.rho_v == 0.0)     
        {
            std::cout<<"--Constant division by zero consVar rho_v \n"; 
            std::exit(0);
        }


        {
            std::cout<<"--Constant division by zero consVar rho_et \n"; 
            std::exit(0);
        }
    
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



