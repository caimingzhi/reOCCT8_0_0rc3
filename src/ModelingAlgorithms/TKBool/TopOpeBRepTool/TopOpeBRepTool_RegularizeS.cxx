// Created on: 1999-01-06
// Created by: Xuan PHAM PHU
// Copyright (c) 1999-1999 Matra Datavision
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

#include <TopOpeBRepTool_REGUS.hpp>
#include <TopOpeBRepTool.hpp>
#include <TopoDS_Solid.hpp>
#include <TopExp_Explorer.hpp>
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

bool TopOpeBRepTool::RegularizeShells(
  const TopoDS_Solid& theSolid,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    OldSheNewShe,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    FSplits)
{
  OldSheNewShe.Clear();
  FSplits.Clear();
  TopOpeBRepTool_REGUS REGUS;
  REGUS.SetOshNsh(OldSheNewShe);
  REGUS.SetFsplits(FSplits);

  //  bool hastoregu = false;
  TopExp_Explorer exsh(theSolid, TopAbs_SHELL);
  for (; exsh.More(); exsh.Next())
  {

    const TopoDS_Shape& sh = exsh.Current();
    REGUS.Init(sh);
    bool ok = REGUS.MapS();
    if (!ok)
      return false;
    ok = REGUS.SplitFaces();
    if (!ok)
      return false;
    REGUS.REGU();

  } // exsh(theSolid)

  REGUS.GetOshNsh(OldSheNewShe); //??????????????????????????????
  REGUS.GetFsplits(FSplits);     //??????????????????????????????
  return true;
}
