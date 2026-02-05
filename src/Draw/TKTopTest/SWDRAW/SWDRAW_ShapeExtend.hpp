#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

//! Contains commands to activate package ShapeExtend
//! List of DRAW commands and corresponding functionalities:
//! sortcompound - ShapeExtend_Explorer::SortedCompound
class SWDRAW_ShapeExtend
{
public:
  DEFINE_STANDARD_ALLOC

  //! Loads commands defined in ShapeExtend
  Standard_EXPORT static void InitCommands(Draw_Interpretor& theCommands);
};
