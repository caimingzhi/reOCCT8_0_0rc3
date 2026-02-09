#pragma once

#include <Poly_Triangulation.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_CString.hpp>
class TopoDS_Shape;

class StlAPI
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool Write(const TopoDS_Shape& theShape,
                                    const char*         theFile,
                                    const bool          theAsciiMode = true);

  Standard_DEPRECATED("This method is very inefficient; see RWStl class for better alternative")
  Standard_EXPORT static bool Read(TopoDS_Shape& theShape, const char* aFile);
};
