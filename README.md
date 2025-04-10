# Garbage
Garbage 2

##  Grid Naming Convention

To maintain clarity and consistency across the 2D finite-volume solver, the following variable naming scheme is used for spatial grids and geometry-related fields:

###  Coordinate Containers   
| Name        | Description                                       |
|-------------|---------------------------------------------------|
| `Rows&Cols` | **ny --> Rows** and **nx --> Columns**            |
| `n_2D`      | Node coordinates for the **interior domain only** |
| `n_g_2D`    | Node coordinates including **ghost/halo cells**   |
| `cc_2D`     | **Cell-centered** coordinates (centroids)         |
| `Point`     | Contains all variables --> x, y, rho, u, v, et    |

