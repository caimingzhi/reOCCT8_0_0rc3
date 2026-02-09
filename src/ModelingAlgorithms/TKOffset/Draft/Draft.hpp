#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class TopoDS_Face;
class gp_Dir;

class Draft
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static double Angle(const TopoDS_Face& F, const gp_Dir& Direction);
};
