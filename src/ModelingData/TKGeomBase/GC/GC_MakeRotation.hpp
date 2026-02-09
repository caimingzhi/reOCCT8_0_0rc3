#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class Geom_Transformation;
class gp_Lin;
class gp_Ax1;
class gp_Pnt;
class gp_Dir;

class GC_MakeRotation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GC_MakeRotation(const gp_Lin& Line, const double Angle);

  Standard_EXPORT GC_MakeRotation(const gp_Ax1& Axis, const double Angle);

  Standard_EXPORT GC_MakeRotation(const gp_Pnt& Point, const gp_Dir& Direc, const double Angle);

  Standard_EXPORT const occ::handle<Geom_Transformation>& Value() const;

  operator const occ::handle<Geom_Transformation>&() const { return Value(); }

private:
  occ::handle<Geom_Transformation> TheRotation;
};
