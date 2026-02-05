#pragma once

#include <Adaptor3d_Curve.hpp>
#include <Extrema_CurveTool.hpp>

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

//! Type alias for 3D point-curve extremum function (for LocateExtPC).
using Extrema_PCFOfEPCOfELPCOfLocateExtPC =
  Extrema_GFuncExtPC<Adaptor3d_Curve,
                     Extrema_CurveTool,
                     Extrema_POnCurv,
                     gp_Pnt,
                     gp_Vec,
                     NCollection_Sequence<Extrema_POnCurv>>;

#include <Extrema_POnCurv.hpp>
#include <gp_Pnt.hpp>

//! Type alias for 3D curve extremum point search for LocateExtPC.
using Extrema_EPCOfELPCOfLocateExtPC = Extrema_GGenExtPC<Adaptor3d_Curve,
                                                         Extrema_CurveTool,
                                                         Extrema_POnCurv,
                                                         gp_Pnt,
                                                         Extrema_PCFOfEPCOfELPCOfLocateExtPC>;

#include <Extrema_ExtPElC.hpp>
#include <Extrema_GGExtPC.hpp>
#include <Extrema_POnCurv.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

//! Type alias for 3D point-to-curve extremum computation for LocateExtPC.
using Extrema_ELPCOfLocateExtPC = Extrema_GGExtPC<Adaptor3d_Curve,
                                                  Extrema_CurveTool,
                                                  Extrema_ExtPElC,
                                                  gp_Pnt,
                                                  gp_Vec,
                                                  Extrema_POnCurv,
                                                  NCollection_Sequence<Extrema_POnCurv>,
                                                  Extrema_EPCOfELPCOfLocateExtPC>;

#include <Extrema_GLocateExtPC.hpp>

#include <Adaptor3d_Curve.hpp>
#include <Extrema_CurveTool.hpp>
#include <Extrema_GenLocateExtPC.hpp>

#include <Adaptor3d_Curve.hpp>
#include <Extrema_CurveTool.hpp>
#include <Extrema_GFuncExtPC.hpp>
#include <Extrema_POnCurv.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

//! Type alias for 3D local point-curve extremum function.
using Extrema_PCLocFOfLocEPCOfLocateExtPC =
  Extrema_GFuncExtPC<Adaptor3d_Curve,
                     Extrema_CurveTool,
                     Extrema_POnCurv,
                     gp_Pnt,
                     gp_Vec,
                     NCollection_Sequence<Extrema_POnCurv>>;

#include <Extrema_POnCurv.hpp>
#include <gp_Pnt.hpp>

//! Type alias for 3D curve local extremum search.
using Extrema_LocEPCOfLocateExtPC = Extrema_GenLocateExtPC<Adaptor3d_Curve,
                                                           Extrema_CurveTool,
                                                           Extrema_POnCurv,
                                                           gp_Pnt,
                                                           Extrema_PCLocFOfLocEPCOfLocateExtPC>;

#include <Extrema_POnCurv.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

//! Type alias for 3D curve extremum locator.
using Extrema_LocateExtPC = Extrema_GLocateExtPC<Adaptor3d_Curve,
                                                 Extrema_CurveTool,
                                                 gp_Pnt,
                                                 gp_Vec,
                                                 Extrema_POnCurv,
                                                 Extrema_ELPCOfLocateExtPC,
                                                 Extrema_LocEPCOfLocateExtPC>;
