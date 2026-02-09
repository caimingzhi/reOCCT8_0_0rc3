#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GC_Root.hpp>
#include <Geom_Plane.hpp>

class gp_Pln;
class gp_Pnt;
class gp_Dir;
class gp_Ax1;

class GC_MakePlane : public GC_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GC_MakePlane(const gp_Pln& Pl);

  Standard_EXPORT GC_MakePlane(const gp_Pnt& P, const gp_Dir& V);

  Standard_EXPORT GC_MakePlane(const double A, const double B, const double C, const double D);

  Standard_EXPORT GC_MakePlane(const gp_Pln& Pln, const gp_Pnt& Point);

  Standard_EXPORT GC_MakePlane(const gp_Pln& Pln, const double Dist);

  Standard_EXPORT GC_MakePlane(const gp_Pnt& P1, const gp_Pnt& P2, const gp_Pnt& P3);

  Standard_EXPORT GC_MakePlane(const gp_Ax1& Axis);

  Standard_EXPORT const occ::handle<Geom_Plane>& Value() const;

  operator const occ::handle<Geom_Plane>&() const { return Value(); }

private:
  occ::handle<Geom_Plane> ThePlane;
};
