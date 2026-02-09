#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class BRepBuilderAPI_Sewing;
class TopoDS_Shape;
class TopoDS_Edge;

class BRepOffsetAPI_FindContigousEdges
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepOffsetAPI_FindContigousEdges(const double tolerance = 1.0e-06,
                                                   const bool   option    = true);

  Standard_EXPORT void Init(const double tolerance, const bool option);

  Standard_EXPORT void Add(const TopoDS_Shape& shape);

  Standard_EXPORT void Perform();

  Standard_EXPORT int NbEdges() const;

  Standard_EXPORT int NbContigousEdges() const;

  Standard_EXPORT const TopoDS_Edge& ContigousEdge(const int index) const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& ContigousEdgeCouple(const int index) const;

  Standard_EXPORT const TopoDS_Edge& SectionToBoundary(const TopoDS_Edge& section) const;

  Standard_EXPORT int NbDegeneratedShapes() const;

  Standard_EXPORT const TopoDS_Shape& DegeneratedShape(const int index) const;

  Standard_EXPORT bool IsDegenerated(const TopoDS_Shape& shape) const;

  Standard_EXPORT bool IsModified(const TopoDS_Shape& shape) const;

  Standard_EXPORT const TopoDS_Shape& Modified(const TopoDS_Shape& shape) const;

  Standard_EXPORT void Dump() const;

private:
  occ::handle<BRepBuilderAPI_Sewing> mySewing;
};
