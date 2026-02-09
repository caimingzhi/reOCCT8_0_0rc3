#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GCE2d_Root.hpp>
#include <Geom2d_Parabola.hpp>

class gp_Parab2d;
class gp_Ax22d;
class gp_Ax2d;
class gp_Pnt2d;

class GCE2d_MakeParabola : public GCE2d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GCE2d_MakeParabola(const gp_Parab2d& Prb);

  Standard_EXPORT GCE2d_MakeParabola(const gp_Ax22d& Axis, const double Focal);

  Standard_EXPORT GCE2d_MakeParabola(const gp_Ax2d& MirrorAxis,
                                     const double   Focal,
                                     const bool     Sense);

  Standard_EXPORT GCE2d_MakeParabola(const gp_Ax2d& D, const gp_Pnt2d& F, const bool Sense = true);

  Standard_EXPORT GCE2d_MakeParabola(const gp_Pnt2d& S1, const gp_Pnt2d& O);

  Standard_EXPORT const occ::handle<Geom2d_Parabola>& Value() const;

  operator const occ::handle<Geom2d_Parabola>&() const { return Value(); }

private:
  occ::handle<Geom2d_Parabola> TheParabola;
};
