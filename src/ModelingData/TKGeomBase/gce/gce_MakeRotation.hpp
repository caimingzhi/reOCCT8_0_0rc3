#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Trsf.hpp>
class gp_Lin;
class gp_Ax1;
class gp_Pnt;
class gp_Dir;

class gce_MakeRotation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeRotation(const gp_Lin& Line, const double Angle);

  Standard_EXPORT gce_MakeRotation(const gp_Ax1& Axis, const double Angle);

  Standard_EXPORT gce_MakeRotation(const gp_Pnt& Point, const gp_Dir& Direc, const double Angle);

  Standard_EXPORT const gp_Trsf& Value() const;

  Standard_EXPORT const gp_Trsf& Operator() const;
  Standard_EXPORT                operator gp_Trsf() const;

private:
  gp_Trsf TheRotation;
};
