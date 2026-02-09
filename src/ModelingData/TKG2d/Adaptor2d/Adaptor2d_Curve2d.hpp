#pragma once

#include <GeomAbs_CurveType.hpp>
#include <GeomAbs_Shape.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Hypr2d.hpp>
#include <gp_Parab2d.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <NCollection_Array1.hpp>

class gp_Pnt2d;
class gp_Vec2d;
class Geom2d_BezierCurve;
class Geom2d_BSplineCurve;

class Adaptor2d_Curve2d : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Adaptor2d_Curve2d, Standard_Transient)
public:
  Standard_EXPORT virtual occ::handle<Adaptor2d_Curve2d> ShallowCopy() const;

  Standard_EXPORT virtual double FirstParameter() const;

  Standard_EXPORT virtual double LastParameter() const;

  Standard_EXPORT virtual GeomAbs_Shape Continuity() const;

  Standard_EXPORT virtual int NbIntervals(const GeomAbs_Shape S) const;

  Standard_EXPORT virtual void Intervals(NCollection_Array1<double>& T,
                                         const GeomAbs_Shape         S) const;

  Standard_EXPORT virtual occ::handle<Adaptor2d_Curve2d> Trim(const double First,
                                                              const double Last,
                                                              const double Tol) const;

  Standard_EXPORT virtual bool IsClosed() const;

  Standard_EXPORT virtual bool IsPeriodic() const;

  Standard_EXPORT virtual double Period() const;

  Standard_EXPORT virtual gp_Pnt2d Value(const double U) const;

  Standard_EXPORT virtual void D0(const double U, gp_Pnt2d& P) const;

  Standard_EXPORT virtual void D1(const double U, gp_Pnt2d& P, gp_Vec2d& V) const;

  Standard_EXPORT virtual void D2(const double U, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2) const;

  Standard_EXPORT virtual void D3(const double U,
                                  gp_Pnt2d&    P,
                                  gp_Vec2d&    V1,
                                  gp_Vec2d&    V2,
                                  gp_Vec2d&    V3) const;

  Standard_EXPORT virtual gp_Vec2d DN(const double U, const int N) const;

  Standard_EXPORT virtual double Resolution(const double R3d) const;

  Standard_EXPORT virtual GeomAbs_CurveType GetType() const;

  Standard_EXPORT virtual gp_Lin2d Line() const;

  Standard_EXPORT virtual gp_Circ2d Circle() const;

  Standard_EXPORT virtual gp_Elips2d Ellipse() const;

  Standard_EXPORT virtual gp_Hypr2d Hyperbola() const;

  Standard_EXPORT virtual gp_Parab2d Parabola() const;

  Standard_EXPORT virtual int Degree() const;

  Standard_EXPORT virtual bool IsRational() const;

  Standard_EXPORT virtual int NbPoles() const;

  Standard_EXPORT virtual int NbKnots() const;

  Standard_EXPORT virtual int NbSamples() const;

  Standard_EXPORT virtual occ::handle<Geom2d_BezierCurve> Bezier() const;

  Standard_EXPORT virtual occ::handle<Geom2d_BSplineCurve> BSpline() const;
  Standard_EXPORT ~Adaptor2d_Curve2d() override;
};
