#pragma once

#include <Standard.hpp>

#include <gp_Pnt2d.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <Bisector_Curve.hpp>
#include <GeomAbs_Shape.hpp>
class Geom2d_Curve;
class Geom2d_Geometry;
class gp_Trsf2d;
class gp_Vec2d;

class Bisector_BisecPC : public Bisector_Curve
{

public:
  Standard_EXPORT Bisector_BisecPC();

  Standard_EXPORT Bisector_BisecPC(const occ::handle<Geom2d_Curve>& Cu,
                                   const gp_Pnt2d&                  P,
                                   const double                     Side,
                                   const double                     DistMax = 500);

  Standard_EXPORT Bisector_BisecPC(const occ::handle<Geom2d_Curve>& Cu,
                                   const gp_Pnt2d&                  P,
                                   const double                     Side,
                                   const double                     UMin,
                                   const double                     UMax);

  Standard_EXPORT void Perform(const occ::handle<Geom2d_Curve>& Cu,
                               const gp_Pnt2d&                  P,
                               const double                     Side,
                               const double                     DistMax = 500);

  Standard_EXPORT bool IsExtendAtStart() const override;

  Standard_EXPORT bool IsExtendAtEnd() const override;

  Standard_EXPORT void Reverse() override;

  Standard_EXPORT double ReversedParameter(const double U) const override;

  Standard_EXPORT occ::handle<Geom2d_Geometry> Copy() const override;

  Standard_EXPORT void Transform(const gp_Trsf2d& T) override;

  Standard_EXPORT bool IsCN(const int N) const override;

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT int NbIntervals() const override;

  Standard_EXPORT double IntervalFirst(const int Index) const override;

  Standard_EXPORT double IntervalLast(const int Index) const override;

  Standard_EXPORT GeomAbs_Shape IntervalContinuity() const;

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT double Distance(const double U) const;

  Standard_EXPORT void D0(const double U, gp_Pnt2d& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt2d& P, gp_Vec2d& V) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2) const override;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt2d&    P,
                          gp_Vec2d&    V1,
                          gp_Vec2d&    V2,
                          gp_Vec2d&    V3) const override;

  Standard_EXPORT gp_Vec2d DN(const double U, const int N) const override;

  Standard_EXPORT void Dump(const int Deep = 0, const int Offset = 0) const;

  Standard_EXPORT double LinkBisCurve(const double U) const;

  Standard_EXPORT double LinkCurveBis(const double U) const;

  Standard_EXPORT double Parameter(const gp_Pnt2d& P) const override;

  Standard_EXPORT bool IsEmpty() const;

  DEFINE_STANDARD_RTTIEXT(Bisector_BisecPC, Bisector_Curve)

private:
  Standard_EXPORT void Values(const double U,
                              const int    N,
                              gp_Pnt2d&    P,
                              gp_Vec2d&    V1,
                              gp_Vec2d&    V2,
                              gp_Vec2d&    V3) const;

  Standard_EXPORT void Extension(const double U,
                                 gp_Pnt2d&    P,
                                 gp_Vec2d&    V1,
                                 gp_Vec2d&    V2,
                                 gp_Vec2d&    V3) const;

  Standard_EXPORT void ComputeIntervals();

  Standard_EXPORT void CuspFilter();

  Standard_EXPORT double SearchBound(const double U1, const double U2) const;

  Standard_EXPORT void Init(const occ::handle<Geom2d_Curve>&    Curve,
                            const gp_Pnt2d&                     Point,
                            const double                        Sign,
                            const NCollection_Sequence<double>& StartIntervals,
                            const NCollection_Sequence<double>& EndIntervals,
                            const int                           BisInterval,
                            const int                           CurrentInterval,
                            const double                        ShiftParameter,
                            const double                        DistMax,
                            const bool                          IsEmpty,
                            const bool                          IsConvex,
                            const bool                          ExtensionStart,
                            const bool                          ExtensionEnd,
                            const gp_Pnt2d&                     PointStartBis,
                            const gp_Pnt2d&                     PointEndBis);

  occ::handle<Geom2d_Curve>    curve;
  gp_Pnt2d                     point;
  double                       sign;
  NCollection_Sequence<double> startIntervals;
  NCollection_Sequence<double> endIntervals;
  int                          bisInterval;
  int                          currentInterval;
  double                       shiftParameter;
  double                       distMax;
  bool                         isEmpty;
  bool                         isConvex;
  bool                         extensionStart;
  bool                         extensionEnd;
  gp_Pnt2d                     pointStartBis;
  gp_Pnt2d                     pointEndBis;
};
