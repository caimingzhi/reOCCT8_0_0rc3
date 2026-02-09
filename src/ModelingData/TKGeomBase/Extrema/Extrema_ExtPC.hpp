#pragma once

#include <Adaptor3d_Curve.hpp>
#include <Extrema_CurveTool.hpp>

#include <Adaptor3d_Curve.hpp>
#include <Extrema_CurveTool.hpp>
#include <Extrema_GGenExtPC.hpp>

#include <Adaptor3d_Curve.hpp>
#include <Extrema_CurveTool.hpp>
#include <Extrema_GFuncExtPC.hpp>
#include <Extrema_POnCurv.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

using Extrema_PCFOfEPCOfExtPC = Extrema_GFuncExtPC<Adaptor3d_Curve,
                                                   Extrema_CurveTool,
                                                   Extrema_POnCurv,
                                                   gp_Pnt,
                                                   gp_Vec,
                                                   NCollection_Sequence<Extrema_POnCurv>>;

#include <Extrema_POnCurv.hpp>
#include <gp_Pnt.hpp>

using Extrema_EPCOfExtPC = Extrema_GGenExtPC<Adaptor3d_Curve,
                                             Extrema_CurveTool,
                                             Extrema_POnCurv,
                                             gp_Pnt,
                                             Extrema_PCFOfEPCOfExtPC>;

#include <Extrema_ExtPElC.hpp>
#include <Extrema_GGExtPC.hpp>
#include <Extrema_POnCurv.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

using Extrema_ExtPC = Extrema_GGExtPC<Adaptor3d_Curve,
                                      Extrema_CurveTool,
                                      Extrema_ExtPElC,
                                      gp_Pnt,
                                      gp_Vec,
                                      Extrema_POnCurv,
                                      NCollection_Sequence<Extrema_POnCurv>,
                                      Extrema_EPCOfExtPC>;
