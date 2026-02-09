#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Vrml_SFRotation.hpp>
#include <Standard_OStream.hpp>

class Vrml_Rotation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_Rotation();

  Standard_EXPORT Vrml_Rotation(const Vrml_SFRotation& aRotation);

  Standard_EXPORT void SetRotation(const Vrml_SFRotation& aRotation);

  Standard_EXPORT Vrml_SFRotation Rotation() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  Vrml_SFRotation myRotation;
};
