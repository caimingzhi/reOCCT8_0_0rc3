#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GCE2d_Root.hpp>
#include <Geom2d_Hyperbola.hpp>

class gp_Hypr2d;
class gp_Ax2d;
class gp_Ax22d;
class gp_Pnt2d;

class GCE2d_MakeHyperbola : public GCE2d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GCE2d_MakeHyperbola(const gp_Hypr2d& H);

  Standard_EXPORT GCE2d_MakeHyperbola(const gp_Ax2d& MajorAxis,
                                      const double   MajorRadius,
                                      const double   MinorRadius,
                                      const bool     Sense);

  Standard_EXPORT GCE2d_MakeHyperbola(const gp_Ax22d& Axis,
                                      const double    MajorRadius,
                                      const double    MinorRadius);

  Standard_EXPORT GCE2d_MakeHyperbola(const gp_Pnt2d& S1,
                                      const gp_Pnt2d& S2,
                                      const gp_Pnt2d& Center);

  Standard_EXPORT const occ::handle<Geom2d_Hyperbola>& Value() const;

  operator const occ::handle<Geom2d_Hyperbola>&() const { return Value(); }

private:
  occ::handle<Geom2d_Hyperbola> TheHyperbola;
};
