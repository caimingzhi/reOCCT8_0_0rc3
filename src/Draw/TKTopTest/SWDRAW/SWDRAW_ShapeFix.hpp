#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

//! Contains commands to activate package ShapeFix
//! List of DRAW commands and corresponding functionalities:
//! edgesameparam - ShapeFix::SameParameter
//! settolerance  - ShapeFix_ShapeTolerance
//! stwire        - ShapeFix_Wire
//! reface        - ShapeFix_Face
//! repcurve      - ShapeFix_PCurves
class SWDRAW_ShapeFix
{
public:
  DEFINE_STANDARD_ALLOC

  //! Loads commands defined in ShapeFix
  Standard_EXPORT static void InitCommands(Draw_Interpretor& theCommands);
};
