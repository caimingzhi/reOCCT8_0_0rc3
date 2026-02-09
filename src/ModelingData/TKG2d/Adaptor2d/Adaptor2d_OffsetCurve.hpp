#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <GeomAbs_CurveType.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>

class gp_Pnt2d;
class gp_Vec2d;
class gp_Lin2d;
class gp_Circ2d;
class gp_Elips2d;
class gp_Hypr2d;
class gp_Parab2d;
class Geom2d_BezierCurve;
class Geom2d_BSplineCurve;

class Adaptor2d_OffsetCurve : public Adaptor2d_Curve2d
{
  DEFINE_STANDARD_RTTIEXT(Adaptor2d_OffsetCurve, Adaptor2d_Curve2d)
public:
  Standard_EXPORT Adaptor2d_OffsetCurve();

  Standard_EXPORT Adaptor2d_OffsetCurve(const occ::handle<Adaptor2d_Curve2d>& C);

  Standard_EXPORT Adaptor2d_OffsetCurve(const occ::handle<Adaptor2d_Curve2d>& C,
                                        const double                          Offset);

  Standard_EXPORT Adaptor2d_OffsetCurve(const occ::handle<Adaptor2d_Curve2d>& C,
                                        const double                          Offset,
                                        const double                          WFirst,
                                        const double                          WLast);

  Standard_EXPORT occ::handle<Adaptor2d_Curve2d> ShallowCopy() const override;

  Standard_EXPORT void Load(const occ::handle<Adaptor2d_Curve2d>& S);

  Standard_EXPORT void Load(const double Offset);

  Standard_EXPORT void Load(const double Offset, const double WFirst, const double WLast);

  const occ::handle<Adaptor2d_Curve2d>& Curve() const { return myCurve; }

  double Offset() const { return myOffset; }

  double FirstParameter() const override { return myFirst; }

  double LastParameter() const override { return myLast; }

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT occ::handle<Adaptor2d_Curve2d> Trim(const double First,
                                                      const double Last,
                                                      const double Tol) const override;

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT double Period() const override;

  Standard_EXPORT gp_Pnt2d Value(const double U) const override;

  Standard_EXPORT void D0(const double U, gp_Pnt2d& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt2d& P, gp_Vec2d& V) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2) const override;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt2d&    P,
                          gp_Vec2d&    V1,
                          gp_Vec2d&    V2,
                          gp_Vec2d&    V3) const override;

  Standard_EXPORT gp_Vec2d DN(const double U, const int N) const override;

  Standard_EXPORT double Resolution(const double R3d) const override;

  Standard_EXPORT GeomAbs_CurveType GetType() const override;

  Standard_EXPORT gp_Lin2d Line() const override;

  Standard_EXPORT gp_Circ2d Circle() const override;

  Standard_EXPORT gp_Elips2d Ellipse() const override;

  Standard_EXPORT gp_Hypr2d Hyperbola() const override;

  Standard_EXPORT gp_Parab2d Parabola() const override;

  Standard_EXPORT int Degree() const override;

  Standard_EXPORT bool IsRational() const override;

  Standard_EXPORT int NbPoles() const override;

  Standard_EXPORT int NbKnots() const override;

  Standard_EXPORT occ::handle<Geom2d_BezierCurve> Bezier() const override;

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> BSpline() const override;

  Standard_EXPORT int NbSamples() const override;

private:
  occ::handle<Adaptor2d_Curve2d> myCurve;
  double                         myOffset;
  double                         myFirst;
  double                         myLast;
};
