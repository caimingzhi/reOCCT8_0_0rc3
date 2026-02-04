#pragma once


#include <Adaptor2d_Curve2d.hpp>
#include <Extrema_GenLocateExtPC.hpp>
#include <Extrema_POnCurv2d.hpp>
#include <Geom2dInt_Geom2dCurveTool.hpp>
#include <Geom2dInt_PCLocFOfTheLocateExtPCOfTheProjPCurOfGInter.hpp>
#include <gp_Pnt2d.hpp>

//! Type alias for Geom2dInt local extremum search.
using Geom2dInt_TheLocateExtPCOfTheProjPCurOfGInter =
  Extrema_GenLocateExtPC<Adaptor2d_Curve2d,
                         Geom2dInt_Geom2dCurveTool,
                         Extrema_POnCurv2d,
                         gp_Pnt2d,
                         Geom2dInt_PCLocFOfTheLocateExtPCOfTheProjPCurOfGInter>;

