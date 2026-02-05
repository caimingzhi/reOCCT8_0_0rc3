#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_OStream.hpp>

//! defines a TransformSeparator node of VRML specifying group properties.
//! This group node is similar to separator node in that it saves state
//! before traversing its children and restores it afterwards.
//! This node can be used to isolate transformations to light sources
//! or objects.
class Vrml_TransformSeparator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_TransformSeparator();

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream);

private:
  bool myFlagPrint;
};
