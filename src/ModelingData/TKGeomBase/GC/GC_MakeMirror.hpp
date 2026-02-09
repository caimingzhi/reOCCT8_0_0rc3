#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom_Transformation;
class gp_Pnt;
class gp_Ax1;
class gp_Lin;
class gp_Dir;
class gp_Pln;
class gp_Ax2;

class GC_MakeMirror
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GC_MakeMirror(const gp_Pnt& Point);

  Standard_EXPORT GC_MakeMirror(const gp_Ax1& Axis);

  Standard_EXPORT GC_MakeMirror(const gp_Lin& Line);

  Standard_EXPORT GC_MakeMirror(const gp_Pnt& Point, const gp_Dir& Direc);

  Standard_EXPORT GC_MakeMirror(const gp_Pln& Plane);

  Standard_EXPORT GC_MakeMirror(const gp_Ax2& Plane);

  Standard_EXPORT const occ::handle<Geom_Transformation>& Value() const;

  operator const occ::handle<Geom_Transformation>&() const { return Value(); }

private:
  occ::handle<Geom_Transformation> TheMirror;
};
