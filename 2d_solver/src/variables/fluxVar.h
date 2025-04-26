#ifndef CFD_VARIABLES_FLUX_H
#define CFD_VARIABLES_FLUX_H


struct fluxVar
{
    double rho_flux;     // F₁ ≡ mass flux
    double rho_u_flux;   // F₂ ≡ x‑momentum flux
    double rho_v_flux;   // F₃ ≡ y‑momentum flux
    double rho_ht_flux;  // F₄ ≡ energy flux

    //fluxVar
    //(
    //  double rho_flux_ = 0.0,
    //  double rho_u_flux_ = 0.0,
    //  double rho_v_flux_ = 0.0,
    //  double rho_ht_flux_ = 0.0
    //) {}

    fluxVar(double rho_flux_   = 0.0,
            double rho_u_flux_ = 0.0,
            double rho_v_flux_ = 0.0,
            double rho_ht_flux_= 0.0)
        : rho_flux   (rho_flux_),
          rho_u_flux (rho_u_flux_),
          rho_v_flux (rho_v_flux_),
          rho_ht_flux(rho_ht_flux_) {}
  
    fluxVar operator=(const fluxVar& b);

};

fluxVar operator+(const fluxVar& a, const fluxVar& b);

fluxVar operator-(const fluxVar& a, const fluxVar& b);

fluxVar operator*(double a, const fluxVar& F);
fluxVar operator*(const fluxVar& a, const fluxVar& b);

fluxVar operator/(const fluxVar& a, const fluxVar& b);
fluxVar operator/(double a, const fluxVar& F);
fluxVar operator/(const fluxVar& F, double a);

#endif
