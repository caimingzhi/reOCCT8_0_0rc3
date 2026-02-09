#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Surface.hpp>
#include <GeomAbs_CurveType.hpp>
#include <GeomAbs_Shape.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

class Adaptor3d_CurveOnSurface : public Adaptor3d_Curve
{
  DEFINE_STANDARD_RTTIEXT(Adaptor3d_CurveOnSurface, Adaptor3d_Curve)
public:
  Standard_EXPORT Adaptor3d_CurveOnSurface();

  Standard_EXPORT Adaptor3d_CurveOnSurface(const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT Adaptor3d_CurveOnSurface(const occ::handle<Adaptor2d_Curve2d>& C,
                                           const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT occ::handle<Adaptor3d_Curve> ShallowCopy() const override;

  Standard_EXPORT void Load(const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT void Load(const occ::handle<Adaptor2d_Curve2d>& C);

  Standard_EXPORT void Load(const occ::handle<Adaptor2d_Curve2d>& C,
                            const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT const occ::handle<Adaptor2d_Curve2d>& GetCurve() const;

  Standard_EXPORT const occ::handle<Adaptor3d_Surface>& GetSurface() const;

  Standard_EXPORT occ::handle<Adaptor2d_Curve2d>& ChangeCurve();

  Standard_EXPORT occ::handle<Adaptor3d_Surface>& ChangeSurface();

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

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
  Standard_EXPORT void EvalKPart();

  Standard_EXPORT void EvalFirstLastSurf();

  Standard_EXPORT void LocatePart(const gp_Pnt2d&                       UV,
                                  const gp_Vec2d&                       DUV,
                                  const occ::handle<Adaptor3d_Surface>& S,
                                  gp_Pnt2d&                             LeftBot,
                                  gp_Pnt2d&                             RightTop) const;

  Standard_EXPORT bool LocatePart_RevExt(const gp_Pnt2d&                       UV,
                                         const gp_Vec2d&                       DUV,
                                         const occ::handle<Adaptor3d_Surface>& S,
                                         gp_Pnt2d&                             LeftBot,
                                         gp_Pnt2d&                             RightTop) const;

  Standard_EXPORT bool LocatePart_Offset(const gp_Pnt2d&                       UV,
                                         const gp_Vec2d&                       DUV,
                                         const occ::handle<Adaptor3d_Surface>& S,
                                         gp_Pnt2d&                             LeftBot,
                                         gp_Pnt2d&                             RightTop) const;

  Standard_EXPORT void FindBounds(const NCollection_Array1<double>& Arr,
                                  const double                      XYComp,
                                  const double                      DUVComp,
                                  int&                              Bnd1,
                                  int&                              Bnd2,
                                  bool&                             DerIsNull) const;

private:
  occ::handle<Adaptor3d_Surface>             mySurface;
  occ::handle<Adaptor2d_Curve2d>             myCurve;
  GeomAbs_CurveType                          myType;
  gp_Circ                                    myCirc;
  gp_Lin                                     myLin;
  occ::handle<Adaptor3d_Surface>             myFirstSurf;
  occ::handle<Adaptor3d_Surface>             myLastSurf;
  occ::handle<NCollection_HSequence<double>> myIntervals;
  GeomAbs_Shape                              myIntCont;
};
