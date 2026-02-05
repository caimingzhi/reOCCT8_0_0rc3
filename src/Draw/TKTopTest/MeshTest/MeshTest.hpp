#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Draw_Interpretor.hpp>

//! Provides methods for testing the mesh algorithms.
class MeshTest
{
public:
  DEFINE_STANDARD_ALLOC

  //! Defines meshing commands
  Standard_EXPORT static void Commands(Draw_Interpretor& DI);

  //! Defines plugin commands
  Standard_EXPORT static void PluginCommands(Draw_Interpretor& DI);
};
