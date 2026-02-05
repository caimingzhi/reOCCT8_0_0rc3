#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Draw_Interpretor.hpp>
#include <Standard_CString.hpp>

//! Provides DRAW interface to the functionalities of Shape Healing
//! toolkit (SHAPEWORKS Delivery Unit).
//!
//! Classes prefixed with Shape* corresponds to the packages of
//! Shape Healing.
class SWDRAW
{
public:
  DEFINE_STANDARD_ALLOC

  //! Loads commands defined in SWDRAW
  Standard_EXPORT static void Init(Draw_Interpretor& theCommands);

  //! Returns the name of the DRAW group accumulating the
  //! commands from the classes prefixed with Shape*.
  //! Returns "Shape Healing".
  Standard_EXPORT static const char* GroupName();
};
