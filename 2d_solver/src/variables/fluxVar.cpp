#include "fluxVar.h"

#include <vector>
#include <string>
#include <iostream>
#include <array>

//Performing operation overloading

//------------------------------------------------------------------------------
// Addition: fluxVar + fluxVar
fluxVar operator+(const fluxVar& a, const fluxVar& b)
{
    return fluxVar
    {
        a.rho_flux   + b.rho_flux,
        a.rho_u_flux + b.rho_u_flux,
        a.rho_v_flux + b.rho_v_flux,
        a.rho_ht_flux+ b.rho_ht_flux
    };
}


fluxVar operator-(const fluxVar& a, const fluxVar& b)
{
    return fluxVar
    {
        a.rho_flux   - b.rho_flux,
        a.rho_u_flux - b.rho_u_flux,
        a.rho_v_flux - b.rho_v_flux,
        a.rho_ht_flux- b.rho_ht_flux
    };
}


fluxVar fluxVar::operator=(const fluxVar& b)
{
    rho_flux    = b.rho_flux;
    rho_u_flux  = b.rho_u_flux;
    rho_v_flux  = b.rho_v_flux;
    rho_ht_flux = b.rho_ht_flux;
    return *this;
}


fluxVar operator*(const fluxVar& F, double a)
{
    return fluxVar
    {
        a * F.rho_flux,
        a * F.rho_u_flux,
        a * F.rho_v_flux,
        a * F.rho_ht_flux
    };
}


fluxVar operator*( double a, const fluxVar& F)
{
    return fluxVar
    {
        a * F.rho_flux,
        a * F.rho_u_flux,
        a * F.rho_v_flux,
        a * F.rho_ht_flux
    };
}


fluxVar operator*(const fluxVar& a, const fluxVar& b)
{
    return fluxVar
    {
        a.rho_flux    * b.rho_flux,
        a.rho_u_flux  * b.rho_u_flux,
        a.rho_v_flux  * b.rho_v_flux,
        a.rho_ht_flux * b.rho_ht_flux
    };
}


fluxVar operator/(const fluxVar& a, const fluxVar& b)
{
    if (b.rho_flux    == 0.0) std::cout<<"fluxVar division by zero in rho_flux\n";
    if (b.rho_u_flux  == 0.0) std::cout<<"fluxVar division by zero in rho_u_flux\n";
    if (b.rho_v_flux  == 0.0) std::cout<<"fluxVar division by zero in rho_v_flux\n";
    if (b.rho_ht_flux == 0.0) std::cout<<"fluxVar division by zero in rho_ht_flux\n";

    return fluxVar
    {
        a.rho_flux    / b.rho_flux,
        a.rho_u_flux  / b.rho_u_flux,
        a.rho_v_flux  / b.rho_v_flux,
        a.rho_ht_flux / b.rho_ht_flux
    };
}


fluxVar operator/(double a, const fluxVar& F)
{
    if (F.rho_flux    == 0.0) std::cout<<"fluxVar division by zero in rho_flux\n";
    if (F.rho_u_flux  == 0.0) std::cout<<"fluxVar division by zero in rho_u_flux\n";
    if (F.rho_v_flux  == 0.0) std::cout<<"fluxVar division by zero in rho_v_flux\n";
    if (F.rho_ht_flux == 0.0) std::cout<<"fluxVar division by zero in rho_ht_flux\n";

    return fluxVar
    {
        a / F.rho_flux,
        a / F.rho_u_flux,
        a / F.rho_v_flux,
        a / F.rho_ht_flux
    };
}


fluxVar operator/(const fluxVar& F, double a)
{
    if (a == 0.0) std::cout<<"fluxVar division by zero (scalar denominator)\n";
    return fluxVar
    {
        F.rho_flux    / a,
        F.rho_u_flux  / a,
        F.rho_v_flux  / a,
        F.rho_ht_flux / a
    };
}
