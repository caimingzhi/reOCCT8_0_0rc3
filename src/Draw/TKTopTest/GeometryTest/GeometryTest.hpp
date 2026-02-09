#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Draw_Interpretor.hpp>

class GeometryTest
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void AllCommands(Draw_Interpretor& I);

  Standard_EXPORT static void CurveCommands(Draw_Interpretor& I);

  Standard_EXPORT static void CurveTanCommands(Draw_Interpretor& I);

  Standard_EXPORT static void FairCurveCommands(Draw_Interpretor& I);

  Standard_EXPORT static void SurfaceCommands(Draw_Interpretor& I);

  Standard_EXPORT static void ConstraintCommands(Draw_Interpretor& I);

  Standard_EXPORT static void APICommands(Draw_Interpretor& I);

  Standard_EXPORT static void ContinuityCommands(Draw_Interpretor& I);

  Standard_EXPORT static void PolyCommands(Draw_Interpretor& I);

  Standard_EXPORT static void TestProjCommands(Draw_Interpretor& I);
};
