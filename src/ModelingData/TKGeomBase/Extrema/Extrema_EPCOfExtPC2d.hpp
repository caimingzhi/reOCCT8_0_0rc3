#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Extrema_Curve2dTool.hpp>
#include <Extrema_GGenExtPC.hpp>

#include <Adaptor2d_Curve2d.hpp>
#include <Extrema_Curve2dTool.hpp>
#include <Extrema_GFuncExtPC.hpp>
#include <Extrema_POnCurv2d.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

//! Type alias for 2D point-curve extremum function.
using Extrema_PCFOfEPCOfExtPC2d = Extrema_GFuncExtPC<Adaptor2d_Curve2d,
                                                     Extrema_Curve2dTool,
                                                     Extrema_POnCurv2d,
                                                     gp_Pnt2d,
                                                     gp_Vec2d,
                                                     NCollection_Sequence<Extrema_POnCurv2d>>;

#include <Extrema_POnCurv2d.hpp>
#include <gp_Pnt2d.hpp>

//! Type alias for 2D curve extremum point search using Extrema_Curve2dTool.
using Extrema_EPCOfExtPC2d = Extrema_GGenExtPC<Adaptor2d_Curve2d,
                                               Extrema_Curve2dTool,
                                               Extrema_POnCurv2d,
                                               gp_Pnt2d,
                                               Extrema_PCFOfEPCOfExtPC2d>;
