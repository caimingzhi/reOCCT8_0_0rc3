#pragma once

#include <Extrema_GenLocateExtPC.hpp>
#include <Extrema_POnCurv2d.hpp>
#include <HLRBRep_TypeDef.hpp>
#include <gp_Pnt2d.hpp>
#include <HLRBRep_CurveTool.hpp>
#include <HLRBRep_PCLocFOfTheLocateExtPCOfTheProjPCurOfCInter.hpp>
#include <Standard_TypeDef.hpp>

//! Type alias for HLRBRep local extremum search.
using HLRBRep_TheLocateExtPCOfTheProjPCurOfCInter =
  Extrema_GenLocateExtPC<HLRBRep_CurvePtr,
                         HLRBRep_CurveTool,
                         Extrema_POnCurv2d,
                         gp_Pnt2d,
                         HLRBRep_PCLocFOfTheLocateExtPCOfTheProjPCurOfCInter>;
