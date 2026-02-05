#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

//! Contains commands to activate package ShapeProcessAPI
class SWDRAW_ShapeProcessAPI
{
public:
  DEFINE_STANDARD_ALLOC

  //! Loads commands defined in ShapeProcessAPI
  Standard_EXPORT static void InitCommands(Draw_Interpretor& theCommands);
};
