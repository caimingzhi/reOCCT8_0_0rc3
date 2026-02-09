#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GC_Root.hpp>
#include <Geom_Circle.hpp>

class gp_Circ;
class gp_Ax2;
class gp_Pnt;
class gp_Dir;
class gp_Ax1;

class GC_MakeCircle : public GC_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GC_MakeCircle(const gp_Circ& C);

  Standard_EXPORT GC_MakeCircle(const gp_Ax2& A2, const double Radius);

  Standard_EXPORT GC_MakeCircle(const gp_Circ& Circ, const double Dist);

  Standard_EXPORT GC_MakeCircle(const gp_Circ& Circ, const gp_Pnt& Point);

  Standard_EXPORT GC_MakeCircle(const gp_Pnt& P1, const gp_Pnt& P2, const gp_Pnt& P3);

  Standard_EXPORT GC_MakeCircle(const gp_Pnt& Center, const gp_Dir& Norm, const double Radius);

  Standard_EXPORT GC_MakeCircle(const gp_Pnt& Center, const gp_Pnt& PtAxis, const double Radius);

  Standard_EXPORT GC_MakeCircle(const gp_Ax1& Axis, const double Radius);

  Standard_EXPORT const occ::handle<Geom_Circle>& Value() const;

  operator const occ::handle<Geom_Circle>&() const { return Value(); }

private:
  occ::handle<Geom_Circle> TheCircle;
};
