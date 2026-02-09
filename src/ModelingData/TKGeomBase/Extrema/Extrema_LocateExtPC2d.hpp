#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Extrema_Curve2dTool.hpp>

#include <Adaptor2d_Curve2d.hpp>
#include <Extrema_Curve2dTool.hpp>

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

using Extrema_PCFOfEPCOfELPCOfLocateExtPC2d =
  Extrema_GFuncExtPC<Adaptor2d_Curve2d,
                     Extrema_Curve2dTool,
                     Extrema_POnCurv2d,
                     gp_Pnt2d,
                     gp_Vec2d,
                     NCollection_Sequence<Extrema_POnCurv2d>>;

#include <Extrema_POnCurv2d.hpp>
#include <gp_Pnt2d.hpp>

using Extrema_EPCOfELPCOfLocateExtPC2d = Extrema_GGenExtPC<Adaptor2d_Curve2d,
                                                           Extrema_Curve2dTool,
                                                           Extrema_POnCurv2d,
                                                           gp_Pnt2d,
                                                           Extrema_PCFOfEPCOfELPCOfLocateExtPC2d>;

#include <Extrema_ExtPElC2d.hpp>
#include <Extrema_GGExtPC.hpp>
#include <Extrema_POnCurv2d.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

using Extrema_ELPCOfLocateExtPC2d = Extrema_GGExtPC<Adaptor2d_Curve2d,
                                                    Extrema_Curve2dTool,
                                                    Extrema_ExtPElC2d,
                                                    gp_Pnt2d,
                                                    gp_Vec2d,
                                                    Extrema_POnCurv2d,
                                                    NCollection_Sequence<Extrema_POnCurv2d>,
                                                    Extrema_EPCOfELPCOfLocateExtPC2d>;

#include <Extrema_GLocateExtPC.hpp>

#include <Adaptor2d_Curve2d.hpp>
#include <Extrema_Curve2dTool.hpp>
#include <Extrema_GenLocateExtPC.hpp>

#include <Adaptor2d_Curve2d.hpp>
#include <Extrema_Curve2dTool.hpp>
#include <Extrema_GFuncExtPC.hpp>
#include <Extrema_POnCurv2d.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

using Extrema_PCLocFOfLocEPCOfLocateExtPC2d =
  Extrema_GFuncExtPC<Adaptor2d_Curve2d,
                     Extrema_Curve2dTool,
                     Extrema_POnCurv2d,
                     gp_Pnt2d,
                     gp_Vec2d,
                     NCollection_Sequence<Extrema_POnCurv2d>>;

#include <Extrema_POnCurv2d.hpp>
#include <gp_Pnt2d.hpp>

using Extrema_LocEPCOfLocateExtPC2d = Extrema_GenLocateExtPC<Adaptor2d_Curve2d,
                                                             Extrema_Curve2dTool,
                                                             Extrema_POnCurv2d,
                                                             gp_Pnt2d,
                                                             Extrema_PCLocFOfLocEPCOfLocateExtPC2d>;

#include <Extrema_POnCurv2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

using Extrema_LocateExtPC2d = Extrema_GLocateExtPC<Adaptor2d_Curve2d,
                                                   Extrema_Curve2dTool,
                                                   gp_Pnt2d,
                                                   gp_Vec2d,
                                                   Extrema_POnCurv2d,
                                                   Extrema_ELPCOfLocateExtPC2d,
                                                   Extrema_LocEPCOfLocateExtPC2d>;
