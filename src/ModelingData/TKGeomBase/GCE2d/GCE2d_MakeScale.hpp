#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class Geom2d_Transformation;
class gp_Pnt2d;

class GCE2d_MakeScale
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GCE2d_MakeScale(const gp_Pnt2d& Point, const double Scale);

  Standard_EXPORT const occ::handle<Geom2d_Transformation>& Value() const;

  operator const occ::handle<Geom2d_Transformation>&() const { return Value(); }

private:
  occ::handle<Geom2d_Transformation> TheScale;
};
