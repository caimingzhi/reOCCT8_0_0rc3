#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

//! Contains commands to work with geometric validation
//! properties of shapes
class XDEDRAW_Props
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void InitCommands(Draw_Interpretor& theCommands);
};

