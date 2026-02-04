#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

//! Contains commands to activate package ShapeProcess
class SWDRAW_ShapeProcess
{
public:
  DEFINE_STANDARD_ALLOC

  //! Loads commands defined in ShapeProc
  Standard_EXPORT static void InitCommands(Draw_Interpretor& theCommands);
};

