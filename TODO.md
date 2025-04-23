# ✅ To-Do List for CFD_FinalProject

This file tracks pending improvements and cleanup tasks for the 2D finite-volume Euler solver implementation.

---

- [ ] **Recheck Implemention of Eigen**
    See if the R and lamda matrices have been properly initialized. Check to see if the function works as indented

- [ ] **Simplify `AddHaloCells_2D()`**  
  Refactor the function to eliminate repetitive lines and improve maintainability.

- [ ] **ExportGridtoCSV**  
    The way this is going to output is in form of a ravel row after row, I would still need to reshape the array in python for example, however, that required prior knowledge of the dimensions of the array. Hence, ideally I should output in some other way that the metadata or the shape of the array is still written to the output.

- [ ] **Write exportGridtoBinary**

---

_Last updated: April 23, 2025_<br>

