#pragma once

#include <Adaptor3d_Surface.hpp>
#include <GeomAbs_IsoType.hpp>

class Adaptor3d_IsoCurve : public Adaptor3d_Curve
{
  DEFINE_STANDARD_RTTIEXT(Adaptor3d_IsoCurve, Adaptor3d_Curve)
public:
  Standard_EXPORT Adaptor3d_IsoCurve();

  Standard_EXPORT Adaptor3d_IsoCurve(const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT Adaptor3d_IsoCurve(const occ::handle<Adaptor3d_Surface>& S,
                                     const GeomAbs_IsoType                 Iso,
                                     const double                          Param);

  Standard_EXPORT Adaptor3d_IsoCurve(const occ::handle<Adaptor3d_Surface>& S,
                                     const GeomAbs_IsoType                 Iso,
                                     const double                          Param,
                                     const double                          WFirst,
                                     const double                          WLast);

  Standard_EXPORT occ::handle<Adaptor3d_Curve> ShallowCopy() const override;

  Standard_EXPORT void Load(const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT void Load(const GeomAbs_IsoType Iso, const double Param);

  Standard_EXPORT void Load(const GeomAbs_IsoType Iso,
                            const double          Param,
                            const double          WFirst,
                            const double          WLast);

  const occ::handle<Adaptor3d_Surface>& Surface() const { return mySurface; }

  GeomAbs_IsoType Iso() const { return myIso; }

  double Parameter() const { return myParameter; }

  double FirstParameter() const override { return myFirst; }

  double LastParameter() const override { return myLast; }

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT occ::handle<Adaptor3d_Curve> Trim(const double First,
                                                    const double Last,
                                                    const double Tol) const override;

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT double Period() const override;

  Standard_EXPORT gp_Pnt Value(const double U) const override;

  Standard_EXPORT void D0(const double U, gp_Pnt& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt& P, gp_Vec& V) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const override;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt&      P,
                          gp_Vec&      V1,
                          gp_Vec&      V2,
                          gp_Vec&      V3) const override;

  Standard_EXPORT gp_Vec DN(const double U, const int N) const override;

  Standard_EXPORT double Resolution(const double R3d) const override;

  Standard_EXPORT GeomAbs_CurveType GetType() const override;

  Standard_EXPORT gp_Lin Line() const override;

  Standard_EXPORT gp_Circ Circle() const override;

  Standard_EXPORT gp_Elips Ellipse() const override;

  Standard_EXPORT gp_Hypr Hyperbola() const override;

  Standard_EXPORT gp_Parab Parabola() const override;

  Standard_EXPORT int Degree() const override;

  Standard_EXPORT bool IsRational() const override;

  Standard_EXPORT int NbPoles() const override;

  Standard_EXPORT int NbKnots() const override;

  Standard_EXPORT occ::handle<Geom_BezierCurve> Bezier() const override;

  Standard_EXPORT occ::handle<Geom_BSplineCurve> BSpline() const override;

private:
  occ::handle<Adaptor3d_Surface> mySurface;
  GeomAbs_IsoType                myIso;
  double                         myFirst;
  double                         myLast;
  double                         myParameter;
};
