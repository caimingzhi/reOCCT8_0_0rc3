#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Draw_Interpretor.hpp>

//! Contains commands to work with GDTs
class XDEDRAW_GDTs
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void InitCommands(Draw_Interpretor& theCommands);
};

