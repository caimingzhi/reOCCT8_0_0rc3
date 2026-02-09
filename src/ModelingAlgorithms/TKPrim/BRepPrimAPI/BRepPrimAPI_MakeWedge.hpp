#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_Wedge.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
class gp_Ax2;
class TopoDS_Shell;
class TopoDS_Solid;

class BRepPrimAPI_MakeWedge : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepPrimAPI_MakeWedge(const double dx,
                                        const double dy,
                                        const double dz,
                                        const double ltx);

  Standard_EXPORT BRepPrimAPI_MakeWedge(const gp_Ax2& Axes,
                                        const double  dx,
                                        const double  dy,
                                        const double  dz,
                                        const double  ltx);

  Standard_EXPORT BRepPrimAPI_MakeWedge(const double dx,
                                        const double dy,
                                        const double dz,
                                        const double xmin,
                                        const double zmin,
                                        const double xmax,
                                        const double zmax);

  Standard_EXPORT BRepPrimAPI_MakeWedge(const gp_Ax2& Axes,
                                        const double  dx,
                                        const double  dy,
                                        const double  dz,
                                        const double  xmin,
                                        const double  zmin,
                                        const double  xmax,
                                        const double  zmax);

  Standard_EXPORT BRepPrim_Wedge& Wedge();

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT const TopoDS_Shell& Shell();
  Standard_EXPORT                     operator TopoDS_Shell();

  Standard_EXPORT const TopoDS_Solid& Solid();
  Standard_EXPORT                     operator TopoDS_Solid();

private:
  BRepPrim_Wedge myWedge;
};
