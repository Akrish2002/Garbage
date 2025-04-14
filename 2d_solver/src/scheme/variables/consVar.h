#ifndef CFD_SCHEMES_STATEVAR_H
#define CFD_SCHEMES_STATEVAR_H

struct consVar
{
    double rho;

    double rho_u;
    double rho_v;
    double rho_et;
    
    consVar
    (
        double rho_ = 0.0, double rho_u_ = 0.0, double rho_v_ = 0.0, double rho_et_ = 0.0

    ) {}

    consVar operator=(const consVar& b);

};

consVar operator+(const consVar& a, const consVar& b);

consVar operator-(const consVar& a, const consVar& b);

consVar operator*(double a, const consVar& b);
consVar operator*(const consVar& a, const consVar& b);

consVar operator/(double a, const consVar& b);
consVar operator/(const consVar& a, double b);
consVar operator/(const consVar& a, const consVar& b);

#endif
