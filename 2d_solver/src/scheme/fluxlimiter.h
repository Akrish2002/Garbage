#ifndef CFD_SCHEMES_FLUXLIMITER_H
#define CFD_SCHEMES_FLUXLIMITER_H

#include "stateVar.h"

#include <string>

inline double limiter_minmod(double r)
{

    return std::max(0, std::min(1, r));

}

//Write other limiters also

stateVar fluxlimiter(const stateVar& r, const std::string& type);

#endif
