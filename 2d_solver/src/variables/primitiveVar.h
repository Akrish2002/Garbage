#ifndef CFD_SCHEMES_PRIMITIVE_H
#define CFD_SCHEMES_PRIMITIVE_H


/* Definition
 * ----------
 *
 *  double rho  :    Density
 *  double u    :    U velocity
 *  double v    :    V velocity
 *  double ht   :    Total enthalpy
 *  double P    :    Pressure
 *  double et   :    Total internal energy
 *
 * This struct helps store the primitive variables
 * Auto initializes them to zero value when called
 */
struct primitiveVar
{
    double rho;
    double u;
    double v;
    double ht;
    double P;
    double et;

    primitiveVar
    (
        double rho_ = 0.0, double u_ = 0.0, double v_ = 0.0, double et_ = 0.0, double ht_ = 0.0, double P_ = 0.0

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
