#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Vrml_MaterialBindingAndNormalBinding.hpp>
#include <Standard_OStream.hpp>

//! defines a NormalBinding node of VRML specifying properties of geometry
//! and its appearance.
//! This node specifies how the current normals are bound to shapes that follow in the scene
//! graph. Each shape node may interpret bindings differently.
//! The bindings for faces and vertices are meaningful only for shapes that are made from
//! faces and vertices. Similarly, the indexed bindings are only used by the shapes that allow
//! indexing. For bindings that require multiple normals, be sure to have at least as many
//! normals defined as are necessary; otherwise, errors will occur.
class Vrml_NormalBinding
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_NormalBinding(const Vrml_MaterialBindingAndNormalBinding aValue);

  Standard_EXPORT Vrml_NormalBinding();

  Standard_EXPORT void SetValue(const Vrml_MaterialBindingAndNormalBinding aValue);

  Standard_EXPORT Vrml_MaterialBindingAndNormalBinding Value() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  Vrml_MaterialBindingAndNormalBinding myValue;
};

