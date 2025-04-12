#include "fluxlimiter.h"

#include <iostream>

stateVar fluxlimiter(const stateVar& r, const std::string& type)
{
    if(type == "minmod")
    {     
        return 
        {
            limiter_minmod(r.rho),
            limiter_minmod(r.rho_u),
            limiter_minmod(r.rho_v),
            limiter_minmod(r.rho_et)
            
        };
    }

    // Write for other flux limiters
    //
    //
    //

    else
    {
        std::cout<<"\n Unknown type of limiter"<<std::endl;
        exit(1);
    }
    

}
