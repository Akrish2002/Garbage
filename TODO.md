# ✅ To-Do List for CFD_FinalProject

This file tracks pending improvements and cleanup tasks for the 2D finite-volume Euler solver implementation.

---

- [ ] **Simplify `AddHaloCells_2D()`**  
  Refactor the function to eliminate repetitive lines and improve maintainability.

- [ ] **Hardcoded ghost cell values**<br>
  Edit the Grid class to have optional number of ghost cells, not just two --> which leads to editing the AddHaloCells() function to include that

- [ ] **ExportGridtoCSV**  
    The way this is going to output is in form of a ravel row after row, I would still need to reshape the array in python for example, however, that required prior knowledge of the dimensions of the array. Hence, ideally I should output in some other way that the metadata or the shape of the array is still written to the output.

- [ ] **Compute Metrics**  
    Break up metric computation into metrics.cpp, keep grid.cpp clean

- [ ] **Write a better compiler**  
    What is cmake that Luis uses? I do not want to run the line every time

- [ ] **Write exportGridtoBinary**

---

_Last updated: April 10, 2025_<br>
_Time: 14:05_

