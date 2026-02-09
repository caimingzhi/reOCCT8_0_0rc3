#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepPrim_Wedge.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
class gp_Pnt;
class gp_Ax2;
class TopoDS_Shell;
class TopoDS_Solid;
class TopoDS_Face;

class BRepPrimAPI_MakeBox : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  BRepPrimAPI_MakeBox() = default;

  Standard_EXPORT BRepPrimAPI_MakeBox(const double dx, const double dy, const double dz);

  Standard_EXPORT BRepPrimAPI_MakeBox(const gp_Pnt& P,
                                      const double  dx,
                                      const double  dy,
                                      const double  dz);

  Standard_EXPORT BRepPrimAPI_MakeBox(const gp_Pnt& P1, const gp_Pnt& P2);

  Standard_EXPORT BRepPrimAPI_MakeBox(const gp_Ax2& Axes,
                                      const double  dx,
                                      const double  dy,
                                      const double  dz);

  Standard_EXPORT void Init(const double theDX, const double theDY, const double theDZ);

  Standard_EXPORT void Init(const gp_Pnt& thePnt,
                            const double  theDX,
                            const double  theDY,
                            const double  theDZ);

  Standard_EXPORT void Init(const gp_Pnt& thePnt1, const gp_Pnt& thePnt2);

  Standard_EXPORT void Init(const gp_Ax2& theAxes,
                            const double  theDX,
                            const double  theDY,
                            const double  theDZ);

  Standard_EXPORT BRepPrim_Wedge& Wedge();

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT const TopoDS_Shell& Shell();
  Standard_EXPORT                     operator TopoDS_Shell();

  Standard_EXPORT const TopoDS_Solid& Solid();
  Standard_EXPORT                     operator TopoDS_Solid();

  Standard_EXPORT const TopoDS_Face& BottomFace();

  Standard_EXPORT const TopoDS_Face& BackFace();

  Standard_EXPORT const TopoDS_Face& FrontFace();

  Standard_EXPORT const TopoDS_Face& LeftFace();

  Standard_EXPORT const TopoDS_Face& RightFace();

  Standard_EXPORT const TopoDS_Face& TopFace();

protected:
  BRepPrim_Wedge myWedge;
};
