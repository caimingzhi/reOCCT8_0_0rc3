// Created on: 1995-01-30
// Created by: Marie Jose MARTZ
// Copyright (c) 1995-1999 Matra Datavision
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

#include <BRep_Tool.hpp>
#include <BRepToIGES_BRShell.hpp>
#include <BRepToIGES_BRSolid.hpp>
#include <BRepToIGES_BRWire.hpp>
#include <BRepTools.hpp>
#include <IGESBasic_Group.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <MoniTool_Macros.hpp>
#include <Message_ProgressScope.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_CompSolid.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Solid.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>

// At first only the geometry is translated (point, curve...)
//=============================================================================
// BRepToIGES_BRSolid
//=============================================================================
BRepToIGES_BRSolid::BRepToIGES_BRSolid() = default;

//=============================================================================
// BRepToIGES_BRSolid
//=============================================================================

BRepToIGES_BRSolid::BRepToIGES_BRSolid(const BRepToIGES_BREntity& BR)
    : BRepToIGES_BREntity(BR)
{
}

//=============================================================================
// TransferSolid
//=============================================================================

occ::handle<IGESData_IGESEntity> BRepToIGES_BRSolid ::TransferSolid(
  const TopoDS_Shape&          start,
  const Message_ProgressRange& theProgress)
{
  occ::handle<IGESData_IGESEntity> res;

  if (start.IsNull())
    return res;

  if (start.ShapeType() == TopAbs_SOLID)
  {
    TopoDS_Solid M = TopoDS::Solid(start);
    res            = TransferSolid(M, theProgress);
  }
  else if (start.ShapeType() == TopAbs_COMPSOLID)
  {
    TopoDS_CompSolid C = TopoDS::CompSolid(start);
    res                = TransferCompSolid(C, theProgress);
  }
  else if (start.ShapeType() == TopAbs_COMPOUND)
  {
    TopoDS_Compound C = TopoDS::Compound(start);
    res               = TransferCompound(C, theProgress);
  }
  else
  {
    // error message
  }
  return res;
}

//=============================================================================
// TransferSolid
//
//=============================================================================

occ::handle<IGESData_IGESEntity> BRepToIGES_BRSolid ::TransferSolid(
  const TopoDS_Solid&          start,
  const Message_ProgressRange& theProgress)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
    return res;

  TopExp_Explorer                                                     Ex;
  occ::handle<IGESData_IGESEntity>                                    IShell;
  BRepToIGES_BRShell                                                  BS(*this);
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> Seq =
    new NCollection_HSequence<occ::handle<Standard_Transient>>();

  int nbshapes = 0;
  for (Ex.Init(start, TopAbs_SHELL); Ex.More(); Ex.Next())
    nbshapes++;
  Message_ProgressScope aPS(theProgress, nullptr, nbshapes);
  for (Ex.Init(start, TopAbs_SHELL); Ex.More() && aPS.More(); Ex.Next())
  {
    Message_ProgressRange aRange = aPS.Next();
    TopoDS_Shell          S      = TopoDS::Shell(Ex.Current());
    if (S.IsNull())
    {
      AddWarning(start, " an Shell is a null entity");
    }
    else
    {
      IShell = BS.TransferShell(S, aRange);
      if (!IShell.IsNull())
        Seq->Append(IShell);
    }
  }

  int                                                                nbshells = Seq->Length();
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> Tab;
  if (nbshells >= 1)
  {
    Tab = new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, nbshells);
    for (int itab = 1; itab <= nbshells; itab++)
    {
      occ::handle<IGESData_IGESEntity> item = GetCasted(IGESData_IGESEntity, Seq->Value(itab));
      Tab->SetValue(itab, item);
    }
  }

  if (nbshells == 1)
  {
    res = IShell;
  }
  else
  {
    occ::handle<IGESBasic_Group> IGroup = new IGESBasic_Group;
    IGroup->Init(Tab);
    res = IGroup;
  }

  SetShapeResult(start, res);

  return res;
}

//=============================================================================
// TransferCompSolid
//=============================================================================

occ::handle<IGESData_IGESEntity> BRepToIGES_BRSolid ::TransferCompSolid(
  const TopoDS_CompSolid&      start,
  const Message_ProgressRange& theProgress)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
    return res;

  TopExp_Explorer                                                     Ex;
  occ::handle<IGESData_IGESEntity>                                    ISolid;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> Seq =
    new NCollection_HSequence<occ::handle<Standard_Transient>>();

  int nbshapes = 0;
  for (Ex.Init(start, TopAbs_SOLID); Ex.More(); Ex.Next())
    nbshapes++;
  Message_ProgressScope aPS(theProgress, nullptr, nbshapes);
  for (Ex.Init(start, TopAbs_SOLID); Ex.More() && aPS.More(); Ex.Next())
  {
    Message_ProgressRange aRange = aPS.Next();
    TopoDS_Solid          S      = TopoDS::Solid(Ex.Current());
    if (S.IsNull())
    {
      AddWarning(start, " an Solid is a null entity");
    }
    else
    {
      ISolid = TransferSolid(S, aRange);
      if (!ISolid.IsNull())
        Seq->Append(ISolid);
    }
  }

  int                                                                nbsolids = Seq->Length();
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> Tab;
  if (nbsolids >= 1)
  {
    Tab = new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, nbsolids);
    for (int itab = 1; itab <= nbsolids; itab++)
    {
      occ::handle<IGESData_IGESEntity> item = GetCasted(IGESData_IGESEntity, Seq->Value(itab));
      Tab->SetValue(itab, item);
    }
  }

  if (nbsolids == 1)
  {
    res = ISolid;
  }
  else
  {
    occ::handle<IGESBasic_Group> IGroup = new IGESBasic_Group;
    IGroup->Init(Tab);
    res = IGroup;
  }

  SetShapeResult(start, res);

  return res;
}

