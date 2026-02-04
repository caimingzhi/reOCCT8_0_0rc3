#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Adaptor3d_Curve.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
#include <NCollection_Array1.hpp>
#include <GeomAbs_CurveType.hpp>

class gp_Pnt;
class gp_Vec;

//! to represent function C'(t)^C''(t)
class GeomFill_SnglrFunc : public Adaptor3d_Curve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_SnglrFunc(const occ::handle<Adaptor3d_Curve>& HC);

  //! Shallow copy of adaptor
  Standard_EXPORT occ::handle<Adaptor3d_Curve> ShallowCopy() const override;

  Standard_EXPORT void SetRatio(const double Ratio);

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

  //! Returns the number of intervals for continuity
  //! <S>. May be one if Continuity(me) >= <S>
  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  //! Stores in <T> the parameters bounding the intervals
  //! of continuity <S>.
  //!
  //! The array must provide enough room to accommodate
  //! for the parameters. i.e. T.Length() > NbIntervals()
  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  //! Computes the point of parameter U on the curve.
  Standard_EXPORT gp_Pnt Value(const double U) const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT double Period() const override;

  //! Computes the point of parameter U on the curve.
  Standard_EXPORT void D0(const double U, gp_Pnt& P) const override;

  //! Computes the point of parameter U on the curve with its
  //! first derivative.
  //! Raised if the continuity of the current interval
  //! is not C1.
  Standard_EXPORT void D1(const double U, gp_Pnt& P, gp_Vec& V) const override;

  //! Returns the point P of parameter U, the first and second
  //! derivatives V1 and V2.
  //! Raised if the continuity of the current interval
  //! is not C2.
  Standard_EXPORT void D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const override;

  //! Returns the point P of parameter U, the first, the second
  //! and the third derivative.
  //! Raised if the continuity of the current interval
  //! is not C1.
  Standard_EXPORT void D3(const double U,
                          gp_Pnt&      P,
                          gp_Vec&      V1,
                          gp_Vec&      V2,
                          gp_Vec&      V3) const override;

  //! The returned vector gives the value of the derivative for the
  //! order of derivation N.
  //! Raised if N < 1.
  Standard_EXPORT gp_Vec DN(const double U, const int N) const override;

  //! Returns the parametric resolution corresponding
  //! to the real space resolution <R3d>.
  Standard_EXPORT double Resolution(const double R3d) const override;

  //! Returns the type of the curve in the current
  //! interval: Line, Circle, Ellipse, Hyperbola,
  //! Parabola, BezierCurve, BSplineCurve, OtherCurve.
  Standard_EXPORT GeomAbs_CurveType GetType() const override;

private:
  occ::handle<Adaptor3d_Curve> myHCurve;
  double                       ratio;
};

