#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Extrema_GFuncExtPC.hpp>
#include <Extrema_POnCurv2d.hpp>
#include <NCollection_Sequence.hpp>
#include <Geom2dInt_Geom2dCurveTool.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

using Geom2dInt_PCLocFOfTheLocateExtPCOfTheProjPCurOfGInter =
  Extrema_GFuncExtPC<Adaptor2d_Curve2d,
                     Geom2dInt_Geom2dCurveTool,
                     Extrema_POnCurv2d,
                     gp_Pnt2d,
                     gp_Vec2d,
                     NCollection_Sequence<Extrema_POnCurv2d>>;
