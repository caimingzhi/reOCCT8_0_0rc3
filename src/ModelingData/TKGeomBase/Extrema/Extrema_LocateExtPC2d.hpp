#pragma once


#include <Adaptor2d_Curve2d.hpp>
#include <Extrema_Curve2dTool.hpp>
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
#include <Extrema_GGenExtPC.hpp>
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
#include <Extrema_GFuncExtPC.hpp>
#include <Extrema_POnCurv2d.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

//! Type alias for 2D point-curve extremum function (for LocateExtPC2d).
using Extrema_PCFOfEPCOfELPCOfLocateExtPC2d =
  Extrema_GFuncExtPC<Adaptor2d_Curve2d,
                     Extrema_Curve2dTool,
                     Extrema_POnCurv2d,
                     gp_Pnt2d,
                     gp_Vec2d,
                     NCollection_Sequence<Extrema_POnCurv2d>>;


#include <Extrema_POnCurv2d.hpp>
#include <gp_Pnt2d.hpp>

//! Type alias for 2D curve extremum point search for LocateExtPC.
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

//! Type alias for 2D point-to-curve extremum computation for LocateExtPC.
using Extrema_ELPCOfLocateExtPC2d = Extrema_GGExtPC<Adaptor2d_Curve2d,
                                                    Extrema_Curve2dTool,
                                                    Extrema_ExtPElC2d,
                                                    gp_Pnt2d,
                                                    gp_Vec2d,
                                                    Extrema_POnCurv2d,
                                                    NCollection_Sequence<Extrema_POnCurv2d>,
                                                    Extrema_EPCOfELPCOfLocateExtPC2d>;


#include <Extrema_GLocateExtPC.hpp>
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
#include <Extrema_GenLocateExtPC.hpp>
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
#include <Extrema_GFuncExtPC.hpp>
#include <Extrema_POnCurv2d.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

//! Type alias for 2D local point-curve extremum function.
using Extrema_PCLocFOfLocEPCOfLocateExtPC2d =
  Extrema_GFuncExtPC<Adaptor2d_Curve2d,
                     Extrema_Curve2dTool,
                     Extrema_POnCurv2d,
                     gp_Pnt2d,
                     gp_Vec2d,
                     NCollection_Sequence<Extrema_POnCurv2d>>;


#include <Extrema_POnCurv2d.hpp>
#include <gp_Pnt2d.hpp>

//! Type alias for 2D curve local extremum search.
using Extrema_LocEPCOfLocateExtPC2d = Extrema_GenLocateExtPC<Adaptor2d_Curve2d,
                                                             Extrema_Curve2dTool,
                                                             Extrema_POnCurv2d,
                                                             gp_Pnt2d,
                                                             Extrema_PCLocFOfLocEPCOfLocateExtPC2d>;


#include <Extrema_POnCurv2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

//! Type alias for 2D curve extremum locator.
using Extrema_LocateExtPC2d = Extrema_GLocateExtPC<Adaptor2d_Curve2d,
                                                   Extrema_Curve2dTool,
                                                   gp_Pnt2d,
                                                   gp_Vec2d,
                                                   Extrema_POnCurv2d,
                                                   Extrema_ELPCOfLocateExtPC2d,
                                                   Extrema_LocEPCOfLocateExtPC2d>;

