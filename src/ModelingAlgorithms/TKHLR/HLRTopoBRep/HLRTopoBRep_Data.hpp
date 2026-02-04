#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>
#include <HLRTopoBRep_FaceData.hpp>
#include <NCollection_Map.hpp>
#include <HLRTopoBRep_VData.hpp>
#include <Standard_Boolean.hpp>
class TopoDS_Edge;
class TopoDS_Face;
class TopoDS_Shape;
class TopoDS_Vertex;

//! Stores the results of the OutLine and IsoLine
//! processes.
class HLRTopoBRep_Data
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRTopoBRep_Data();

  //! Clear of all the maps.
  Standard_EXPORT void Clear();

  //! Clear of all the data not needed during and after
  //! the hiding process.
  Standard_EXPORT void Clean();

  //! Returns True if the Edge is split.
  Standard_EXPORT bool EdgeHasSplE(const TopoDS_Edge& E) const;

  //! Returns True if the Face has internal outline.
  Standard_EXPORT bool FaceHasIntL(const TopoDS_Face& F) const;

  //! Returns True if the Face has outlines on restriction.
  Standard_EXPORT bool FaceHasOutL(const TopoDS_Face& F) const;

  //! Returns True if the Face has isolines.
  Standard_EXPORT bool FaceHasIsoL(const TopoDS_Face& F) const;

  Standard_EXPORT bool IsSplEEdgeEdge(const TopoDS_Edge& E1, const TopoDS_Edge& E2) const;

  Standard_EXPORT bool IsIntLFaceEdge(const TopoDS_Face& F, const TopoDS_Edge& E) const;

  Standard_EXPORT bool IsOutLFaceEdge(const TopoDS_Face& F, const TopoDS_Edge& E) const;

  Standard_EXPORT bool IsIsoLFaceEdge(const TopoDS_Face& F, const TopoDS_Edge& E) const;

  Standard_EXPORT TopoDS_Shape NewSOldS(const TopoDS_Shape& New) const;

  //! Returns the list of the edges.
  const NCollection_List<TopoDS_Shape>& EdgeSplE(const TopoDS_Edge& E) const;

  //! Returns the list of the internal OutLines.
  const NCollection_List<TopoDS_Shape>& FaceIntL(const TopoDS_Face& F) const;

  //! Returns the list of the OutLines on restriction.
  const NCollection_List<TopoDS_Shape>& FaceOutL(const TopoDS_Face& F) const;

  //! Returns the list of the IsoLines.
  const NCollection_List<TopoDS_Shape>& FaceIsoL(const TopoDS_Face& F) const;

  //! Returns True if V is an outline vertex on a
  //! restriction.
  bool IsOutV(const TopoDS_Vertex& V) const;

  //! Returns True if V is an internal outline vertex.
  bool IsIntV(const TopoDS_Vertex& V) const;

  Standard_EXPORT void AddOldS(const TopoDS_Shape& NewS, const TopoDS_Shape& OldS);

  Standard_EXPORT NCollection_List<TopoDS_Shape>& AddSplE(const TopoDS_Edge& E);

  Standard_EXPORT NCollection_List<TopoDS_Shape>& AddIntL(const TopoDS_Face& F);

  Standard_EXPORT NCollection_List<TopoDS_Shape>& AddOutL(const TopoDS_Face& F);

  Standard_EXPORT NCollection_List<TopoDS_Shape>& AddIsoL(const TopoDS_Face& F);

  void AddOutV(const TopoDS_Vertex& V);

  void AddIntV(const TopoDS_Vertex& V);

  Standard_EXPORT void InitEdge();

  bool MoreEdge() const;

  Standard_EXPORT void NextEdge();

  const TopoDS_Edge& Edge() const;

  //! Start an iteration on the vertices of E.
  Standard_EXPORT void InitVertex(const TopoDS_Edge& E);

  bool MoreVertex() const;

  void NextVertex();

  Standard_EXPORT const TopoDS_Vertex& Vertex() const;

  Standard_EXPORT double Parameter() const;

  //! Insert before the current position.
  Standard_EXPORT void InsertBefore(const TopoDS_Vertex& V, const double P);

  Standard_EXPORT void Append(const TopoDS_Vertex& V, const double P);

private:
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>                   myOldS;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> mySplE;
  NCollection_DataMap<TopoDS_Shape, HLRTopoBRep_FaceData, TopTools_ShapeMapHasher>           myData;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>                                     myOutV;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>                                     myIntV;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<HLRTopoBRep_VData>, TopTools_ShapeMapHasher>
    myEdgesVertices;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<HLRTopoBRep_VData>, TopTools_ShapeMapHasher>::
    Iterator                                    myEIterator;
  NCollection_List<HLRTopoBRep_VData>::Iterator myVIterator;
  NCollection_List<HLRTopoBRep_VData>*          myVList;
};
// Created on: 1995-02-07
// Created by: Christophe MARION
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

#include <HLRTopoBRep_FaceData.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>

//=================================================================================================

inline const NCollection_List<TopoDS_Shape>& HLRTopoBRep_Data::EdgeSplE(const TopoDS_Edge& E) const
{
  return mySplE(E);
}

//=================================================================================================

inline const NCollection_List<TopoDS_Shape>& HLRTopoBRep_Data::FaceIntL(const TopoDS_Face& F) const
{
  return myData(F).FaceIntL();
}

//=================================================================================================

inline const NCollection_List<TopoDS_Shape>& HLRTopoBRep_Data::FaceOutL(const TopoDS_Face& F) const
{
  return myData(F).FaceOutL();
}

//=================================================================================================

inline const NCollection_List<TopoDS_Shape>& HLRTopoBRep_Data::FaceIsoL(const TopoDS_Face& F) const
{
  return myData(F).FaceIsoL();
}

//=================================================================================================

inline bool HLRTopoBRep_Data::IsOutV(const TopoDS_Vertex& V) const
{
  return myOutV.Contains(V);
}

//=================================================================================================

inline bool HLRTopoBRep_Data::IsIntV(const TopoDS_Vertex& V) const
{
  return myIntV.Contains(V);
}

//=================================================================================================

inline void HLRTopoBRep_Data::AddOutV(const TopoDS_Vertex& V)
{
  myOutV.Add(V);
}

//=================================================================================================

inline void HLRTopoBRep_Data::AddIntV(const TopoDS_Vertex& V)
{
  myIntV.Add(V);
}

//=================================================================================================

inline bool HLRTopoBRep_Data::MoreEdge() const
{
  return myEIterator.More();
}

//=================================================================================================

inline const TopoDS_Edge& HLRTopoBRep_Data::Edge() const
{
  return TopoDS::Edge(myEIterator.Key());
}

//=================================================================================================

inline bool HLRTopoBRep_Data::MoreVertex() const
{
  return myVIterator.More();
}

//=================================================================================================

inline void HLRTopoBRep_Data::NextVertex()
{
  myVIterator.Next();
}


