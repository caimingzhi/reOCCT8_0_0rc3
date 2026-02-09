#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_List.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>

#include <TopLoc_Location.hpp>
#include <Message_ProgressRange.hpp>

class BRepTools_Modification;
class Geom_Curve;
class Geom_Surface;

class BRepTools_Modifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepTools_Modifier(bool theMutableInput = false);

  Standard_EXPORT BRepTools_Modifier(const TopoDS_Shape& S);

  Standard_EXPORT BRepTools_Modifier(const TopoDS_Shape&                        S,
                                     const occ::handle<BRepTools_Modification>& M);

  Standard_EXPORT void Init(const TopoDS_Shape& S);

  Standard_EXPORT void Perform(const occ::handle<BRepTools_Modification>& M,
                               const Message_ProgressRange& theProgress = Message_ProgressRange());

  bool IsDone() const;

  Standard_EXPORT bool IsMutableInput() const;

  Standard_EXPORT void SetMutableInput(bool theMutableInput);

  const TopoDS_Shape& ModifiedShape(const TopoDS_Shape& S) const;

private:
  struct NewCurveInfo
  {
    occ::handle<Geom_Curve> myCurve;
    TopLoc_Location         myLoc;
    double                  myToler;
  };

  struct NewSurfaceInfo
  {
    occ::handle<Geom_Surface> mySurface;
    TopLoc_Location           myLoc;
    double                    myToler;
    bool                      myRevWires;
    bool                      myRevFace;
  };

  Standard_EXPORT void Put(const TopoDS_Shape& S);

  Standard_EXPORT bool Rebuild(const TopoDS_Shape&                        S,
                               const occ::handle<BRepTools_Modification>& M,
                               bool&                                      theNewGeom,
                               const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void CreateNewVertices(
    const NCollection_IndexedDataMap<TopoDS_Shape,
                                     NCollection_List<TopoDS_Shape>,
                                     TopTools_ShapeMapHasher>& theMVE,
    const occ::handle<BRepTools_Modification>&                 M);

  Standard_EXPORT void FillNewCurveInfo(
    const NCollection_IndexedDataMap<TopoDS_Shape,
                                     NCollection_List<TopoDS_Shape>,
                                     TopTools_ShapeMapHasher>& theMEF,
    const occ::handle<BRepTools_Modification>&                 M);

  Standard_EXPORT void FillNewSurfaceInfo(const occ::handle<BRepTools_Modification>& M);

  Standard_EXPORT void CreateOtherVertices(
    const NCollection_IndexedDataMap<TopoDS_Shape,
                                     NCollection_List<TopoDS_Shape>,
                                     TopTools_ShapeMapHasher>& theMVE,
    const NCollection_IndexedDataMap<TopoDS_Shape,
                                     NCollection_List<TopoDS_Shape>,
                                     TopTools_ShapeMapHasher>& theMEF,
    const occ::handle<BRepTools_Modification>&                 M);

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>  myMap;
  TopoDS_Shape                                                              myShape;
  bool                                                                      myDone;
  NCollection_DataMap<TopoDS_Edge, NewCurveInfo, TopTools_ShapeMapHasher>   myNCInfo;
  NCollection_DataMap<TopoDS_Face, NewSurfaceInfo, TopTools_ShapeMapHasher> myNSInfo;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>                    myNonUpdFace;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>                    myHasNewGeom;
  bool                                                                      myMutableInput;
};

#include <Standard_NoSuchObject.hpp>

inline const TopoDS_Shape& BRepTools_Modifier::ModifiedShape(const TopoDS_Shape& S) const
{
  if (!myMap.IsBound(S))
  {
    throw Standard_NoSuchObject();
  }
  return myMap(S);
}

inline bool BRepTools_Modifier::IsDone() const
{
  return myDone;
}
