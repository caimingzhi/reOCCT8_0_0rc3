#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_CString.hpp>
class TopoDS_Shape;

//! API for writing to VRML 1.0
class VrmlAPI
{
public:
  DEFINE_STANDARD_ALLOC

  //! With help of this class user can change parameters of writing.
  //! Converts the shape aShape to VRML format of the passed version and writes it
  //! to the file identified by aFileName using default parameters.
  Standard_EXPORT static bool Write(const TopoDS_Shape& aShape,
                                    const char*         aFileName,
                                    const int           aVersion = 2);
};

