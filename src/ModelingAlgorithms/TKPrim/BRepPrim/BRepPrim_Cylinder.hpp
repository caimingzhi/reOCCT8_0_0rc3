#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_Revolution.hpp>
class gp_Ax2;
class gp_Pnt;
class TopoDS_Face;

class BRepPrim_Cylinder : public BRepPrim_Revolution
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepPrim_Cylinder(const gp_Ax2& Position,
                                    const double  Radius,
                                    const double  Height);

  Standard_EXPORT BRepPrim_Cylinder(const double Radius);

  Standard_EXPORT BRepPrim_Cylinder(const gp_Pnt& Center, const double Radius);

  Standard_EXPORT BRepPrim_Cylinder(const gp_Ax2& Axes, const double Radius);

  Standard_EXPORT BRepPrim_Cylinder(const double R, const double H);

  Standard_EXPORT BRepPrim_Cylinder(const gp_Pnt& Center, const double R, const double H);

  Standard_EXPORT TopoDS_Face MakeEmptyLateralFace() const override;

private:
  Standard_EXPORT void SetMeridian();

  double myRadius;
};
