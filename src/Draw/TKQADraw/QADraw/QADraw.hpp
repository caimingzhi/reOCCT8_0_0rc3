#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Draw_Interpretor.hpp>

class QADraw
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void CommonCommands(Draw_Interpretor& theCommands);

  Standard_EXPORT static void AdditionalCommands(Draw_Interpretor& theCommands);

  Standard_EXPORT static void TutorialCommands(Draw_Interpretor& theCommands);

  Standard_EXPORT static void Factory(Draw_Interpretor& theCommands);
};
