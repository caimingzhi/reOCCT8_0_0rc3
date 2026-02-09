#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class TopoDS_Shell;
class TopoDS_Solid;

class BRepClass3d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static TopoDS_Shell OuterShell(const TopoDS_Solid& S);
};
