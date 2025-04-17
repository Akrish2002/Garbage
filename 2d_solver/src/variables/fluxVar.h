#ifndef CFD_VARIABLES_FLUX_H
#define CFD_VARIABLES_FLUX_H


struct fluxVar
{
    double rho_flux;     // F₁ ≡ mass flux
    double rho_u_flux;   // F₂ ≡ x‑momentum flux
    double rho_v_flux;   // F₃ ≡ y‑momentum flux
    double rho_et_flux;  // F₄ ≡ energy flux

    fluxVar
    (
      double rho_flux_ = 0.0,
      double rho_u_flux_ = 0.0,
      double rho_v_flux_ = 0.0,
      double rho_et_flux_ = 0.0
    ) {}
  
    fluxVar& operator=(const fluxVar& b);

};

fluxVar operator+(const fluxVar& a, const fluxVar& b);

fluxVar operator-(const fluxVar& a, const fluxVar& b);

fluxVar operator*(double a, const fluxVar& F);
fluxVar operator*(const fluxVar& a, const fluxVar& b);

fluxVar operator/(const fluxVar& a, const fluxVar& b);
fluxVar operator/(double a, const fluxVar& F);
fluxVar operator/(const fluxVar& F, double a);

#endif
