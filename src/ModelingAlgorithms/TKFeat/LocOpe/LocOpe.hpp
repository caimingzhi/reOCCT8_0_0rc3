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

//! Provides tools to implement local topological
//! operations on a shape.
class LocOpe
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns true when the wire <W> is closed
  //! on the face <OnF>.
  Standard_EXPORT static bool Closed(const TopoDS_Wire& W, const TopoDS_Face& OnF);

  //! Returns true when the edge <E> is closed
  //! on the face <OnF>.
  Standard_EXPORT static bool Closed(const TopoDS_Edge& E, const TopoDS_Face& OnF);

  //! Returns true when the faces are tangent
  Standard_EXPORT static bool TgtFaces(const TopoDS_Edge& E,
                                       const TopoDS_Face& F1,
                                       const TopoDS_Face& F2);

  Standard_EXPORT static void SampleEdges(const TopoDS_Shape& S, NCollection_Sequence<gp_Pnt>& Pt);
};
