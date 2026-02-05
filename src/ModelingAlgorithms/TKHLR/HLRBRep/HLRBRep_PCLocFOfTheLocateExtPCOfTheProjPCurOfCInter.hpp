#pragma once

#include <Extrema_GFuncExtPC.hpp>
#include <Extrema_POnCurv2d.hpp>
#include <HLRBRep_TypeDef.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <HLRBRep_CurveTool.hpp>
#include <Standard_TypeDef.hpp>

//! Type alias for 2D curve extremum function using HLRBRep_CurveTool.
using HLRBRep_PCLocFOfTheLocateExtPCOfTheProjPCurOfCInter =
  Extrema_GFuncExtPC<HLRBRep_CurvePtr,
                     HLRBRep_CurveTool,
                     Extrema_POnCurv2d,
                     gp_Pnt2d,
                     gp_Vec2d,
                     NCollection_Sequence<Extrema_POnCurv2d>>;
