#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_List.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Map.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt.hpp>

#include <Message_ProgressRange.hpp>

class BRepTools_ReShape;
class TopoDS_Edge;
class TopoDS_Face;
class Geom_Surface;
class TopLoc_Location;
class Geom2d_Curve;
class Geom_Curve;

//! Provides methods to
//!
//! - identify possible contiguous boundaries (for control
//! afterwards (of continuity: C0, C1, ...))
//!
//! - assemble contiguous shapes into one shape.
//! Only manifold shapes will be found. Sewing will not
//! be done in case of multiple edges.
//!
//! For sewing, use this function as following:
//! - create an empty object
//! - default tolerance 1.E-06
//! - with face analysis on
//! - with sewing operation on
//! - set the cutting option as you need (default True)
//! - define a tolerance
//! - add shapes to be sewed -> Add
//! - compute -> Perform
//! - output the resulted shapes
//! - output free edges if necessary
//! - output multiple edges if necessary
//! - output the problems if any
class BRepBuilderAPI_Sewing : public Standard_Transient
{

public:
  //! Creates an object with
  //! tolerance of connexity
  //! option for sewing (if false only control)
  //! option for analysis of degenerated shapes
  //! option for cutting of free edges.
  //! option for non manifold processing
  Standard_EXPORT BRepBuilderAPI_Sewing(const double tolerance = 1.0e-06,
                                        const bool   option1   = true,
                                        const bool   option2   = true,
                                        const bool   option3   = true,
                                        const bool   option4   = false);

  //! initialize the parameters if necessary
  Standard_EXPORT void Init(const double tolerance = 1.0e-06,
                            const bool   option1   = true,
                            const bool   option2   = true,
                            const bool   option3   = true,
                            const bool   option4   = false);

  //! Loads the context shape.
  Standard_EXPORT void Load(const TopoDS_Shape& shape);

  //! Defines the shapes to be sewed or controlled
  Standard_EXPORT void Add(const TopoDS_Shape& shape);

