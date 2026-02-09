#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <ChFi2d_ConstructionError.hpp>
class TopoDS_Edge;
class TopoDS_Vertex;
class TopoDS_Face;

class ChFi2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool CommonVertex(const TopoDS_Edge& E1,
                                           const TopoDS_Edge& E2,
                                           TopoDS_Vertex&     V);

  Standard_EXPORT static ChFi2d_ConstructionError FindConnectedEdges(const TopoDS_Face&   F,
                                                                     const TopoDS_Vertex& V,
                                                                     TopoDS_Edge&         E1,
                                                                     TopoDS_Edge&         E2);
};
