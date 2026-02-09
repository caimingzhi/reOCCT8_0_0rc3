#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_OStream.hpp>

class Vrml_TransformSeparator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_TransformSeparator();

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream);

private:
  bool myFlagPrint;
};
