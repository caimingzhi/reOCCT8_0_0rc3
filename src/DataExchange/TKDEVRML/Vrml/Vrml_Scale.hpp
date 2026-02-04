#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Vec.hpp>
#include <Standard_OStream.hpp>

//! defines a Scale node of VRML specifying transform
//! properties.
//! This node defines a 3D scaling about the origin.
//! By default:
//! myRotation = (1 1 1)
class Vrml_Scale
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_Scale();

  Standard_EXPORT Vrml_Scale(const gp_Vec& aScaleFactor);

  Standard_EXPORT void SetScaleFactor(const gp_Vec& aScaleFactor);

  Standard_EXPORT gp_Vec ScaleFactor() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  gp_Vec myScaleFactor;
};

