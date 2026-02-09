#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_OStream.hpp>

class Vrml_Switch
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_Switch(const int aWhichChild = -1);

  Standard_EXPORT void SetWhichChild(const int aWhichChild);

  Standard_EXPORT int WhichChild() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  int myWhichChild;
};
