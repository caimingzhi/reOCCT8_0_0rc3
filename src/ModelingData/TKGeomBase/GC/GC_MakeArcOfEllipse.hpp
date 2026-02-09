#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GC_Root.hpp>
#include <Geom_TrimmedCurve.hpp>

class gp_Elips;
class gp_Pnt;

class GC_MakeArcOfEllipse : public GC_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GC_MakeArcOfEllipse(const gp_Elips& Elips,
                                      const double    Alpha1,
                                      const double    Alpha2,
                                      const bool      Sense);

  Standard_EXPORT GC_MakeArcOfEllipse(const gp_Elips& Elips,
                                      const gp_Pnt&   P,
                                      const double    Alpha,
                                      const bool      Sense);

  Standard_EXPORT GC_MakeArcOfEllipse(const gp_Elips& Elips,
                                      const gp_Pnt&   P1,
                                      const gp_Pnt&   P2,
                                      const bool      Sense);

  Standard_EXPORT const occ::handle<Geom_TrimmedCurve>& Value() const;

  operator const occ::handle<Geom_TrimmedCurve>&() const { return Value(); }

private:
  occ::handle<Geom_TrimmedCurve> TheArc;
};
