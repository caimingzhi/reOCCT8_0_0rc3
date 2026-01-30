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

#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <Transfer_TransientProcess.hpp>
#include <TransferBRep.hpp>
#include <XSControl_ConnectedShapes.hpp>
#include <XSControl_TransferReader.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XSControl_ConnectedShapes, IFSelect_SelectExplore)

XSControl_ConnectedShapes::XSControl_ConnectedShapes()
    : IFSelect_SelectExplore(1)
{
}

XSControl_ConnectedShapes::XSControl_ConnectedShapes(
  const occ::handle<XSControl_TransferReader>& TR)
    : IFSelect_SelectExplore(1),
      theTR(TR)
{
}

void XSControl_ConnectedShapes::SetReader(const occ::handle<XSControl_TransferReader>& TR)
{
  theTR = TR;
}

bool XSControl_ConnectedShapes::Explore(const int /*level*/,
                                        const occ::handle<Standard_Transient>& ent,
                                        const Interface_Graph& /*G*/,
                                        Interface_EntityIterator& explored) const
{
  occ::handle<Transfer_TransientProcess> TP;
  if (!theTR.IsNull())
    TP = theTR->TransientProcess();
  if (TP.IsNull())
    return false;
  TopoDS_Shape Shape = TransferBRep::ShapeResult(TP, ent);
  if (Shape.IsNull())
    return false;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> li =
    AdjacentEntities(Shape, TP, TopAbs_FACE);
  explored.AddList(li);
  return true;
}

TCollection_AsciiString XSControl_ConnectedShapes::ExploreLabel() const
{
  TCollection_AsciiString lab("Connected Entities through produced Shapes");
  return lab;
}

occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> XSControl_ConnectedShapes::
  AdjacentEntities(const TopoDS_Shape&                           ashape,
                   const occ::handle<Transfer_TransientProcess>& TP,
                   const TopAbs_ShapeEnum                        type)
{
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> li =
    new NCollection_HSequence<occ::handle<Standard_Transient>>();
  int i, nb = TP->NbMapped();
  //  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> adj (nb);
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> vtx(20);

  for (TopExp_Explorer vert(ashape, TopAbs_VERTEX); vert.More(); vert.Next())
  {
    vtx.Add(vert.Current());
  }

  for (i = 1; i <= nb; i++)
  {
    occ::handle<Transfer_Binder> bnd = TP->MapItem(i);
    TopoDS_Shape                 sh  = TransferBRep::ShapeResult(bnd);
    if (sh.IsNull())
      continue;
    if (sh.ShapeType() != type)
      continue;
    for (TopExp_Explorer vsh(sh, TopAbs_VERTEX); vsh.More(); vsh.Next())
    {
      const TopoDS_Shape& avtx = vsh.Current();
      if (vtx.Contains(avtx))
      {
        li->Append(TP->Mapped(i));
        break; // break from this inner for, next entity
      }
    }
  }

  return li;
}
