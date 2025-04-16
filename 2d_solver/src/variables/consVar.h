#ifndef CFD_SCHEMES_CONSVAR_H
#define CFD_SCHEMES_CONSVAR_H


/* Definition
 * ----------
 *
 *  double rho      :   Density
 *  double rho_u    :   Density * u
 *  double rho_v    :   Density * v
 *  double rho_et   :   Density * et (Total internal energy)
 *
 * This struct helps store the conservative variables, essential Q from lecture notes
 * Auto initializes them to zero value when called
 */
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
