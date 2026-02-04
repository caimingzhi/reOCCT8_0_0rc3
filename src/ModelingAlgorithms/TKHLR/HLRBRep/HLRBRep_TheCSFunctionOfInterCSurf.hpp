#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <Standard_Boolean.hpp>
#include <math_Vector.hpp>
class HLRBRep_Surface;
class HLRBRep_SurfaceTool;
class gp_Lin;
class HLRBRep_LineTool;
class math_Matrix;
class gp_Pnt;

class HLRBRep_TheCSFunctionOfInterCSurf : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_TheCSFunctionOfInterCSurf(HLRBRep_Surface* const& S, const gp_Lin& C);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

  Standard_EXPORT const gp_Pnt& Point() const;

  Standard_EXPORT double Root() const;

  Standard_EXPORT HLRBRep_Surface* const& AuxillarSurface() const;

  Standard_EXPORT const gp_Lin& AuxillarCurve() const;

private:
  HLRBRep_Surface* surface;
  gp_Lin           curve;
  gp_Pnt           p;
  double           f;
};

