#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_Cylinder.hpp>
#include <BRepPrimAPI_MakeOneAxis.hpp>
class gp_Ax2;

class BRepPrimAPI_MakeCylinder : public BRepPrimAPI_MakeOneAxis
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepPrimAPI_MakeCylinder(const double R, const double H);

  Standard_EXPORT BRepPrimAPI_MakeCylinder(const double R, const double H, const double Angle);

  Standard_EXPORT BRepPrimAPI_MakeCylinder(const gp_Ax2& Axes, const double R, const double H);

  Standard_EXPORT BRepPrimAPI_MakeCylinder(const gp_Ax2& Axes,
                                           const double  R,
                                           const double  H,
                                           const double  Angle);

  Standard_EXPORT void* OneAxis() override;

  Standard_EXPORT BRepPrim_Cylinder& Cylinder();

private:
  BRepPrim_Cylinder myCylinder;
};
