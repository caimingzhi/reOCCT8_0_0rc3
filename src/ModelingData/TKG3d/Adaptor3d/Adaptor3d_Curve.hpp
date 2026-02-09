#pragma once

#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Hypr.hpp>
#include <gp_Parab.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <NCollection_Array1.hpp>
#include <GeomAbs_CurveType.hpp>

class gp_Pnt;
class gp_Vec;
class Geom_BezierCurve;
class Geom_BSplineCurve;
class Geom_OffsetCurve;

class Adaptor3d_Curve : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Adaptor3d_Curve, Standard_Transient)
public:
  Standard_EXPORT virtual occ::handle<Adaptor3d_Curve> ShallowCopy() const;

  Standard_EXPORT virtual double FirstParameter() const;

  Standard_EXPORT virtual double LastParameter() const;

  Standard_EXPORT virtual GeomAbs_Shape Continuity() const;

  Standard_EXPORT virtual int NbIntervals(const GeomAbs_Shape S) const;

  Standard_EXPORT virtual void Intervals(NCollection_Array1<double>& T,
                                         const GeomAbs_Shape         S) const;

  Standard_EXPORT virtual occ::handle<Adaptor3d_Curve> Trim(const double First,
                                                            const double Last,
                                                            const double Tol) const;

  Standard_EXPORT virtual bool IsClosed() const;

  Standard_EXPORT virtual bool IsPeriodic() const;

  Standard_EXPORT virtual double Period() const;

  Standard_EXPORT virtual gp_Pnt Value(const double U) const;

  Standard_EXPORT virtual void D0(const double U, gp_Pnt& P) const;

  Standard_EXPORT virtual void D1(const double U, gp_Pnt& P, gp_Vec& V) const;

  Standard_EXPORT virtual void D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const;

  Standard_EXPORT virtual void D3(const double U,
                                  gp_Pnt&      P,
                                  gp_Vec&      V1,
                                  gp_Vec&      V2,
                                  gp_Vec&      V3) const;

  Standard_EXPORT virtual gp_Vec DN(const double U, const int N) const;

  Standard_EXPORT virtual double Resolution(const double R3d) const;

  Standard_EXPORT virtual GeomAbs_CurveType GetType() const;

  Standard_EXPORT virtual gp_Lin Line() const;

  Standard_EXPORT virtual gp_Circ Circle() const;

  Standard_EXPORT virtual gp_Elips Ellipse() const;

  Standard_EXPORT virtual gp_Hypr Hyperbola() const;

  Standard_EXPORT virtual gp_Parab Parabola() const;

  Standard_EXPORT virtual int Degree() const;

  Standard_EXPORT virtual bool IsRational() const;

  Standard_EXPORT virtual int NbPoles() const;

  Standard_EXPORT virtual int NbKnots() const;

  Standard_EXPORT virtual occ::handle<Geom_BezierCurve> Bezier() const;

  Standard_EXPORT virtual occ::handle<Geom_BSplineCurve> BSpline() const;

  Standard_EXPORT virtual occ::handle<Geom_OffsetCurve> OffsetCurve() const;

  Standard_EXPORT ~Adaptor3d_Curve() override;
};
