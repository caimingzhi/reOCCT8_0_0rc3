#pragma once

#include <Adaptor2d_Curve2d.hpp>

#include <Adaptor2d_Curve2d.hpp>
#include <Extrema_Curve2dTool.hpp>
#include <Extrema_GFuncExtCC.hpp>
#include <Extrema_POnCurv2d.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

using Extrema_CCLocFOfLocECC2d = Extrema_GFuncExtCC<Adaptor2d_Curve2d,
                                                    Extrema_Curve2dTool,
                                                    Adaptor2d_Curve2d,
                                                    Extrema_Curve2dTool,
                                                    Extrema_POnCurv2d,
                                                    gp_Pnt2d,
                                                    gp_Vec2d,
                                                    NCollection_Sequence<Extrema_POnCurv2d>>;

#include <Extrema_Curve2dTool.hpp>
#include <Extrema_GenLocateExtCC.hpp>
#include <Extrema_POnCurv2d.hpp>

using Extrema_LocECC2d = Extrema_GenLocateExtCC<Adaptor2d_Curve2d,
                                                Extrema_Curve2dTool,
                                                Extrema_POnCurv2d,
                                                Extrema_CCLocFOfLocECC2d>;
