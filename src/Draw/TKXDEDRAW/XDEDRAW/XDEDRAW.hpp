#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

//! Provides DRAW commands for work with DECAF data structures
class XDEDRAW
{
  DEFINE_STANDARD_ALLOC
public:
  //! Provides common commands for work XDE
  //! Initializes all the functions
  Standard_EXPORT static void Init(Draw_Interpretor& di);

  //! Loads all Draw commands of TKXDEDRAW. Used for plugin.
  Standard_EXPORT static void Factory(Draw_Interpretor& theDI);
};
