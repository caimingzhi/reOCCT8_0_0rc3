#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <Extrema_POnCurv.hpp>
#include <Extrema_POnSurf.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>
class Adaptor3d_Curve;
class Adaptor3d_Surface;
class math_Matrix;
class Extrema_POnCurv;
class Extrema_POnSurf;

class Extrema_FuncExtCS : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_FuncExtCS();

  Standard_EXPORT Extrema_FuncExtCS(const Adaptor3d_Curve& C, const Adaptor3d_Surface& S);

  Standard_EXPORT void Initialize(const Adaptor3d_Curve& C, const Adaptor3d_Surface& S);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& UV, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& UV, math_Matrix& DF) override;

  Standard_EXPORT bool Values(const math_Vector& UV, math_Vector& F, math_Matrix& DF) override;

  Standard_EXPORT int GetStateNumber() override;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT double SquareDistance(const int N) const;

  Standard_EXPORT const Extrema_POnCurv& PointOnCurve(const int N) const;

  Standard_EXPORT const Extrema_POnSurf& PointOnSurface(const int N) const;

  NCollection_Sequence<double>& SquareDistances() { return mySqDist; }

  NCollection_Sequence<Extrema_POnCurv>& PointsOnCurve() { return myPoint1; }

  NCollection_Sequence<Extrema_POnSurf>& PointsOnSurf() { return myPoint2; }

private:
  const Adaptor3d_Curve*                myC;
  const Adaptor3d_Surface*              myS;
  gp_Pnt                                myP1;
  gp_Pnt                                myP2;
  double                                myt;
  double                                myU;
  double                                myV;
  NCollection_Sequence<double>          mySqDist;
  NCollection_Sequence<Extrema_POnCurv> myPoint1;
  NCollection_Sequence<Extrema_POnSurf> myPoint2;
  bool                                  myCinit;
  bool                                  mySinit;
};
