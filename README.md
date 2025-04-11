# Garbage

##  Grid Naming Convention

To maintain clarity and consistency across the 2D finite-volume solver, the following variable naming scheme is used:

###  Coordinate Containers   
| Name        | Description                                       |
|-------------|---------------------------------------------------|
| `n_2D`      | Node coordinates for the **interior domain only** |
| `n_g_2D`    | Node coordinates including **ghost/halo cells**   |
| `cc_2D`     | **Cell-centered** coordinates (centroids)         |
| `Point`     | Contains variables --> x, y                       |  
| `StateVar`   | Contains variables --> rho, u, v and et           |

