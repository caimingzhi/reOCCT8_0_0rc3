#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomAbs_JoinType.hpp>
class Geom2d_TrimmedCurve;
class Geom2d_Curve;
class gp_Pnt2d;
class gp_Vec2d;
class Geom2d_Point;

class Bisector_Bisec
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Bisector_Bisec();

  Standard_EXPORT void Perform(const occ::handle<Geom2d_Curve>& Cu1,
                               const occ::handle<Geom2d_Curve>& Cu2,
                               const gp_Pnt2d&                  P,
                               const gp_Vec2d&                  V1,
                               const gp_Vec2d&                  V2,
                               const double                     Sense,
                               const GeomAbs_JoinType           ajointype,
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

  Standard_EXPORT const occ::handle<Geom2d_TrimmedCurve>& Value() const;

  Standard_EXPORT const occ::handle<Geom2d_TrimmedCurve>& ChangeValue();

private:
  occ::handle<Geom2d_TrimmedCurve> thebisector;
};
