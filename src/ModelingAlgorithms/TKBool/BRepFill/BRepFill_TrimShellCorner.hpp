#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepFill_TransitionStyle.hpp>
#include <gp_Ax2.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <BOPDS_PDS.hpp>

//! Trims sets of faces in the corner to make proper parts of pipe
class BRepFill_TrimShellCorner
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor: takes faces to intersect,
  //! type of transition (it can be RightCorner or RoundCorner)
  //! and axis of bisector plane
  //! theIntersectPointCrossDirection : prev path direction at the origin point of theAxeOfBisPlane
  //! cross next path direction at the origin point of theAxeOfBisPlane. used when EE has more than
  //! one vertices
  Standard_EXPORT BRepFill_TrimShellCorner(
    const occ::handle<NCollection_HArray2<TopoDS_Shape>>& theFaces,
    const BRepFill_TransitionStyle                        theTransition,
    const gp_Ax2&                                         theAxeOfBisPlane,
    const gp_Vec&                                         theIntPointCrossDir);

  Standard_EXPORT void AddBounds(const occ::handle<NCollection_HArray2<TopoDS_Shape>>& Bounds);

  Standard_EXPORT void AddUEdges(const occ::handle<NCollection_HArray2<TopoDS_Shape>>& theUEdges);

  Standard_EXPORT void AddVEdges(const occ::handle<NCollection_HArray2<TopoDS_Shape>>& theVEdges,
                                 const int                                             theIndex);

  Standard_EXPORT void Perform();

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool HasSection() const;

  Standard_EXPORT void Modified(const TopoDS_Shape& S, NCollection_List<TopoDS_Shape>& theModified);

private:
  bool MakeFacesSec(const int        theIndex,
                    const BOPDS_PDS& theDS,
                    const int        theFaceIndex1,
                    const int        theFaceIndex2,
                    const int        theSSInterfIndex);

  bool MakeFacesNonSec(const int        theIndex,
                       const BOPDS_PDS& theDS,
                       const int        theFaceIndex1,
                       const int        theFaceIndex2);

  bool ChooseSection(const TopoDS_Shape&  Comp,
                     const TopoDS_Vertex& theFirstVertex,
                     const TopoDS_Vertex& theLastVertex,
                     TopoDS_Shape&        resWire,
                     gp_Pln&              resPlane,
                     bool&                IsSingular);

  BRepFill_TransitionStyle                       myTransition;
  gp_Ax2                                         myAxeOfBisPlane;
  gp_Vec                                         myIntPointCrossDir;
  TopoDS_Shape                                   myShape1;
  TopoDS_Shape                                   myShape2;
  occ::handle<NCollection_HArray2<TopoDS_Shape>> myBounds;
  occ::handle<NCollection_HArray2<TopoDS_Shape>> myUEdges;
  occ::handle<NCollection_HArray1<TopoDS_Shape>> myVEdges;
  occ::handle<NCollection_HArray2<TopoDS_Shape>> myFaces;
  bool                                           myDone;
  bool                                           myHasSection;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myHistMap;
};
