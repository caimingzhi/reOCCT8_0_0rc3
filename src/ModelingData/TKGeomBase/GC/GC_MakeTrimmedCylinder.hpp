#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GC_Root.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>

class gp_Pnt;
class gp_Circ;
class gp_Ax1;

class GC_MakeTrimmedCylinder : public GC_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GC_MakeTrimmedCylinder(const gp_Pnt& P1, const gp_Pnt& P2, const gp_Pnt& P3);

  Standard_EXPORT GC_MakeTrimmedCylinder(const gp_Circ& Circ, const double Height);

  Standard_EXPORT GC_MakeTrimmedCylinder(const gp_Ax1& A1,
                                         const double  Radius,
                                         const double  Height);

  Standard_EXPORT const occ::handle<Geom_RectangularTrimmedSurface>& Value() const;

  operator const occ::handle<Geom_RectangularTrimmedSurface>&() const { return Value(); }

private:
  occ::handle<Geom_RectangularTrimmedSurface> TheCyl;
};
