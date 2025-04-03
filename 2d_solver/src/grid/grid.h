//Include guard
#ifndef CFD_GRID
#define CFD_GRID

#include <vector>
#include <array>
#include <string>


// Grid Class
// 2D grid reader and additional fucntions
//

class Grid
{
    private:
        std::string m_file;
        bool m_write;
        std::vector<std::vector<double>> m_coords;
        int m_nx, m_ny, m_nz;

    public:
        //Constructor
        Grid(std::string file, /*Luis had one more here*/ bool write=false);

        //Functions
        void addHaloCells();
        void computeMetrics();

        //Destructor
        ~Grid();
}

#endif
