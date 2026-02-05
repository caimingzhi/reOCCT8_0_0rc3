#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

//! Contains commands to activate package ShapeAnalysis
//! List of DRAW commands and corresponding functionalities:
//! tolerance - ShapeAnalysis_ShapeTolerance
//! projcurve - ShapeAnalysis_Curve
//! projface  - ShapeAnalysis_Surface
class SWDRAW_ShapeAnalysis
{
public:
  DEFINE_STANDARD_ALLOC

  //! Loads commands defined in ShapeAnalysis
  Standard_EXPORT static void InitCommands(Draw_Interpretor& theCommands);
};
