#ifndef CFD_DEBUGGER_DEBUG_H
#define CFD_DEBUGGER_DEBUG_H

#include "grid.h"

/*Parameters required
 * ------------------
 *  None
 *
 *  Used for outputting intermediary statements to debug the code
 *  Created one for each function in grid.h to break down debugging
 */

void D_GridConstructer(std::vector<std::vector<Point>>& n_2D, int d=0);
void D_AddHaloCells(std::vector<std::vector<Point>>& n_g_2D, int d=0);
//oid D_ComputeProjCellFaceArea();
//oid D_AvgToCellCenter();

#endif
