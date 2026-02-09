#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GC_Root.hpp>
#include <Geom_CylindricalSurface.hpp>

class gp_Ax2;
class gp_Cylinder;
class gp_Pnt;
class gp_Ax1;
class gp_Circ;

class GC_MakeCylindricalSurface : public GC_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GC_MakeCylindricalSurface(const gp_Ax2& A2, const double Radius);

  Standard_EXPORT GC_MakeCylindricalSurface(const gp_Cylinder& C);

  Standard_EXPORT GC_MakeCylindricalSurface(const gp_Cylinder& Cyl, const gp_Pnt& Point);

  Standard_EXPORT GC_MakeCylindricalSurface(const gp_Cylinder& Cyl, const double Dist);

  Standard_EXPORT GC_MakeCylindricalSurface(const gp_Pnt& P1, const gp_Pnt& P2, const gp_Pnt& P3);

  Standard_EXPORT GC_MakeCylindricalSurface(const gp_Ax1& Axis, const double Radius);

  Standard_EXPORT GC_MakeCylindricalSurface(const gp_Circ& Circ);

  Standard_EXPORT const occ::handle<Geom_CylindricalSurface>& Value() const;

  operator const occ::handle<Geom_CylindricalSurface>&() const { return Value(); }

private:
  occ::handle<Geom_CylindricalSurface> TheCylinder;
};
