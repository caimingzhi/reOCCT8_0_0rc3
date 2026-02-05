#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Extrema_Curve2dTool.hpp>
#include <Extrema_ExtPC2d.hpp>
#include <Extrema_GGenExtCC.hpp>
#include <Extrema_POnCurv2d.hpp>
#include <gp_Pnt2d.hpp>

//! Type alias for 2D curve-curve extremum computation.
using Extrema_ECC2d = Extrema_GGenExtCC<Adaptor2d_Curve2d,
                                        Extrema_Curve2dTool,
                                        Adaptor2d_Curve2d,
                                        Extrema_Curve2dTool,
                                        Extrema_POnCurv2d,
                                        gp_Pnt2d,
                                        Extrema_ExtPC2d>;
