#pragma once


#include <Adaptor2d_Curve2d.hpp>
// Created on: 1991-02-26
// Created by: Isabelle GRIGNON
// Copyright (c) 1991-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.


#include <Adaptor2d_Curve2d.hpp>
#include <Extrema_Curve2dTool.hpp>
#include <Extrema_GFuncExtCC.hpp>
#include <Extrema_POnCurv2d.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

//! Type alias for 2D curve-curve extremum function.
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

//! Type alias for 2D curve-curve local extremum locator.
using Extrema_LocECC2d = Extrema_GenLocateExtCC<Adaptor2d_Curve2d,
                                                Extrema_Curve2dTool,
                                                Extrema_POnCurv2d,
                                                Extrema_CCLocFOfLocECC2d>;

