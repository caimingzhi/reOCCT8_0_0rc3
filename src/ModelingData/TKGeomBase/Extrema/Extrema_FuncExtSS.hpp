#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <Extrema_POnSurf.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>
class Adaptor3d_Surface;
class math_Matrix;
class Extrema_POnSurf;

class Extrema_FuncExtSS : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_FuncExtSS();

  Standard_EXPORT Extrema_FuncExtSS(const Adaptor3d_Surface& S1, const Adaptor3d_Surface& S2);

  Standard_EXPORT void Initialize(const Adaptor3d_Surface& S1, const Adaptor3d_Surface& S2);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& UV, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& UV, math_Matrix& DF) override;

  Standard_EXPORT bool Values(const math_Vector& UV, math_Vector& F, math_Matrix& DF) override;

  Standard_EXPORT int GetStateNumber() override;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT double SquareDistance(const int N) const;

  Standard_EXPORT const Extrema_POnSurf& PointOnS1(const int N) const;

  Standard_EXPORT const Extrema_POnSurf& PointOnS2(const int N) const;

private:
  const Adaptor3d_Surface*              myS1;
  const Adaptor3d_Surface*              myS2;
  gp_Pnt                                myP1;
  gp_Pnt                                myP2;
  double                                myU1;
  double                                myV1;
  double                                myU2;
  double                                myV2;
  NCollection_Sequence<double>          mySqDist;
  NCollection_Sequence<Extrema_POnSurf> myPoint1;
  NCollection_Sequence<Extrema_POnSurf> myPoint2;
  bool                                  myS1init;
  bool                                  myS2init;
};
