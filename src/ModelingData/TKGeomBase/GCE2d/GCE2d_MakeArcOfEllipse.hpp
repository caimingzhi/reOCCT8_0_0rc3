#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GCE2d_Root.hpp>
#include <Geom2d_TrimmedCurve.hpp>

class gp_Elips2d;
class gp_Pnt2d;

class GCE2d_MakeArcOfEllipse : public GCE2d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GCE2d_MakeArcOfEllipse(const gp_Elips2d& Elips,
                                         const double      Alpha1,
                                         const double      Alpha2,
                                         const bool        Sense = true);

  Standard_EXPORT GCE2d_MakeArcOfEllipse(const gp_Elips2d& Elips,
                                         const gp_Pnt2d&   P,
                                         const double      Alpha,
                                         const bool        Sense = true);

  Standard_EXPORT GCE2d_MakeArcOfEllipse(const gp_Elips2d& Elips,
                                         const gp_Pnt2d&   P1,
                                         const gp_Pnt2d&   P2,
                                         const bool        Sense = true);

  Standard_EXPORT const occ::handle<Geom2d_TrimmedCurve>& Value() const;

  operator const occ::handle<Geom2d_TrimmedCurve>&() const { return Value(); }

private:
  occ::handle<Geom2d_TrimmedCurve> TheArc;
};
