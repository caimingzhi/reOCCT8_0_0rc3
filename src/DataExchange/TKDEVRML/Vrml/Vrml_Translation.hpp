#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Vec.hpp>
#include <Standard_OStream.hpp>

//! defines a Translation of VRML specifying transform
//! properties.
//! This node defines a translation by 3D vector.
//! By default:
//! myTranslation (0,0,0)
class Vrml_Translation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_Translation();

  Standard_EXPORT Vrml_Translation(const gp_Vec& aTranslation);

  Standard_EXPORT void SetTranslation(const gp_Vec& aTranslation);

  Standard_EXPORT gp_Vec Translation() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  gp_Vec myTranslation;
};

