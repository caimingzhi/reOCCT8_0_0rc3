#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom2d_Transformation;
class gp_Vec2d;
class gp_Pnt2d;

class GCE2d_MakeTranslation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GCE2d_MakeTranslation(const gp_Vec2d& Vect);

  Standard_EXPORT GCE2d_MakeTranslation(const gp_Pnt2d& Point1, const gp_Pnt2d& Point2);

  Standard_EXPORT const occ::handle<Geom2d_Transformation>& Value() const;

  operator const occ::handle<Geom2d_Transformation>&() const { return Value(); }

private:
  occ::handle<Geom2d_Transformation> TheTranslation;
};