//=============================================================================
// TransferCompound
//=============================================================================

occ::handle<IGESData_IGESEntity> BRepToIGES_BRSolid ::TransferCompound(
  const TopoDS_Compound&       start,
  const Message_ProgressRange& theProgress)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
    return res;

  TopExp_Explorer                                                     Ex;
  occ::handle<IGESData_IGESEntity>                                    IShape;
  BRepToIGES_BRShell                                                  BS(*this);
  BRepToIGES_BRWire                                                   BW(*this);
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> Seq =
    new NCollection_HSequence<occ::handle<Standard_Transient>>();

  // count numbers of subshapes
  int nbshapes = 0;
  for (Ex.Init(start, TopAbs_SOLID); Ex.More(); Ex.Next())
    nbshapes++;
  for (Ex.Init(start, TopAbs_SHELL, TopAbs_SOLID); Ex.More(); Ex.Next())
    nbshapes++;
  for (Ex.Init(start, TopAbs_FACE, TopAbs_SHELL); Ex.More(); Ex.Next())
    nbshapes++;
  for (Ex.Init(start, TopAbs_WIRE, TopAbs_FACE); Ex.More(); Ex.Next())
    nbshapes++;
  for (Ex.Init(start, TopAbs_EDGE, TopAbs_WIRE); Ex.More(); Ex.Next())
    nbshapes++;
  for (Ex.Init(start, TopAbs_VERTEX, TopAbs_EDGE); Ex.More(); Ex.Next())
    nbshapes++;
  Message_ProgressScope aPS(theProgress, nullptr, nbshapes);

  // take all Solids
  for (Ex.Init(start, TopAbs_SOLID); Ex.More() && aPS.More(); Ex.Next())
  {
    Message_ProgressRange aRange = aPS.Next();
    TopoDS_Solid          S      = TopoDS::Solid(Ex.Current());
    if (S.IsNull())
    {
      AddWarning(start, " a Solid is a null entity");
    }
    else
    {
      IShape = TransferSolid(S, aRange);
      if (!IShape.IsNull())
        Seq->Append(IShape);
    }
  }

  // take all isolated Shells
  for (Ex.Init(start, TopAbs_SHELL, TopAbs_SOLID); Ex.More() && aPS.More(); Ex.Next())
  {
    Message_ProgressRange aRange = aPS.Next();
    TopoDS_Shell          S      = TopoDS::Shell(Ex.Current());
    if (S.IsNull())
    {
      AddWarning(start, " a Shell is a null entity");
    }
    else
    {
      IShape = BS.TransferShell(S, aRange);
      if (!IShape.IsNull())
        Seq->Append(IShape);
    }
  }

  // take all isolated Faces
  for (Ex.Init(start, TopAbs_FACE, TopAbs_SHELL); Ex.More() && aPS.More(); Ex.Next())
  {
    Message_ProgressRange aRange = aPS.Next();
    TopoDS_Face           S      = TopoDS::Face(Ex.Current());
    if (S.IsNull())
    {
      AddWarning(start, " a Face is a null entity");
    }
    else
    {
      IShape = BS.TransferFace(S, aRange);
      if (!IShape.IsNull())
        Seq->Append(IShape);
    }
  }

  // take all isolated Wires
  for (Ex.Init(start, TopAbs_WIRE, TopAbs_FACE); Ex.More() && aPS.More(); Ex.Next(), aPS.Next())
  {
    TopoDS_Wire S = TopoDS::Wire(Ex.Current());
    if (S.IsNull())
    {
      AddWarning(start, " a Wire is a null entity");
    }
    else
    {
      IShape = BW.TransferWire(S);
      if (!IShape.IsNull())
        Seq->Append(IShape);
    }
  }

  // take all isolated Edges
  for (Ex.Init(start, TopAbs_EDGE, TopAbs_WIRE); Ex.More() && aPS.More(); Ex.Next(), aPS.Next())
  {
    TopoDS_Edge S = TopoDS::Edge(Ex.Current());
    if (S.IsNull())
    {
      AddWarning(start, " an Edge is a null entity");
    }
    else
    {
      NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> anEmptyMap;
      IShape = BW.TransferEdge(S, anEmptyMap, false);
      if (!IShape.IsNull())
        Seq->Append(IShape);
    }
  }

  // take all isolated Vertices
  for (Ex.Init(start, TopAbs_VERTEX, TopAbs_EDGE); Ex.More() && aPS.More(); Ex.Next(), aPS.Next())
  {
    TopoDS_Vertex S = TopoDS::Vertex(Ex.Current());
    if (S.IsNull())
    {
      AddWarning(start, " a Vertex is a null entity");
    }
    else
    {
      IShape = BW.TransferVertex(S);
      if (!IShape.IsNull())
        Seq->Append(IShape);
    }
  }

  // construct the group
  nbshapes = Seq->Length();
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> Tab;
  if (nbshapes >= 1)
  {
    Tab = new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, nbshapes);
    for (int itab = 1; itab <= nbshapes; itab++)
    {
      occ::handle<IGESData_IGESEntity> item = GetCasted(IGESData_IGESEntity, Seq->Value(itab));
      Tab->SetValue(itab, item);
    }
  }

  if (nbshapes == 1)
  {
    res = IShape;
  }
  else
  {
    occ::handle<IGESBasic_Group> IGroup = new IGESBasic_Group;
    IGroup->Init(Tab);
    res = IGroup;
  }

  SetShapeResult(start, res);

  return res;
}
