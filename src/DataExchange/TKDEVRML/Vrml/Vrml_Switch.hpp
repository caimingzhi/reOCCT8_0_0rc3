#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_OStream.hpp>

//! defines a Switch node of VRML specifying group properties.
//! This group node traverses one, none, or all of its children.
//! One can use this node to switch on and off the effects of some
//! properties or to switch between different properties.
//! The whichChild field specifies the index of the child to traverse,
//! where the first child has index 0.
//! A value of -1 (the default) means do not traverse any children.
//! A value of -3 traverses all children, making the switch behave exactly
//! like a regular Group.
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

