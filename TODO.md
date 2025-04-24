# ✅ To-Do List for CFD_FinalProject

This file tracks pending improvements and cleanup tasks for the 2D finite-volume Euler solver implementation.

---
- [ ] **Print statments**    
    Since after MUSCL implementation, I have stopped adding print statements, add to track solver progress.  

- [ ] **fluxVar**  
    Changed = operation overloading in fluxVar.h from reference to non-refernce kind and it compiled, why?  

- [ ] **S_xi_nx and so on**  
    Difference in grid size might cause seg fault if indices are incorrectly called, recheck implementation

- [ ] **Recheck Implemention of Eigen**  
    See if the R and lamda matrices have been properly initialized. Check to see if the function works as indented

- [ ] **ExportGridtoCSV**  
    The way this is going to output is in form of a ravel row after row, I would still need to reshape the array in python for example, however, that required prior knowledge of the dimensions of the array. Hence, ideally I should output in some other way that the metadata or the shape of the array is still written to the output.

- [ ] **Write exportGridtoBinary**

---

_Last updated: April 23, 2025_<br>

