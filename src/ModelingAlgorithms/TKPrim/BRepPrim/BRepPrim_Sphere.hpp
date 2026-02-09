#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_Revolution.hpp>
class gp_Pnt;
class gp_Ax2;
class TopoDS_Face;

class BRepPrim_Sphere : public BRepPrim_Revolution
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepPrim_Sphere(const double Radius);

  Standard_EXPORT BRepPrim_Sphere(const gp_Pnt& Center, const double Radius);

  Standard_EXPORT BRepPrim_Sphere(const gp_Ax2& Axes, const double Radius);

  Standard_EXPORT TopoDS_Face MakeEmptyLateralFace() const override;

private:
  Standard_EXPORT void SetMeridian();

  double myRadius;
};
