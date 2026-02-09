#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Extrema_GCurveLocator.hpp>
#include <Extrema_POnCurv2d.hpp>
#include <Geom2dInt_Geom2dCurveTool.hpp>
#include <gp_Pnt2d.hpp>

using Geom2dInt_TheCurveLocatorOfTheProjPCurOfGInter =
  Extrema_GCurveLocator<Adaptor2d_Curve2d, Geom2dInt_Geom2dCurveTool, Extrema_POnCurv2d, gp_Pnt2d>;
