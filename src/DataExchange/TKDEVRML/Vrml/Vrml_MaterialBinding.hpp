#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Vrml_MaterialBindingAndNormalBinding.hpp>
#include <Standard_OStream.hpp>

class Vrml_MaterialBinding
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_MaterialBinding(const Vrml_MaterialBindingAndNormalBinding aValue);

  Standard_EXPORT Vrml_MaterialBinding();

  Standard_EXPORT void SetValue(const Vrml_MaterialBindingAndNormalBinding aValue);

  Standard_EXPORT Vrml_MaterialBindingAndNormalBinding Value() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  Vrml_MaterialBindingAndNormalBinding myValue;
};
