#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class Geom_Transformation;
class gp_Pnt;

class GC_MakeScale
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GC_MakeScale(const gp_Pnt& Point, const double Scale);

  Standard_EXPORT const occ::handle<Geom_Transformation>& Value() const;

  operator const occ::handle<Geom_Transformation>&() const { return Value(); }

private:
  occ::handle<Geom_Transformation> TheScale;
};
