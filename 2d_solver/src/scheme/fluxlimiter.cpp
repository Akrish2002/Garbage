#include "fluxlimiter.h"

#include <iostream>

stateVar fluxlimiter(const stateVar& r, const std::string& type)
{
    if(type == "minmod") limiter = limiter_minmod;
    // Write for other flux limiters
    //
    //
    //

    else
    {
        std::cout<<"\n Unknown type of limiter"<<std::endl;
        exit(1);
    }
    
    return 
    {
        limiter(r.rho),
        limiter(r.rho_u),
        limiter(r.rho_v),
        limiter(r.rho_et),
        
    };

}
