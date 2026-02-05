#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

//! Contains commands to activate package ShapeUpgrade
//! List of DRAW commands and corresponding functionalities:
//! DT_ShapeDivide         - ShapeUpgrade_ShapeDivide
//! DT_PlaneDividedFace    - ShapeUpgrade_PlaneDividedFace
//! DT_PlaneGridShell      - ShapeUpgrade_PlaneGridShell
//! DT_PlaneFaceCommon     - ShapeUpgrade_PlaneFaceCommon
//! DT_Split2dCurve        - ShapeUpgrade_Split2dCurve
//! DT_SplitCurve          - ShapeUpgrade_SplitCurve
//! DT_SplitSurface        - ShapeUpgrade_SplitSurface
//! DT_SupportModification - ShapeUpgrade_DataMapOfShapeSurface
//! DT_Debug               - ShapeUpgrade::SetDebug
//! shellsolid             - ShapeAnalysis_Shell/ShapeUpgrade_ShellSewing
class SWDRAW_ShapeUpgrade
{
public:
  DEFINE_STANDARD_ALLOC

  //! Loads commands defined in ShapeUpgrade
  Standard_EXPORT static void InitCommands(Draw_Interpretor& theCommands);
};
