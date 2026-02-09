#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_CString.hpp>
class TopoDS_Shape;

class VrmlAPI
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool Write(const TopoDS_Shape& aShape,
                                    const char*         aFileName,
                                    const int           aVersion = 2);
};
