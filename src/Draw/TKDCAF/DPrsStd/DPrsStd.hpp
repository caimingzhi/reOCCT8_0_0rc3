#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

class DPrsStd
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void AllCommands(Draw_Interpretor& I);

  Standard_EXPORT static void AISPresentationCommands(Draw_Interpretor& I);

  Standard_EXPORT static void AISViewerCommands(Draw_Interpretor& I);

  Standard_EXPORT static void BasicCommands(Draw_Interpretor& I);

  Standard_EXPORT static void Factory(Draw_Interpretor& theDI);
};
