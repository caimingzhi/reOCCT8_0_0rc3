// Created on: 1992-03-04
// Created by: Laurent BUCHARD
// Copyright (c) 1992-1999 Matra Datavision
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

#include <IntCurve_IntImpConicParConic.hpp>

#include <Standard_ConstructionError.hpp>
#include <IntCurve_IConicTool.hpp>
#include <IntCurve_PConic.hpp>
#include <IntCurve_PConicTool.hpp>
#include <IntCurve_ProjectOnPConicTool.hpp>
#include <IntCurve_MyImpParToolOfIntImpConicParConic.hpp>
#include <IntRes2d_Domain.hpp>
#include <gp_Pnt2d.hpp>

#define ImpTool IntCurve_IConicTool
#define ImpTool_hxx <IntCurve_IConicTool.hpp>
#define ParCurve IntCurve_PConic
#define ParCurve_hxx <IntCurve_PConic.hpp>
#define ParTool IntCurve_PConicTool
#define ParTool_hxx <IntCurve_PConicTool.hpp>
#define ProjectOnPCurveTool IntCurve_ProjectOnPConicTool
#define ProjectOnPCurveTool_hxx <IntCurve_ProjectOnPConicTool.hpp>
#define IntImpParGen_MyImpParTool IntCurve_MyImpParToolOfIntImpConicParConic
#define IntImpParGen_MyImpParTool_hxx <IntCurve_MyImpParToolOfIntImpConicParConic.hpp>
#define IntImpParGen_Intersector IntCurve_IntImpConicParConic
#define IntImpParGen_Intersector_hxx <IntCurve_IntImpConicParConic.hpp>
#include <IntImpParGen_Intersector.hpp>
