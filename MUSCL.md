# Documentation  
## MUSCL  
1. Shifted the extrapolated state vectors Eq (3) and (4) by -1 to maintain consistency with face indices  
2. Second order extrapolation for the faces of the interior cells since we have values along the halo cell centers  
3. First order for cell faces along the border since we _for now implementation is for single layer of halo cells_  
    - Reasoning at pg7 --> Last face needs nx + 1 for reconstruction, therefore only first order reconstruction of statevar possible
4. T17 --> Pg7, nx and ny are points along columns and rows, they are physical indices. To have center indices stateVar, we initialize Q with nx+1 and ny+1
