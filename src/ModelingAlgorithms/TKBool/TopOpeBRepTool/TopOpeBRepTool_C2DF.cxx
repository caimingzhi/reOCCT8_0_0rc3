// Created on: 1998-03-23
// Created by: Jean Yves LEBEY
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

#include <Geom2d_Curve.hpp>
#include <TopOpeBRepTool_C2DF.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopAbs_State.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_List.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>
#include <TCollection_AsciiString.hpp>

//=================================================================================================

TopOpeBRepTool_C2DF::TopOpeBRepTool_C2DF() = default;

//=================================================================================================

TopOpeBRepTool_C2DF::TopOpeBRepTool_C2DF(const occ::handle<Geom2d_Curve>& PC,
                                         const double                     f2d,
                                         const double                     l2d,
                                         const double                     tol,
                                         const TopoDS_Face&               F)
{
  myPC   = PC;
  myf2d  = f2d;
  myl2d  = l2d;
  mytol  = tol;
  myFace = F;
}

//=================================================================================================

void TopOpeBRepTool_C2DF::SetPC(const occ::handle<Geom2d_Curve>& PC,
                                const double                     f2d,
                                const double                     l2d,
                                const double                     tol)
{
  myPC  = PC;
  myf2d = f2d;
  myl2d = l2d;
  mytol = tol;
}

//=================================================================================================

void TopOpeBRepTool_C2DF::SetFace(const TopoDS_Face& F)
{
  myFace = F;
}

//=================================================================================================

const occ::handle<Geom2d_Curve>& TopOpeBRepTool_C2DF::PC(double& f2d,
                                                         double& l2d,
                                                         double& tol) const
{
  f2d = myf2d;
  l2d = myl2d;
  tol = mytol;
  return myPC;
}

//=================================================================================================

const TopoDS_Face& TopOpeBRepTool_C2DF::Face() const
{
  return myFace;
}

//=================================================================================================

bool TopOpeBRepTool_C2DF::IsPC(const occ::handle<Geom2d_Curve>& PC) const
{
  bool b = (PC == myPC);
  return b;
}

//=================================================================================================

bool TopOpeBRepTool_C2DF::IsFace(const TopoDS_Face& F) const
{
  bool b = (F.IsEqual(myFace));
  return b;
}
