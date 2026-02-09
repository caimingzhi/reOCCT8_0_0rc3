#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GC_Root.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>

class gp_Pnt;

class GC_MakeTrimmedCone : public GC_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GC_MakeTrimmedCone(const gp_Pnt& P1,
                                     const gp_Pnt& P2,
                                     const gp_Pnt& P3,
                                     const gp_Pnt& P4);

  Standard_EXPORT GC_MakeTrimmedCone(const gp_Pnt& P1,
                                     const gp_Pnt& P2,
                                     const double  R1,
                                     const double  R2);

  Standard_EXPORT const occ::handle<Geom_RectangularTrimmedSurface>& Value() const;

  operator const occ::handle<Geom_RectangularTrimmedSurface>&() const { return Value(); }

private:
  occ::handle<Geom_RectangularTrimmedSurface> TheCone;
};
