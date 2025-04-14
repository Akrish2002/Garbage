#ifndef CFD_SCHEMES_STATEVAR_H
#define CFD_SCHEMES_STATEVAR_H

struct primitiveVar
{
    double rho;
    double u;
    double v;
    double et;
    double h;
    double P;

    primitiveVar
    (
        double rho_ = 0.0, double u_ = 0.0, double v_ = 0.0, double et_ = 0.0, double h_ = 0.0, double P_ = 0.0

    ) {}

    primitiveVar operator=(const primitiveVar& b);

};

primitiveVar operator+(const primitiveVar& a, const primitiveVar& b);

primitiveVar operator-(const primitiveVar& a, const primitiveVar& b);

primitiveVar operator*(double a, const primitiveVar& b);
primitiveVar operator*(const primitiveVar& a, const primitiveVar& b);

primitiveVar operator/(double a, const primitiveVar& b);
primitiveVar operator/(const primitiveVar& a, double b);
primitiveVar operator/(const primitiveVar& a, const primitiveVar& b);

#endif
