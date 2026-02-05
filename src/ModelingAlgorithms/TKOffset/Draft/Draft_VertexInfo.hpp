#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_List.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Boolean.hpp>
class TopoDS_Edge;

class Draft_VertexInfo
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Draft_VertexInfo();

  Standard_EXPORT void Add(const TopoDS_Edge& E);

  Standard_EXPORT const gp_Pnt& Geometry() const;

  Standard_EXPORT double Parameter(const TopoDS_Edge& E);

  Standard_EXPORT void InitEdgeIterator();

  Standard_EXPORT const TopoDS_Edge& Edge() const;

  Standard_EXPORT void NextEdge();

  Standard_EXPORT bool MoreEdge() const;

  Standard_EXPORT gp_Pnt& ChangeGeometry();

  Standard_EXPORT double& ChangeParameter(const TopoDS_Edge& E);

private:
  gp_Pnt                                   myGeom;
  NCollection_List<TopoDS_Shape>           myEdges;
  NCollection_List<double>                 myParams;
  NCollection_List<TopoDS_Shape>::Iterator myItEd;
};
