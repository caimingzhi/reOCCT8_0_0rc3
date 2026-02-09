#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Vertex.hpp>
#include <TopAbs_Orientation.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class ShapeExtend_WireData;
class TopoDS_Wire;
class TopoDS_Edge;

class ShapeFix_WireSegment
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeFix_WireSegment();

  Standard_EXPORT ShapeFix_WireSegment(const occ::handle<ShapeExtend_WireData>& wire,
                                       const TopAbs_Orientation ori = TopAbs_EXTERNAL);

  Standard_EXPORT ShapeFix_WireSegment(const TopoDS_Wire&       wire,
                                       const TopAbs_Orientation ori = TopAbs_EXTERNAL);

  Standard_EXPORT void Clear();

  Standard_EXPORT void Load(const occ::handle<ShapeExtend_WireData>& wire);

  Standard_EXPORT const occ::handle<ShapeExtend_WireData>& WireData() const;

  Standard_EXPORT void Orientation(const TopAbs_Orientation ori);

  Standard_EXPORT TopAbs_Orientation Orientation() const;

  Standard_EXPORT TopoDS_Vertex FirstVertex() const;

  Standard_EXPORT TopoDS_Vertex LastVertex() const;

  Standard_EXPORT bool IsClosed() const;

  Standard_EXPORT int NbEdges() const;

  Standard_EXPORT TopoDS_Edge Edge(const int i) const;

  Standard_EXPORT void SetEdge(const int i, const TopoDS_Edge& edge);

  Standard_EXPORT void AddEdge(const int i, const TopoDS_Edge& edge);

  Standard_EXPORT void AddEdge(const int          i,
                               const TopoDS_Edge& edge,
                               const int          iumin,
                               const int          iumax,
                               const int          ivmin,
                               const int          ivmax);

  Standard_EXPORT void SetPatchIndex(const int i,
                                     const int iumin,
                                     const int iumax,
                                     const int ivmin,
                                     const int ivmax);

  Standard_EXPORT void DefineIUMin(const int i, const int iumin);

  Standard_EXPORT void DefineIUMax(const int i, const int iumax);

  Standard_EXPORT void DefineIVMin(const int i, const int ivmin);

  Standard_EXPORT void DefineIVMax(const int i, const int ivmax);

  Standard_EXPORT void GetPatchIndex(const int i,
                                     int&      iumin,
                                     int&      iumax,
                                     int&      ivmin,
                                     int&      ivmax) const;

  Standard_EXPORT bool CheckPatchIndex(const int i) const;

  Standard_EXPORT void SetVertex(const TopoDS_Vertex& theVertex);

  Standard_EXPORT TopoDS_Vertex GetVertex() const;

  Standard_EXPORT bool IsVertex() const;

private:
  occ::handle<ShapeExtend_WireData>       myWire;
  TopoDS_Vertex                           myVertex;
  TopAbs_Orientation                      myOrient;
  occ::handle<NCollection_HSequence<int>> myIUMin;
  occ::handle<NCollection_HSequence<int>> myIUMax;
  occ::handle<NCollection_HSequence<int>> myIVMin;
  occ::handle<NCollection_HSequence<int>> myIVMax;
};
