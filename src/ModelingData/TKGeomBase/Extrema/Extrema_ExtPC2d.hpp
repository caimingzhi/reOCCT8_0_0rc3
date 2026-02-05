#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Extrema_Curve2dTool.hpp>
#include <Extrema_EPCOfExtPC2d.hpp>
#include <Extrema_ExtPElC2d.hpp>
#include <Extrema_GGExtPC.hpp>
#include <Extrema_POnCurv2d.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

//! Type alias for 2D point-to-curve extremum computation.
using Extrema_ExtPC2d = Extrema_GGExtPC<Adaptor2d_Curve2d,
                                        Extrema_Curve2dTool,
                                        Extrema_ExtPElC2d,
                                        gp_Pnt2d,
                                        gp_Vec2d,
                                        Extrema_POnCurv2d,
                                        NCollection_Sequence<Extrema_POnCurv2d>,
                                        Extrema_EPCOfExtPC2d>;
