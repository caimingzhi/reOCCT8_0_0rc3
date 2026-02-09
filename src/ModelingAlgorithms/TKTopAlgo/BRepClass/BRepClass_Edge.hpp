#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>

#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>

class BRepClass_Edge
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepClass_Edge();

  Standard_EXPORT BRepClass_Edge(const TopoDS_Edge& E, const TopoDS_Face& F);

  TopoDS_Edge&       Edge();
  const TopoDS_Edge& Edge() const;

  TopoDS_Face&       Face();
  const TopoDS_Face& Face() const;

  const TopoDS_Edge& NextEdge() const { return myNextEdge; }

  Standard_EXPORT void SetNextEdge(
    const NCollection_IndexedDataMap<TopoDS_Shape,
                                     NCollection_List<TopoDS_Shape>,
                                     TopTools_ShapeMapHasher>& theMapVE);

  double MaxTolerance() const { return myMaxTolerance; }

  void SetMaxTolerance(const double theValue) { myMaxTolerance = theValue; }

  bool UseBndBox() const { return myUseBndBox; }

  void SetUseBndBox(const bool theValue) { myUseBndBox = theValue; }

private:
  TopoDS_Edge myEdge;
  TopoDS_Face myFace;
  TopoDS_Edge myNextEdge;
  double      myMaxTolerance;
  bool        myUseBndBox;
};

inline TopoDS_Edge& BRepClass_Edge::Edge()
{
  return myEdge;
}

inline const TopoDS_Edge& BRepClass_Edge::Edge() const
{
  return myEdge;
}

inline TopoDS_Face& BRepClass_Edge::Face()
{
  return myFace;
}

inline const TopoDS_Face& BRepClass_Edge::Face() const
{
  return myFace;
}
