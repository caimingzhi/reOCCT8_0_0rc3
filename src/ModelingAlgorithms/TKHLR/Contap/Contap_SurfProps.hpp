#pragma once

#include <Adaptor3d_Surface.hpp>

class gp_Pnt;
class gp_Vec;

class Contap_SurfProps
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Normale(const occ::handle<Adaptor3d_Surface>& S,
                                      const double                          U,
                                      const double                          V,
                                      gp_Pnt&                               P,
                                      gp_Vec&                               N);

  Standard_EXPORT static void DerivAndNorm(const occ::handle<Adaptor3d_Surface>& S,
                                           const double                          U,
                                           const double                          V,
                                           gp_Pnt&                               P,
                                           gp_Vec&                               d1u,
                                           gp_Vec&                               d1v,
                                           gp_Vec&                               N);

  Standard_EXPORT static void NormAndDn(const occ::handle<Adaptor3d_Surface>& S,
                                        const double                          U,
                                        const double                          V,
                                        gp_Pnt&                               P,
                                        gp_Vec&                               N,
                                        gp_Vec&                               Dnu,
                                        gp_Vec&                               Dnv);
};
