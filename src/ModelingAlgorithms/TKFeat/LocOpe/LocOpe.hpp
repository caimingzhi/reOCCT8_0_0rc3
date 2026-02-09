#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
class TopoDS_Wire;
class TopoDS_Face;
class TopoDS_Edge;
class TopoDS_Shape;

class LocOpe
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool Closed(const TopoDS_Wire& W, const TopoDS_Face& OnF);

  Standard_EXPORT static bool Closed(const TopoDS_Edge& E, const TopoDS_Face& OnF);

  Standard_EXPORT static bool TgtFaces(const TopoDS_Edge& E,
                                       const TopoDS_Face& F1,
                                       const TopoDS_Face& F2);

  Standard_EXPORT static void SampleEdges(const TopoDS_Shape& S, NCollection_Sequence<gp_Pnt>& Pt);
};
