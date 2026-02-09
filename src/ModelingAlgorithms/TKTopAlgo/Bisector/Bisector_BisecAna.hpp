#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Bisector_Curve.hpp>
#include <Standard_Real.hpp>
#include <GeomAbs_JoinType.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
class Geom2d_TrimmedCurve;
class Geom2d_Curve;
class gp_Pnt2d;
class gp_Vec2d;
class Geom2d_Point;
class GccInt_Bisec;
class Geom2d_Geometry;
class gp_Trsf2d;

class Bisector_BisecAna : public Bisector_Curve
{

public:
  Standard_EXPORT Bisector_BisecAna();

  Standard_EXPORT void Perform(const occ::handle<Geom2d_Curve>& Cu1,
                               const occ::handle<Geom2d_Curve>& Cu2,
                               const gp_Pnt2d&                  P,
                               const gp_Vec2d&                  V1,
                               const gp_Vec2d&                  V2,
                               const double                     Sense,
                               const GeomAbs_JoinType           jointype,
                               const double                     Tolerance,
                               const bool                       oncurve = true);

  Standard_EXPORT void Perform(const occ::handle<Geom2d_Curve>& Cu,
                               const occ::handle<Geom2d_Point>& Pnt,
                               const gp_Pnt2d&                  P,
                               const gp_Vec2d&                  V1,
                               const gp_Vec2d&                  V2,
                               const double                     Sense,
                               const double                     Tolerance,
                               const bool                       oncurve = true);

  Standard_EXPORT void Perform(const occ::handle<Geom2d_Point>& Pnt,
                               const occ::handle<Geom2d_Curve>& Cu,
                               const gp_Pnt2d&                  P,
                               const gp_Vec2d&                  V1,
                               const gp_Vec2d&                  V2,
                               const double                     Sense,
                               const double                     Tolerance,
                               const bool                       oncurve = true);

  Standard_EXPORT void Perform(const occ::handle<Geom2d_Point>& Pnt1,
                               const occ::handle<Geom2d_Point>& Pnt2,
                               const gp_Pnt2d&                  P,
                               const gp_Vec2d&                  V1,
                               const gp_Vec2d&                  V2,
                               const double                     Sense,
                               const double                     Tolerance = 0.0,
                               const bool                       oncurve   = true);

  Standard_EXPORT void Init(const occ::handle<Geom2d_TrimmedCurve>& bisector);

  Standard_EXPORT bool IsExtendAtStart() const override;

  Standard_EXPORT bool IsExtendAtEnd() const override;

  Standard_EXPORT void SetTrim(const occ::handle<Geom2d_Curve>& Cu);

  Standard_EXPORT void SetTrim(const double uf, const double ul);

  Standard_EXPORT void Reverse() override;

  Standard_EXPORT double ReversedParameter(const double U) const override;

  Standard_EXPORT bool IsCN(const int N) const override;

  Standard_EXPORT occ::handle<Geom2d_Geometry> Copy() const override;

  Standard_EXPORT void Transform(const gp_Trsf2d& T) override;

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT void D0(const double U, gp_Pnt2d& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt2d& P, gp_Vec2d& V1) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2) const override;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt2d&    P,
                          gp_Vec2d&    V1,
                          gp_Vec2d&    V2,
                          gp_Vec2d&    V3) const override;

  Standard_EXPORT gp_Vec2d DN(const double U, const int N) const override;

  Standard_EXPORT occ::handle<Geom2d_Curve> Geom2dCurve() const;

  Standard_EXPORT double Parameter(const gp_Pnt2d& P) const override;

  Standard_EXPORT double ParameterOfStartPoint() const;

  Standard_EXPORT double ParameterOfEndPoint() const;

  Standard_EXPORT int NbIntervals() const override;

  Standard_EXPORT double IntervalFirst(const int Index) const override;

  Standard_EXPORT double IntervalLast(const int Index) const override;

  Standard_EXPORT void Dump(const int Deep = 0, const int Offset = 0) const;

  DEFINE_STANDARD_RTTIEXT(Bisector_BisecAna, Bisector_Curve)

private:
  Standard_EXPORT double Distance(const gp_Pnt2d&                  P,
                                  const occ::handle<GccInt_Bisec>& Bis,
                                  const gp_Vec2d&                  V1,
                                  const gp_Vec2d&                  V2,
                                  const gp_Vec2d&                  VecRef,
                                  const double                     Sense,
                                  double&                          U,
                                  bool&                            sense,
                                  bool&                            ok,
                                  const bool                       IsBisecOfTwoLines = false);

  occ::handle<Geom2d_TrimmedCurve> thebisector;
};
