#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_OStream.hpp>
class TopoDS_Shape;

class TopTools
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Dump(const TopoDS_Shape& Sh, Standard_OStream& S);

  Standard_EXPORT static void Dummy(const int I);
};
