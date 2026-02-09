#pragma once

#include <Standard.hpp>

#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <Bisector_PolyBis.hpp>
#include <gp_Pnt2d.hpp>
#include <Bisector_Curve.hpp>
#include <GeomAbs_Shape.hpp>
class Geom2d_Curve;
class Geom2d_Geometry;
class gp_Trsf2d;
class gp_Vec2d;

class Bisector_BisecCC : public Bisector_Curve
{

public:
  Standard_EXPORT Bisector_BisecCC();

  Standard_EXPORT Bisector_BisecCC(const occ::handle<Geom2d_Curve>& Cu1,
                                   const occ::handle<Geom2d_Curve>& Cu2,
                                   const double                     Side1,
                                   const double                     Side2,
                                   const gp_Pnt2d&                  Origin,
                                   const double                     DistMax = 500);

  Standard_EXPORT void Perform(const occ::handle<Geom2d_Curve>& Cu1,
                               const occ::handle<Geom2d_Curve>& Cu2,
                               const double                     Side1,
                               const double                     Side2,
                               const gp_Pnt2d&                  Origin,
                               const double                     DistMax = 500);

  Standard_EXPORT bool IsExtendAtStart() const override;

  Standard_EXPORT bool IsExtendAtEnd() const override;

  Standard_EXPORT void Reverse() override;

  Standard_EXPORT double ReversedParameter(const double U) const override;

  Standard_EXPORT bool IsCN(const int N) const override;

  Standard_EXPORT occ::handle<Bisector_BisecCC> ChangeGuide() const;

  Standard_EXPORT occ::handle<Geom2d_Geometry> Copy() const override;

  Standard_EXPORT void Transform(const gp_Trsf2d& T) override;

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT int NbIntervals() const override;

  Standard_EXPORT double IntervalFirst(const int Index) const override;

  Standard_EXPORT double IntervalLast(const int Index) const override;

  Standard_EXPORT GeomAbs_Shape IntervalContinuity() const;

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT gp_Pnt2d ValueAndDist(const double U,
                                        double&      U1,
                                        double&      U2,
                                        double&      Distance) const;

  Standard_EXPORT gp_Pnt2d ValueByInt(const double U,
                                      double&      U1,
                                      double&      U2,
                                      double&      Distance) const;

  Standard_EXPORT void D0(const double U, gp_Pnt2d& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt2d& P, gp_Vec2d& V) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2) const override;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt2d&    P,
                          gp_Vec2d&    V1,
                          gp_Vec2d&    V2,
                          gp_Vec2d&    V3) const override;

  Standard_EXPORT gp_Vec2d DN(const double U, const int N) const override;

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT double LinkBisCurve(const double U) const;

  Standard_EXPORT double LinkCurveBis(const double U) const;

  Standard_EXPORT double Parameter(const gp_Pnt2d& P) const override;

  Standard_EXPORT occ::handle<Geom2d_Curve> Curve(const int IndCurve) const;

  Standard_EXPORT const Bisector_PolyBis& Polygon() const;

  Standard_EXPORT void Dump(const int Deep = 0, const int Offset = 0) const;

  DEFINE_STANDARD_RTTIEXT(Bisector_BisecCC, Bisector_Curve)

private:
  Standard_EXPORT void Values(const double U,
                              const int    N,
                              gp_Pnt2d&    P,
                              gp_Vec2d&    V1,
                              gp_Vec2d&    V2,
                              gp_Vec2d&    V3) const;

  Standard_EXPORT void SupLastParameter();

  Standard_EXPORT gp_Pnt2d
    Extension(const double U, double& U1, double& U2, double& Dist, gp_Vec2d& T1) const;

  Standard_EXPORT double SearchBound(const double U1, const double U2) const;

  Standard_EXPORT void ComputePointEnd();

  Standard_EXPORT void Curve(const int Index, const occ::handle<Geom2d_Curve>& C);

  Standard_EXPORT void Sign(const int Index, const double Sign);

  Standard_EXPORT void Polygon(const Bisector_PolyBis& Poly);

  Standard_EXPORT void DistMax(const double DistMax);

  Standard_EXPORT void IsConvex(const int Index, const bool IsConvex);

  Standard_EXPORT void IsEmpty(const bool IsEmpty);

  Standard_EXPORT void ExtensionStart(const bool ExtensionStart);

  Standard_EXPORT void ExtensionEnd(const bool ExtensionEnd);

  Standard_EXPORT void PointStart(const gp_Pnt2d& Point);

  Standard_EXPORT void PointEnd(const gp_Pnt2d& Point);

  Standard_EXPORT void StartIntervals(const NCollection_Sequence<double>& StartIntervals);

  Standard_EXPORT void EndIntervals(const NCollection_Sequence<double>& EndIntervals);

  Standard_EXPORT void FirstParameter(const double U1);

  Standard_EXPORT void LastParameter(const double U1);

  occ::handle<Geom2d_Curve>    curve1;
  occ::handle<Geom2d_Curve>    curve2;
  double                       sign1;
  double                       sign2;
  NCollection_Sequence<double> startIntervals;
  NCollection_Sequence<double> endIntervals;
  int                          currentInterval;
  Bisector_PolyBis             myPolygon;
  double                       shiftParameter;
  double                       distMax;
  bool                         isEmpty;
  bool                         isConvex1;
  bool                         isConvex2;
  bool                         extensionStart;
  bool                         extensionEnd;
  gp_Pnt2d                     pointStart;
  gp_Pnt2d                     pointEnd;
};