  //! Computing
  //! theProgress - progress indicator of algorithm
  Standard_EXPORT void Perform(const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Gives the sewed shape
  //! a null shape if nothing constructed
  //! may be a face, a shell, a solid or a compound
  Standard_EXPORT const TopoDS_Shape& SewedShape() const;

  //! set context
  Standard_EXPORT void SetContext(const occ::handle<BRepTools_ReShape>& theContext);

  //! return context
  Standard_EXPORT const occ::handle<BRepTools_ReShape>& GetContext() const;

  //! Gives the number of free edges (edge shared by one face)
  Standard_EXPORT int NbFreeEdges() const;

  //! Gives each free edge
  Standard_EXPORT const TopoDS_Edge& FreeEdge(const int index) const;

  //! Gives the number of multiple edges
  //! (edge shared by more than two faces)
  Standard_EXPORT int NbMultipleEdges() const;

  //! Gives each multiple edge
  Standard_EXPORT const TopoDS_Edge& MultipleEdge(const int index) const;

  //! Gives the number of contiguous edges (edge shared by two faces)
  Standard_EXPORT int NbContigousEdges() const;

  //! Gives each contiguous edge
  Standard_EXPORT const TopoDS_Edge& ContigousEdge(const int index) const;

  //! Gives the sections (edge) belonging to a contiguous edge
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& ContigousEdgeCouple(const int index) const;

  //! Indicates if a section is bound (before use SectionToBoundary)
  Standard_EXPORT bool IsSectionBound(const TopoDS_Edge& section) const;

  //! Gives the original edge (free boundary) which becomes the
  //! the section. Remember that sections constitute common edges.
  //! This information is important for control because with
  //! original edge we can find the surface to which the section
  //! is attached.
  Standard_EXPORT const TopoDS_Edge& SectionToBoundary(const TopoDS_Edge& section) const;

  //! Gives the number of degenerated shapes
  Standard_EXPORT int NbDegeneratedShapes() const;

  //! Gives each degenerated shape
  Standard_EXPORT const TopoDS_Shape& DegeneratedShape(const int index) const;

  //! Indicates if a input shape is degenerated
  Standard_EXPORT bool IsDegenerated(const TopoDS_Shape& shape) const;

  //! Indicates if a input shape has been modified
  Standard_EXPORT bool IsModified(const TopoDS_Shape& shape) const;

  //! Gives a modifieded shape
  Standard_EXPORT const TopoDS_Shape& Modified(const TopoDS_Shape& shape) const;

  //! Indicates if a input subshape has been modified
  Standard_EXPORT bool IsModifiedSubShape(const TopoDS_Shape& shape) const;

  //! Gives a modifieded subshape
  Standard_EXPORT TopoDS_Shape ModifiedSubShape(const TopoDS_Shape& shape) const;

  //! print the information
  Standard_EXPORT void Dump() const;

  //! Gives the number of deleted faces (faces smallest than tolerance)
  Standard_EXPORT int NbDeletedFaces() const;

  //! Gives each deleted face
  Standard_EXPORT const TopoDS_Face& DeletedFace(const int index) const;

  //! Gives a modified shape
  Standard_EXPORT TopoDS_Face WhichFace(const TopoDS_Edge& theEdg, const int index = 1) const;

  //! Gets same parameter mode.
  bool SameParameterMode() const;

  //! Sets same parameter mode.
  void SetSameParameterMode(const bool SameParameterMode);

  //! Gives set tolerance.
  double Tolerance() const;

  //! Sets tolerance
  void SetTolerance(const double theToler);

  //! Gives set min tolerance.
  double MinTolerance() const;

  //! Sets min tolerance
  void SetMinTolerance(const double theMinToler);

  //! Gives set max tolerance
  double MaxTolerance() const;

  //! Sets max tolerance.
  void SetMaxTolerance(const double theMaxToler);

  //! Returns mode for sewing faces By default - true.
  bool FaceMode() const;

  //! Sets mode for sewing faces By default - true.
  void SetFaceMode(const bool theFaceMode);

  //! Returns mode for sewing floating edges By default - false.
  bool FloatingEdgesMode() const;

  //! Sets mode for sewing floating edges By default - false.
  //! Returns mode for cutting floating edges By default - false.
  //! Sets mode for cutting floating edges By default - false.
  void SetFloatingEdgesMode(const bool theFloatingEdgesMode);

  //! Returns mode for accounting of local tolerances
  //! of edges and vertices during of merging.
  bool LocalTolerancesMode() const;

  //! Sets mode for accounting of local tolerances
  //! of edges and vertices during of merging
  //! in this case WorkTolerance = myTolerance + tolEdge1+ tolEdg2;
  void SetLocalTolerancesMode(const bool theLocalTolerancesMode);

  //! Sets mode for non-manifold sewing.
  void SetNonManifoldMode(const bool theNonManifoldMode);

  //! Gets mode for non-manifold sewing.
  //!
  //! INTERNAL FUNCTIONS ---
  bool NonManifoldMode() const;

  DEFINE_STANDARD_RTTIEXT(BRepBuilderAPI_Sewing, Standard_Transient)

protected:
  //! Performs cutting of sections
  //! theProgress - progress indicator of processing
  Standard_EXPORT void Cutting(const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void Merging(const bool                   passage,
                               const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool IsMergedClosed(const TopoDS_Edge& Edge1,
                                      const TopoDS_Edge& Edge2,
                                      const TopoDS_Face& fase) const;

  Standard_EXPORT bool FindCandidates(NCollection_Sequence<TopoDS_Shape>& seqSections,
                                      NCollection_IndexedMap<int>&        mapReference,
                                      NCollection_Sequence<int>&          seqCandidates,
                                      NCollection_Sequence<bool>&         seqOrientations);

  Standard_EXPORT void AnalysisNearestEdges(const NCollection_Sequence<TopoDS_Shape>& sequenceSec,
                                            NCollection_Sequence<int>&  seqIndCandidate,
                                            NCollection_Sequence<bool>& seqOrientations,
                                            const bool                  evalDist = true);

  //! Merged nearest edges.
  Standard_EXPORT bool MergedNearestEdges(const TopoDS_Shape&                 edge,
                                          NCollection_Sequence<TopoDS_Shape>& SeqMergedEdge,
                                          NCollection_Sequence<bool>&         SeqMergedOri);

  Standard_EXPORT void EdgeProcessing(
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Recompute regularity on merged edges
  Standard_EXPORT void EdgeRegularity(
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void CreateOutputInformations();

  //! Defines if surface is U closed.
  Standard_EXPORT virtual bool IsUClosedSurface(const occ::handle<Geom_Surface>& surf,
                                                const TopoDS_Shape&              theEdge,
                                                const TopLoc_Location&           theloc) const;

  //! Defines if surface is V closed.
  Standard_EXPORT virtual bool IsVClosedSurface(const occ::handle<Geom_Surface>& surf,
                                                const TopoDS_Shape&              theEdge,
                                                const TopLoc_Location&           theloc) const;

  //! This method is called from Perform only
  //! theProgress - progress indicator of processing
  Standard_EXPORT virtual void FaceAnalysis(
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! This method is called from Perform only
  Standard_EXPORT virtual void FindFreeBoundaries();

  //! This method is called from Perform only
  //! theProgress - progress indicator of processing
  Standard_EXPORT virtual void VerticesAssembling(
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! This method is called from Perform only
  Standard_EXPORT virtual void CreateSewedShape();

  //! Get wire from free edges.
  //! This method is called from EdgeProcessing only
  Standard_EXPORT virtual void GetFreeWires(
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& MapFreeEdges,
    NCollection_Sequence<TopoDS_Shape>&                            seqWires);

  //! This method is called from MergingOfSections only
  Standard_EXPORT virtual void EvaluateAngulars(NCollection_Sequence<TopoDS_Shape>& sequenceSec,
                                                NCollection_Array1<bool>&           secForward,
                                                NCollection_Array1<double>&         tabAng,
                                                const int                           indRef) const;

  //! This method is called from MergingOfSections only
  Standard_EXPORT virtual void EvaluateDistances(NCollection_Sequence<TopoDS_Shape>& sequenceSec,
                                                 NCollection_Array1<bool>&           secForward,
                                                 NCollection_Array1<double>&         tabAng,
                                                 NCollection_Array1<double>&         arrLen,
                                                 NCollection_Array1<double>&         tabMinDist,
                                                 const int                           indRef) const;

  //! This method is called from SameParameterEdge only
  Standard_EXPORT virtual occ::handle<Geom2d_Curve> SameRange(
    const occ::handle<Geom2d_Curve>& CurvePtr,
    const double                     FirstOnCurve,
    const double                     LastOnCurve,
    const double                     RequestedFirst,
    const double                     RequestedLast) const;

  //! This method is called from SameParameterEdge only
  Standard_EXPORT virtual void SameParameter(const TopoDS_Edge& edge) const;

  //! This method is called from Merging only
  Standard_EXPORT virtual TopoDS_Edge SameParameterEdge(
    const TopoDS_Shape&                                     edge,
    const NCollection_Sequence<TopoDS_Shape>&               seqEdges,
    const NCollection_Sequence<bool>&                       seqForward,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& mapMerged,
    const occ::handle<BRepTools_ReShape>&                   locReShape);

  //! This method is called from Merging only
  Standard_EXPORT virtual TopoDS_Edge SameParameterEdge(
    const TopoDS_Edge&                    edge1,
    const TopoDS_Edge&                    edge2,
    const NCollection_List<TopoDS_Shape>& listFaces1,
    const NCollection_List<TopoDS_Shape>& listFaces2,
    const bool                            secForward,
    int&                                  whichSec,
    const bool                            firstCall = true);

  //! Projects points on curve
  //! This method is called from Cutting only
  Standard_EXPORT void ProjectPointsOnCurve(const NCollection_Array1<gp_Pnt>& arrPnt,
                                            const occ::handle<Geom_Curve>&    Crv,
                                            const double                      first,
                                            const double                      last,
                                            NCollection_Array1<double>&       arrDist,
                                            NCollection_Array1<double>&       arrPara,
                                            NCollection_Array1<gp_Pnt>&       arrProj,
                                            const bool                        isConsiderEnds) const;

  //! Creates cutting vertices on projections
  //! This method is called from Cutting only
  Standard_EXPORT virtual void CreateCuttingNodes(
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& MapVert,
    const TopoDS_Shape&                                                  bound,
    const TopoDS_Shape&                                                  vfirst,
    const TopoDS_Shape&                                                  vlast,
    const NCollection_Array1<double>&                                    arrDist,
    const NCollection_Array1<double>&                                    arrPara,
    const NCollection_Array1<gp_Pnt>&                                    arrPnt,
    NCollection_Sequence<TopoDS_Shape>&                                  seqNode,
    NCollection_Sequence<double>&                                        seqPara);

  //! Performs cutting of bound
  //! This method is called from Cutting only
  Standard_EXPORT virtual void CreateSections(const TopoDS_Shape&                       bound,
                                              const NCollection_Sequence<TopoDS_Shape>& seqNode,
                                              const NCollection_Sequence<double>&       seqPara,
                                              NCollection_List<TopoDS_Shape>&           listEdge);

  //! Makes all edges from shape same parameter
  //! if SameParameterMode is equal to true
  //! This method is called from Perform only
  Standard_EXPORT virtual void SameParameterShape();

  double                                                                          myTolerance;
  bool                                                                            mySewing;
  bool                                                                            myAnalysis;
  bool                                                                            myCutting;
  bool                                                                            myNonmanifold;
  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myOldShapes;
  TopoDS_Shape                                                                    mySewedShape;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>                   myDegenerated;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>                   myFreeEdges;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>                   myMultipleEdges;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                                           myContigousEdges;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myContigSecBound;
  int                                                                      myNbShapes;
  int                                                                      myNbVertices;
  int                                                                      myNbEdges;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myBoundFaces;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                                                  myBoundSections;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>        mySectionBound;
  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myVertexNode;
  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myVertexNodeFree;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myNodeSections;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                                myCuttingNode;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myLittleFace;
  TopoDS_Shape                                                  myShape;
  occ::handle<BRepTools_ReShape>                                myReShape;

private:
  bool                                                   myFaceMode;
  bool                                                   myFloatingEdgesMode;
  bool                                                   mySameParameterMode;
  bool                                                   myLocalToleranceMode;
  double                                                 myMinTolerance;
  double                                                 myMaxTolerance;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myMergedEdges;
};
// Created on: 2000-12-18
// Created by: Galina KULIKOVA
// Copyright (c) 2000-2014 OPEN CASCADE SAS
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

//=================================================================================================

inline void BRepBuilderAPI_Sewing::SetMaxTolerance(const double theMaxToler)
{
  myMaxTolerance = theMaxToler;
}

//=================================================================================================

inline double BRepBuilderAPI_Sewing::MaxTolerance() const
{
  return myMaxTolerance;
}

//=================================================================================================

inline double BRepBuilderAPI_Sewing::Tolerance() const
{
  return myTolerance;
}

//=================================================================================================

inline void BRepBuilderAPI_Sewing::SetTolerance(const double theToler)
{
  myTolerance = theToler;
}

//=================================================================================================

inline void BRepBuilderAPI_Sewing::SetMinTolerance(const double theMinToler)
{
  myMinTolerance = theMinToler;
}

//=================================================================================================

inline double BRepBuilderAPI_Sewing::MinTolerance() const
{
  return myMinTolerance;
}

//=================================================================================================

inline void BRepBuilderAPI_Sewing::SetFaceMode(const bool theFaceMode)
{
  myFaceMode = theFaceMode;
}

//=================================================================================================

inline bool BRepBuilderAPI_Sewing::FaceMode() const
{
  return myFaceMode;
}

//=================================================================================================

inline void BRepBuilderAPI_Sewing::SetFloatingEdgesMode(const bool theFloatingEdgesMode)
{
  myFloatingEdgesMode = theFloatingEdgesMode;
}

//=================================================================================================

inline bool BRepBuilderAPI_Sewing::FloatingEdgesMode() const
{
  return myFloatingEdgesMode;
}

/*
//=================================================================================================

inline  void BRepBuilderAPI_Sewing::SetCuttingFloatingEdgesMode(const bool
theCuttingFloatingEdgesMode)
{
  myCuttingFloatingEdgesMode = theCuttingFloatingEdgesMode;
}

//=================================================================================================

inline  bool BRepBuilderAPI_Sewing::CuttingFloatingEdgesMode() const
{
  return myCuttingFloatingEdgesMode;
}
*/

//=================================================================================================

inline bool BRepBuilderAPI_Sewing::SameParameterMode() const
{
  return mySameParameterMode;
}

//=================================================================================================

inline void BRepBuilderAPI_Sewing::SetSameParameterMode(const bool SameParameterMode)
{
  mySameParameterMode = SameParameterMode;
}

//=================================================================================================

inline void BRepBuilderAPI_Sewing::SetLocalTolerancesMode(const bool theLocalTolerancesMode)
{
  myLocalToleranceMode = theLocalTolerancesMode;
}

//=================================================================================================

inline bool BRepBuilderAPI_Sewing::LocalTolerancesMode() const
{
  return myLocalToleranceMode;
}

//=================================================================================================

inline void BRepBuilderAPI_Sewing::SetNonManifoldMode(const bool theNonManifoldMode)
{
  myNonmanifold = theNonManifoldMode;
}

//=================================================================================================

inline bool BRepBuilderAPI_Sewing::NonManifoldMode() const
{
  return myNonmanifold;
}


