#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <Extrema_POnSurf.hpp>
#include <Standard_Boolean.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>

class Adaptor3d_Surface;
class math_Matrix;
class Extrema_POnSurf;

class Extrema_FuncPSNorm : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_FuncPSNorm();

  Standard_EXPORT Extrema_FuncPSNorm(const gp_Pnt& P, const Adaptor3d_Surface& S);

  Standard_EXPORT void Initialize(const Adaptor3d_Surface& S);

  Standard_EXPORT void SetPoint(const gp_Pnt& P);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& UV, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& UV, math_Matrix& DF) override;

  Standard_EXPORT bool Values(const math_Vector& UV, math_Vector& F, math_Matrix& DF) override;

  Standard_EXPORT int GetStateNumber() override;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT double SquareDistance(const int N) const;

  Standard_EXPORT const Extrema_POnSurf& Point(const int N) const;

private:
  gp_Pnt                                myP;
  const Adaptor3d_Surface*              myS;
  double                                myU;
  double                                myV;
  gp_Pnt                                myPs;
  NCollection_Sequence<double>          mySqDist;
  NCollection_Sequence<Extrema_POnSurf> myPoint;
  bool                                  myPinit;
  bool                                  mySinit;
};
