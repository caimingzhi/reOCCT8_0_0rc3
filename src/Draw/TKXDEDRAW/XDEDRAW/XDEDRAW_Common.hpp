#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

class XDEDRAW_Common
{
  DEFINE_STANDARD_ALLOC
public:
  Standard_EXPORT static void InitCommands(Draw_Interpretor& theCommands);
};
