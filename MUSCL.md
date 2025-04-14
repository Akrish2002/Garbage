# Documentation  
## MUSCL  
1. Second order extrapolation for cell faces of the interior cells since we have values along the halo cell centers  
2. First order extrapolation for cell faces along the border since there exists only _single layer of halo cells_  
    - Reasoning at pg7 --> Last face needs nx + 1 for reconstruction, therefore only first order reconstruction of statevar possible
3. T17 --> Pg7, nx and ny are points along columns and rows, they are physical indices. To have center indices stateVar, we initialize Q with nx+1 and ny+1
4. Shifted the extrapolated state vectors Eq (3) and (4) by -1 to maintain consistency with face indices.  
    - It also follows, for better logic consistency, to initialize face stateVar also with nx+1 and ny+1, my quip is **if I do so would it affect the solver downstream?**  
### Flux Limiters
- Flux limiters are used in high resolution schemes to avoid spurious oscillations that would occur with high order spatial discretization due to shocks, discontinuities or sharp changes in solution. 
