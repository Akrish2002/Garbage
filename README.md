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

### Documentation  
#### MUSCL  
1. Shifted the extrapolated state vectors Eq (3) and (4) by -1 to maintain consistency with face indices  
2. Second order extrapolation for the faces of the interior cells since we have values along the halo cell centers  
3. First order for cell faces along the border since we _for now implementation is for single layer of halo cells_  
