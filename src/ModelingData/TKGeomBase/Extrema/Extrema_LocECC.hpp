#pragma once

#include <Adaptor3d_Curve.hpp>

#include <Adaptor3d_Curve.hpp>
#include <Extrema_CurveTool.hpp>
#include <Extrema_GFuncExtCC.hpp>
#include <Extrema_POnCurv.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

using Extrema_CCLocFOfLocECC = Extrema_GFuncExtCC<Adaptor3d_Curve,
                                                  Extrema_CurveTool,
                                                  Adaptor3d_Curve,
                                                  Extrema_CurveTool,
                                                  Extrema_POnCurv,
                                                  gp_Pnt,
                                                  gp_Vec,
                                                  NCollection_Sequence<Extrema_POnCurv>>;

#include <Extrema_CurveTool.hpp>
#include <Extrema_GenLocateExtCC.hpp>
#include <Extrema_POnCurv.hpp>

using Extrema_LocECC = Extrema_GenLocateExtCC<Adaptor3d_Curve,
                                              Extrema_CurveTool,
                                              Extrema_POnCurv,
                                              Extrema_CCLocFOfLocECC>;
