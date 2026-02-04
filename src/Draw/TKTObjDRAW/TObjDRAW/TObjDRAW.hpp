#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

//! Provides DRAW commands for work with TObj data structures
class TObjDRAW
{
public:
  DEFINE_STANDARD_ALLOC

  //! Initializes all the functions
  Standard_EXPORT static void Init(Draw_Interpretor& di);

  //! Loads all Draw commands of TKTObjDRAW. Used for plugin.
  Standard_EXPORT static void Factory(Draw_Interpretor& theDI);
};

