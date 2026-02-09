#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom2d_Transformation;
class gp_Pnt2d;
class gp_Ax2d;
class gp_Lin2d;
class gp_Dir2d;

class GCE2d_MakeMirror
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GCE2d_MakeMirror(const gp_Pnt2d& Point);

  Standard_EXPORT GCE2d_MakeMirror(const gp_Ax2d& Axis);

  Standard_EXPORT GCE2d_MakeMirror(const gp_Lin2d& Line);

  Standard_EXPORT GCE2d_MakeMirror(const gp_Pnt2d& Point, const gp_Dir2d& Direc);

  Standard_EXPORT const occ::handle<Geom2d_Transformation>& Value() const;

  operator const occ::handle<Geom2d_Transformation>&() const { return Value(); }

private:
  occ::handle<Geom2d_Transformation> TheMirror;
};
