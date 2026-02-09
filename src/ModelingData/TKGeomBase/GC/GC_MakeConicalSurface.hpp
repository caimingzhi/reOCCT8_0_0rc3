#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GC_Root.hpp>
#include <Geom_ConicalSurface.hpp>

class gp_Ax2;
class gp_Cone;
class gp_Pnt;

class GC_MakeConicalSurface : public GC_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GC_MakeConicalSurface(const gp_Ax2& A2, const double Ang, const double Radius);

  Standard_EXPORT GC_MakeConicalSurface(const gp_Cone& C);

  Standard_EXPORT GC_MakeConicalSurface(const gp_Pnt& P1,
                                        const gp_Pnt& P2,
                                        const gp_Pnt& P3,
                                        const gp_Pnt& P4);

  Standard_EXPORT GC_MakeConicalSurface(const gp_Pnt& P1,
                                        const gp_Pnt& P2,
                                        const double  R1,
                                        const double  R2);

  Standard_EXPORT const occ::handle<Geom_ConicalSurface>& Value() const;

  operator const occ::handle<Geom_ConicalSurface>&() const { return Value(); }

private:
  occ::handle<Geom_ConicalSurface> TheCone;
};
