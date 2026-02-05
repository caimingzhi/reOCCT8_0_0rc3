#pragma once

#include <Standard.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <Standard_Transient.hpp>
class TopoDS_Edge;
class TopoDS_Vertex;
class TopoDS_Face;

class LocOpe_GeneratedShape : public Standard_Transient
{

public:
  Standard_EXPORT virtual const NCollection_List<TopoDS_Shape>& GeneratingEdges() = 0;

  //! Returns the edge created by the vertex <V>. If
  //! none, must return a null shape.
  Standard_EXPORT virtual TopoDS_Edge Generated(const TopoDS_Vertex& V) = 0;

  //! Returns the face created by the edge <E>. If none,
  //! must return a null shape.
  Standard_EXPORT virtual TopoDS_Face Generated(const TopoDS_Edge& E) = 0;

  //! Returns the list of correctly oriented generated
  //! faces.
  Standard_EXPORT virtual const NCollection_List<TopoDS_Shape>& OrientedFaces() = 0;

  DEFINE_STANDARD_RTTIEXT(LocOpe_GeneratedShape, Standard_Transient)

protected:
  NCollection_List<TopoDS_Shape> myGEdges;
  NCollection_List<TopoDS_Shape> myList;
};
