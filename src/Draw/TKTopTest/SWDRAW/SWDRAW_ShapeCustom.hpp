#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

//! Contains commands to activate package ShapeCustom
//! List of DRAW commands and corresponding functionalities:
//! directfaces - ShapeCustom::DirectFaces
//! scaleshape  - ShapeCustom::ScaleShape
class SWDRAW_ShapeCustom
{
public:
  DEFINE_STANDARD_ALLOC

  //! Loads commands defined in ShapeCustom
  Standard_EXPORT static void InitCommands(Draw_Interpretor& theCommands);
};
