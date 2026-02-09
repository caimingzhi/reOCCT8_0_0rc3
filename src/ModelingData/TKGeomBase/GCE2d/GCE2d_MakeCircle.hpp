#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GCE2d_Root.hpp>
#include <Geom2d_Circle.hpp>

class gp_Circ2d;
class gp_Ax2d;
class gp_Ax22d;
class gp_Pnt2d;

class GCE2d_MakeCircle : public GCE2d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GCE2d_MakeCircle(const gp_Circ2d& C);

  Standard_EXPORT GCE2d_MakeCircle(const gp_Ax2d& A, const double Radius, const bool Sense = true);

  Standard_EXPORT GCE2d_MakeCircle(const gp_Ax22d& A, const double Radius);

  Standard_EXPORT GCE2d_MakeCircle(const gp_Circ2d& Circ, const double Dist);

  Standard_EXPORT GCE2d_MakeCircle(const gp_Circ2d& Circ, const gp_Pnt2d& Point);

  Standard_EXPORT GCE2d_MakeCircle(const gp_Pnt2d& P1, const gp_Pnt2d& P2, const gp_Pnt2d& P3);

  Standard_EXPORT GCE2d_MakeCircle(const gp_Pnt2d& P, const double Radius, const bool Sense = true);

  Standard_EXPORT GCE2d_MakeCircle(const gp_Pnt2d& Center,
                                   const gp_Pnt2d& Point,
                                   const bool      Sense = true);

  Standard_EXPORT const occ::handle<Geom2d_Circle>& Value() const;

  operator const occ::handle<Geom2d_Circle>&() const { return Value(); }

private:
  occ::handle<Geom2d_Circle> TheCircle;
};
