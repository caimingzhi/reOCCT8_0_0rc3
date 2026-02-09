#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Draw_Interpretor.hpp>

class MeshTest
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Commands(Draw_Interpretor& DI);

  Standard_EXPORT static void PluginCommands(Draw_Interpretor& DI);
};
