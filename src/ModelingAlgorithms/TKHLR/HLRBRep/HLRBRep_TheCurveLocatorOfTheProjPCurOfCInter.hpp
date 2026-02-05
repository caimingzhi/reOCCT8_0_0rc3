#pragma once

#include <Extrema_GCurveLocator.hpp>
#include <Extrema_POnCurv2d.hpp>
#include <HLRBRep_TypeDef.hpp>
#include <gp_Pnt2d.hpp>
#include <HLRBRep_CurveTool.hpp>
#include <Standard_TypeDef.hpp>

//! Type alias for curve locator using HLRBRep_CurveTool.
using HLRBRep_TheCurveLocatorOfTheProjPCurOfCInter =
  Extrema_GCurveLocator<HLRBRep_CurvePtr, HLRBRep_CurveTool, Extrema_POnCurv2d, gp_Pnt2d>;
