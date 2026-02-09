#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Solid.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
class TopoDS_Face;
class gp_Pnt;
class TopoDS_Shell;

class BRepPrimAPI_MakeHalfSpace : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepPrimAPI_MakeHalfSpace(const TopoDS_Face& Face, const gp_Pnt& RefPnt);

  Standard_EXPORT BRepPrimAPI_MakeHalfSpace(const TopoDS_Shell& Shell, const gp_Pnt& RefPnt);

  Standard_EXPORT const TopoDS_Solid& Solid() const;
  Standard_EXPORT                     operator TopoDS_Solid() const;

private:
  TopoDS_Solid mySolid;
};
