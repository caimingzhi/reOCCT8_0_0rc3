#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GC_Root.hpp>
#include <Geom_Hyperbola.hpp>

class gp_Hypr;
class gp_Ax2;
class gp_Pnt;

class GC_MakeHyperbola : public GC_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GC_MakeHyperbola(const gp_Hypr& H);

  Standard_EXPORT GC_MakeHyperbola(const gp_Ax2& A2,
                                   const double  MajorRadius,
                                   const double  MinorRadius);

  Standard_EXPORT GC_MakeHyperbola(const gp_Pnt& S1, const gp_Pnt& S2, const gp_Pnt& Center);

  Standard_EXPORT const occ::handle<Geom_Hyperbola>& Value() const;

  operator const occ::handle<Geom_Hyperbola>&() const { return Value(); }

private:
  occ::handle<Geom_Hyperbola> TheHyperbola;
};
