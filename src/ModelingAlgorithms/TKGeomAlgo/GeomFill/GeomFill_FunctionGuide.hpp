#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <Standard_Integer.hpp>
#include <math_Vector.hpp>

class Adaptor3d_Curve;
class GeomFill_SectionLaw;
class Geom_Curve;
class Geom_Surface;
class gp_Pnt;
class math_Matrix;
class gp_Vec;

class GeomFill_FunctionGuide : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_FunctionGuide(const occ::handle<GeomFill_SectionLaw>& S,
                                         const occ::handle<Adaptor3d_Curve>&     Guide,
                                         const double                            ParamOnLaw = 0.0);

  Standard_EXPORT void SetParam(const double  Param,
                                const gp_Pnt& Centre,
                                const gp_XYZ& Dir,
                                const gp_XYZ& XDir);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

  Standard_EXPORT bool DerivT(const math_Vector& X,
                              const gp_XYZ&      DCentre,
                              const gp_XYZ&      DDir,
                              math_Vector&       DFDT);

  Standard_EXPORT bool Deriv2T(const gp_XYZ& DCentre,
                               const gp_XYZ& DDir,
                               math_Vector&  DFDT,
                               math_Vector&  D2FT);

private:
  Standard_EXPORT void DSDT(const double  U,
                            const double  V,
                            const gp_XYZ& DCentre,
                            const gp_XYZ& DDir,
                            gp_Vec&       DSDT) const;

  occ::handle<Adaptor3d_Curve>     TheGuide;
  occ::handle<GeomFill_SectionLaw> TheLaw;
  bool                             isconst;
  occ::handle<Geom_Curve>          TheCurve;
  occ::handle<Geom_Curve>          TheConst;
  occ::handle<Geom_Surface>        TheSurface;
  double                           First;
  double                           Last;
  double                           TheUonS;
  gp_XYZ                           Centre;
  gp_XYZ                           Dir;
};
