#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GCE2d_Root.hpp>
#include <Geom2d_TrimmedCurve.hpp>

class gp_Circ2d;
class gp_Pnt2d;
class gp_Vec2d;

class GCE2d_MakeArcOfCircle : public GCE2d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GCE2d_MakeArcOfCircle(const gp_Circ2d& Circ,
                                        const double     Alpha1,
                                        const double     Alpha2,
                                        const bool       Sense = true);

  Standard_EXPORT GCE2d_MakeArcOfCircle(const gp_Circ2d& Circ,
                                        const gp_Pnt2d&  P,
                                        const double     Alpha,
                                        const bool       Sense = true);

  Standard_EXPORT GCE2d_MakeArcOfCircle(const gp_Circ2d& Circ,
                                        const gp_Pnt2d&  P1,
                                        const gp_Pnt2d&  P2,
                                        const bool       Sense = true);

  Standard_EXPORT GCE2d_MakeArcOfCircle(const gp_Pnt2d& P1, const gp_Pnt2d& P2, const gp_Pnt2d& P3);

  Standard_EXPORT GCE2d_MakeArcOfCircle(const gp_Pnt2d& P1, const gp_Vec2d& V, const gp_Pnt2d& P2);

  Standard_EXPORT const occ::handle<Geom2d_TrimmedCurve>& Value() const;

  operator const occ::handle<Geom2d_TrimmedCurve>&() const { return Value(); }

private:
  occ::handle<Geom2d_TrimmedCurve> TheArc;
};
