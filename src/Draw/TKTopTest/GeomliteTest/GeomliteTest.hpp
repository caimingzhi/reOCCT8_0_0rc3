#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Draw_Interpretor.hpp>

class GeomliteTest
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void AllCommands(Draw_Interpretor& I);

  Standard_EXPORT static void CurveCommands(Draw_Interpretor& I);

  Standard_EXPORT static void SurfaceCommands(Draw_Interpretor& I);

  Standard_EXPORT static void API2dCommands(Draw_Interpretor& I);

  Standard_EXPORT static void ApproxCommands(Draw_Interpretor& I);

  Standard_EXPORT static void ModificationCommands(Draw_Interpretor& I);
};
