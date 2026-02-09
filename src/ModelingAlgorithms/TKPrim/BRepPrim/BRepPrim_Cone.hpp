#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_Revolution.hpp>
class gp_Ax2;
class gp_Pnt;
class TopoDS_Face;

class BRepPrim_Cone : public BRepPrim_Revolution
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepPrim_Cone(const double  Angle,
                                const gp_Ax2& Position,
                                const double  Height,
                                const double  Radius = 0);

  Standard_EXPORT BRepPrim_Cone(const double Angle);

  Standard_EXPORT BRepPrim_Cone(const double Angle, const gp_Pnt& Apex);

  Standard_EXPORT BRepPrim_Cone(const double Angle, const gp_Ax2& Axes);

  Standard_EXPORT BRepPrim_Cone(const double R1, const double R2, const double H);

  Standard_EXPORT BRepPrim_Cone(const gp_Pnt& Center,
                                const double  R1,
                                const double  R2,
                                const double  H);

  Standard_EXPORT BRepPrim_Cone(const gp_Ax2& Axes,
                                const double  R1,
                                const double  R2,
                                const double  H);

  Standard_EXPORT TopoDS_Face MakeEmptyLateralFace() const override;

private:
  Standard_EXPORT void SetMeridian();

  Standard_EXPORT void SetParameters(const double R1, const double R2, const double H);

  double myHalfAngle;
  double myRadius;
};
