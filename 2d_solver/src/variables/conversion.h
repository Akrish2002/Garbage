#ifndef CFD_SCHEMES_CONVERSION_H
#define CFD_SCHEMES_CONVERSION_H

#include "consVar.h"
#include "primitiveVar.h"


/* Parameters required
 * -------------------
 *
 *  consVar& Q       : Conservative variable Q is passed by reference
 *  double gamma     : Specific heat
 *
 *  Function converts conservative variables to primitive variables using definitions provided in the lecture notes
 */
primitiveVar convertConstoPrim
(
    consVar& Q,
    const double gamma

);


#endif
