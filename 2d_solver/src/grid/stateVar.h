#ifndef CFD_GRID_STATEVAR_H
#define CFD_GRID_STATEVAR_H

struct stateVar
{
    double rho;
    double rho_u;
    double rho_v;
    double rho_et;
    
    stateVar(double rho_ = 0.0, double rho_u_ = 0.0, double rho_v_ = 0.0, double rho_et_ = 0.0) {}

};

stateVar operator+(const stateVar& a, const stateVar& b);
stateVar operator-(const stateVar& a, const stateVar& b);
stateVar operator*(const stateVar& a, const stateVar& b);
stateVar operator/(const stateVar& a, const stateVar& b);
stateVar operator/(double a, const stateVar& b);

#endif
