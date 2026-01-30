// Created on: 1998-05-18
// Created by: Philippe NOUAILLE
// Copyright (c) 1998-1999 Matra Datavision
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

#include <Blend_CurvPointFuncInv.hpp>
#include <Blend_FuncInv.hpp>
#include <BRepBlend_Line.hpp>
#include <BRepTopAdaptor_TopolTool.hpp>
#include <ChFi3d_Builder.hpp>
#include <ChFiDS_ElSpine.hpp>
#include <ChFiDS_Spine.hpp>
#include <ChFiDS_SurfData.hpp>
#include <TopOpeBRepBuild_HBuilder.hpp>

//=================================================================================================

void ChFi3d_Builder::SimulSurf(occ::handle<ChFiDS_SurfData>&,
                               const occ::handle<ChFiDS_ElSpine>&,
                               const occ::handle<ChFiDS_Spine>&,
                               const int,
                               const occ::handle<BRepAdaptor_Surface>&,
                               const occ::handle<Adaptor3d_TopolTool>&,
                               const occ::handle<BRepAdaptor_Curve2d>&,
                               const occ::handle<BRepAdaptor_Surface>&,
                               const occ::handle<BRepAdaptor_Curve2d>&,
                               bool&,
                               const occ::handle<BRepAdaptor_Surface>&,
                               const occ::handle<Adaptor3d_TopolTool>&,
                               const TopAbs_Orientation,
                               const double,
                               const double,
                               double&,
                               double&,
                               const bool,
                               const bool,
                               const bool,
                               const bool,
                               const bool,
                               const bool,
                               const math_Vector&)
{
  throw Standard_Failure("SimulSurf Not Implemented");
}

//=================================================================================================

void ChFi3d_Builder::SimulSurf(occ::handle<ChFiDS_SurfData>&,
                               const occ::handle<ChFiDS_ElSpine>&,
                               const occ::handle<ChFiDS_Spine>&,
                               const int,
                               const occ::handle<BRepAdaptor_Surface>&,
                               const occ::handle<Adaptor3d_TopolTool>&,
                               const TopAbs_Orientation,
                               const occ::handle<BRepAdaptor_Surface>&,
                               const occ::handle<Adaptor3d_TopolTool>&,
                               const occ::handle<BRepAdaptor_Curve2d>&,
                               const occ::handle<BRepAdaptor_Surface>&,
                               const occ::handle<BRepAdaptor_Curve2d>&,
                               bool&,
                               const double,
                               const double,
                               double&,
                               double&,
                               const bool,
                               const bool,
                               const bool,
                               const bool,
                               const bool,
                               const bool,
                               const math_Vector&)
{
  throw Standard_Failure("SimulSurf Not Implemented");
}

//=================================================================================================

void ChFi3d_Builder::SimulSurf(occ::handle<ChFiDS_SurfData>&,
                               const occ::handle<ChFiDS_ElSpine>&,
                               const occ::handle<ChFiDS_Spine>&,
                               const int,
                               const occ::handle<BRepAdaptor_Surface>&,
                               const occ::handle<Adaptor3d_TopolTool>&,
                               const occ::handle<BRepAdaptor_Curve2d>&,
                               const occ::handle<BRepAdaptor_Surface>&,
                               const occ::handle<BRepAdaptor_Curve2d>&,
                               bool&,
                               const TopAbs_Orientation,
                               const occ::handle<BRepAdaptor_Surface>&,
                               const occ::handle<Adaptor3d_TopolTool>&,
                               const occ::handle<BRepAdaptor_Curve2d>&,
                               const occ::handle<BRepAdaptor_Surface>&,
                               const occ::handle<BRepAdaptor_Curve2d>&,
                               bool&,
                               const TopAbs_Orientation,
                               const double,
                               const double,
                               double&,
                               double&,
                               const bool,
                               const bool,
                               const bool,
                               const bool,
                               const bool,
                               const bool,
                               const bool,
                               const math_Vector&)
{
  throw Standard_Failure("SimulSurf Not Implemented");
}

//=================================================================================================

void ChFi3d_Builder::PerformSurf(NCollection_Sequence<occ::handle<ChFiDS_SurfData>>&,
                                 const occ::handle<ChFiDS_ElSpine>&,
                                 const occ::handle<ChFiDS_Spine>&,
                                 const int,
                                 const occ::handle<BRepAdaptor_Surface>&,
                                 const occ::handle<Adaptor3d_TopolTool>&,
                                 const occ::handle<BRepAdaptor_Curve2d>&,
                                 const occ::handle<BRepAdaptor_Surface>&,
                                 const occ::handle<BRepAdaptor_Curve2d>&,
                                 bool&,
                                 const occ::handle<BRepAdaptor_Surface>&,
                                 const occ::handle<Adaptor3d_TopolTool>&,
                                 const TopAbs_Orientation,
                                 const double,
                                 const double,
                                 const double,
                                 double&,
                                 double&,
                                 const bool,
                                 const bool,
                                 const bool,
                                 const bool,
                                 const bool,
                                 const bool,
                                 const math_Vector&)
{
  throw Standard_Failure("PerformSurf Not Implemented");
}

//=================================================================================================

void ChFi3d_Builder::PerformSurf(NCollection_Sequence<occ::handle<ChFiDS_SurfData>>&,
                                 const occ::handle<ChFiDS_ElSpine>&,
                                 const occ::handle<ChFiDS_Spine>&,
                                 const int,
                                 const occ::handle<BRepAdaptor_Surface>&,
                                 const occ::handle<Adaptor3d_TopolTool>&,
                                 const TopAbs_Orientation,
                                 const occ::handle<BRepAdaptor_Surface>&,
                                 const occ::handle<Adaptor3d_TopolTool>&,
                                 const occ::handle<BRepAdaptor_Curve2d>&,
                                 const occ::handle<BRepAdaptor_Surface>&,
                                 const occ::handle<BRepAdaptor_Curve2d>&,
                                 bool&,
                                 const double,
                                 const double,
                                 const double,
                                 double&,
                                 double&,
                                 const bool,
                                 const bool,
                                 const bool,
                                 const bool,
                                 const bool,
                                 const bool,
                                 const math_Vector&)
{
  throw Standard_Failure("PerformSurf Not Implemented");
}

//=================================================================================================

void ChFi3d_Builder::PerformSurf(NCollection_Sequence<occ::handle<ChFiDS_SurfData>>&,
                                 const occ::handle<ChFiDS_ElSpine>&,
                                 const occ::handle<ChFiDS_Spine>&,
                                 const int,
                                 const occ::handle<BRepAdaptor_Surface>&,
                                 const occ::handle<Adaptor3d_TopolTool>&,
                                 const occ::handle<BRepAdaptor_Curve2d>&,
                                 const occ::handle<BRepAdaptor_Surface>&,
                                 const occ::handle<BRepAdaptor_Curve2d>&,
                                 bool&,
                                 const TopAbs_Orientation,
                                 const occ::handle<BRepAdaptor_Surface>&,
                                 const occ::handle<Adaptor3d_TopolTool>&,
                                 const occ::handle<BRepAdaptor_Curve2d>&,
                                 const occ::handle<BRepAdaptor_Surface>&,
                                 const occ::handle<BRepAdaptor_Curve2d>&,
                                 bool&,
                                 const TopAbs_Orientation,
                                 const double,
                                 const double,
                                 const double,
                                 double&,
                                 double&,
                                 const bool,
                                 const bool,
                                 const bool,
                                 const bool,
                                 const bool,
                                 const bool,
                                 const bool,
                                 const math_Vector&)
{
  throw Standard_Failure("PerformSurf Not Implemented");
}
