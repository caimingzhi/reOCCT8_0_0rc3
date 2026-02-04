#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>
class TopoDS_Edge;
class TopoDS_Shape;

//! Rebuilds edges to connect with new vertices, was moved from ShapeBuild.
//! Makes vertices to be shared to connect edges,
//! updates positions and tolerances for shared vertices.
//! Accepts edges bounded by two vertices each.
class ShapeFix_EdgeConnect
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeFix_EdgeConnect();

  //! Adds information on connectivity between start vertex
  //! of second edge and end vertex of first edge,
  //! taking edges orientation into account
  Standard_EXPORT void Add(const TopoDS_Edge& aFirst, const TopoDS_Edge& aSecond);

  //! Adds connectivity information for the whole shape.
  //! Note: edges in wires must be well ordered
  //! Note: flag Closed should be set for closed wires
  Standard_EXPORT void Add(const TopoDS_Shape& aShape);

  //! Builds shared vertices, updates their positions and tolerances
  Standard_EXPORT void Build();

  //! Clears internal data structure
  Standard_EXPORT void Clear();

private:
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myVertices;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myLists;
};

