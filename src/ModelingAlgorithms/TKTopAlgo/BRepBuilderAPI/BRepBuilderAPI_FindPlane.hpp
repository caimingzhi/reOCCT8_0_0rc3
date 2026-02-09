#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom_Plane;
class TopoDS_Shape;

class BRepBuilderAPI_FindPlane
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBuilderAPI_FindPlane();

  Standard_EXPORT BRepBuilderAPI_FindPlane(const TopoDS_Shape& S, const double Tol = -1);

  Standard_EXPORT void Init(const TopoDS_Shape& S, const double Tol = -1);

  Standard_EXPORT bool Found() const;

  Standard_EXPORT occ::handle<Geom_Plane> Plane() const;

private:
  occ::handle<Geom_Plane> myPlane;
};
