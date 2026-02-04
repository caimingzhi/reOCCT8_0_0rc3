#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

//! Contains commands to work with shapes and assemblies
class XDEDRAW_Shapes
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void InitCommands(Draw_Interpretor& theCommands);
};

