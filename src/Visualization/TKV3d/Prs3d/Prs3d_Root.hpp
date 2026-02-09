#pragma once

#include <Graphic3d_Group.hpp>
#include <Prs3d_Presentation.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Prs3d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_DEPRECATED("This method is deprecated - Prs3d_Presentation::CurrentGroup() should be "
                      "called instead")

  static occ::handle<Graphic3d_Group> CurrentGroup(const occ::handle<Prs3d_Presentation>& thePrs3d)
  {
    return thePrs3d->CurrentGroup();
  }

  Standard_DEPRECATED("This method is deprecated - Prs3d_Presentation::NewGroup() should be called "
                      "instead")

  static occ::handle<Graphic3d_Group> NewGroup(const occ::handle<Prs3d_Presentation>& thePrs3d)
  {
    return thePrs3d->NewGroup();
  }
};
