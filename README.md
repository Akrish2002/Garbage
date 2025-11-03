# General

##  Grid Naming Convention

To maintain clarity and consistency across the 2D finite-volume solver, the following variable naming scheme is used:

###  Coordinate Containers   
| Name        | Description                                       |
|-------------|---------------------------------------------------|
| `n_2D`            | Node coordinates for the **interior domain only**                                 |
| `n_g_2D`          | Node coordinates including **ghost/halo cells**                                   |
| `cc_2D`           | **Cell-centered** coordinates (centroids)                                         |
| `Point`           | Contains variables --> x, y                                                       |  
| `consVar`         | Contains variables --> rho, rho_u, rho_v and rho_et                               |
| `primitiveVar`    | Contains variables --> rho, u, v, et, ht and P                                    |
| `fluxVar`         | Contains variables --> rho_flux, rho_u_flux, rho_v_flux and rho_et_flux           |

### Logic  
-  nx and ny are grid node numbers, they are not cell centers  
    - nx + 2 and ny + 2 --> Number of grid nodes including Halo
    - nx + 1 and ny + 1 --> Number of cell centers including Halo
        - Q, V, E, F 
 
