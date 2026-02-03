// Created by: Peter KURNEV
// Copyright (c) 1999-2012 OPEN CASCADE SAS
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

#ifndef _BOPAlgo_WireSplitter_HeaderFile
#define _BOPAlgo_WireSplitter_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
// Created by: Peter KURNEV
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

#ifndef _BOPAlgo_PWireEdgeSet_HeaderFile
#define _BOPAlgo_PWireEdgeSet_HeaderFile

class BOPAlgo_WireEdgeSet;
typedef BOPAlgo_WireEdgeSet* BOPAlgo_PWireEdgeSet;

#endif // _BOPAlgo_PWireEdgeSet_HeaderFile

#include <NCollection_List.hpp>
#include <BOPTools_ConnexityBlock.hpp>
#include <BOPAlgo_Algo.hpp>
#include <IntTools_Context.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <TopoDS_Shape.hpp>
class TopoDS_Wire;
class TopoDS_Face;

//! The class is to build loops from the given set of edges.
//!
//! It returns the following Error statuses
//! - *BOPAlgo_AlertNullInputShapes* - in case there no input edges to build the loops.
//!
class BOPAlgo_WireSplitter : public BOPAlgo_Algo
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPAlgo_WireSplitter();
  Standard_EXPORT ~BOPAlgo_WireSplitter() override;

  Standard_EXPORT BOPAlgo_WireSplitter(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  Standard_EXPORT void SetWES(const BOPAlgo_WireEdgeSet& theWES);

  Standard_EXPORT BOPAlgo_WireEdgeSet& WES();

  //! Sets the context for the algorithm
  Standard_EXPORT void SetContext(const occ::handle<IntTools_Context>& theContext);

  //! Returns the context
  Standard_EXPORT const occ::handle<IntTools_Context>& Context();

  Standard_EXPORT void Perform(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  static void MakeWire(NCollection_List<TopoDS_Shape>& theLE, TopoDS_Wire& theW);

  Standard_EXPORT static void SplitBlock(const TopoDS_Face&                   theF,
                                         BOPTools_ConnexityBlock&             theCB,
                                         const occ::handle<IntTools_Context>& theContext);

protected:
  Standard_EXPORT void CheckData() override;

  Standard_EXPORT void MakeWires(const Message_ProgressRange& theRange);

  BOPAlgo_PWireEdgeSet                      myWES;
  NCollection_List<BOPTools_ConnexityBlock> myLCB;
  occ::handle<IntTools_Context>             myContext;
};
// Created by: Peter KURNEV
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

#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>

#include <TopoDS_Edge.hpp>

//=================================================================================================

class BOPAlgo_EdgeInfo
{
public:
  //
  BOPAlgo_EdgeInfo()
      : myPassed(false),
        myInFlag(false),
        myIsInside(false),
        myAngle(-1.) {};

  //
  void SetEdge(const TopoDS_Edge& theE) { myEdge = theE; };

  //
  const TopoDS_Edge& Edge() const { return myEdge; };

  //
  void SetPassed(const bool theFlag) { myPassed = theFlag; };

  //
  bool Passed() const { return myPassed; };

  //
  void SetInFlag(const bool theFlag) { myInFlag = theFlag; };

  //
  bool IsIn() const { return myInFlag; };

  //
  void SetAngle(const double theAngle) { myAngle = theAngle; };

  //
  double Angle() const { return myAngle; };

  //
  bool IsInside() const { return myIsInside; };

  //
  void SetIsInside(const bool theIsInside) { myIsInside = theIsInside; };

  //
protected:
  TopoDS_Edge myEdge;
  bool        myPassed;
  bool        myInFlag;
  bool        myIsInside;
  double      myAngle;
};

#include <NCollection_List.hpp>

#include <NCollection_IndexedDataMap.hpp>
#include <TopTools_ShapeMapHasher.hpp>

//=================================================================================================

inline void BOPAlgo_WireSplitter::MakeWire(NCollection_List<TopoDS_Shape>& aLE, TopoDS_Wire& aWire)
{
  BRep_Builder aBB;
  aBB.MakeWire(aWire);
  //
  NCollection_List<TopoDS_Shape>::Iterator aIt(aLE);
  for (; aIt.More(); aIt.Next())
  {
    aBB.Add(aWire, aIt.Value());
  }
  aWire.Closed(BRep_Tool::IsClosed(aWire));
}


#endif // _BOPAlgo_WireSplitter_HeaderFile
