#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom_Transformation;
class gp_Vec;
class gp_Pnt;

class GC_MakeTranslation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GC_MakeTranslation(const gp_Vec& Vect);

  Standard_EXPORT GC_MakeTranslation(const gp_Pnt& Point1, const gp_Pnt& Point2);

  Standard_EXPORT const occ::handle<Geom_Transformation>& Value() const;

  operator const occ::handle<Geom_Transformation>&() const { return Value(); }

private:
  occ::handle<Geom_Transformation> TheTranslation;
};
