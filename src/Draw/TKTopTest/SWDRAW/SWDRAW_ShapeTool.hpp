#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

//! Defines functions to control shapes (in way useful for XSTEP),
//! additional features which should be basic, or call tools which
//! are bound with transfer needs.
//! But these functions work on shapes, geometry, nothing else
//! (no file, no model, no entity)
class SWDRAW_ShapeTool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Defines and loads all basic functions for SWDRAW on Shapes
  Standard_EXPORT static void InitCommands(Draw_Interpretor& theCommands);
};

