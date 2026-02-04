#pragma once


#include <Standard.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_DataMap.hpp>
#include <LocOpe_GeneratedShape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Face;
class TopoDS_Edge;
class TopoDS_Vertex;

class LocOpe_GluedShape : public LocOpe_GeneratedShape
{

public:
  Standard_EXPORT LocOpe_GluedShape();

  Standard_EXPORT LocOpe_GluedShape(const TopoDS_Shape& S);

  Standard_EXPORT void Init(const TopoDS_Shape& S);

  Standard_EXPORT void GlueOnFace(const TopoDS_Face& F);

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& GeneratingEdges() override;

  //! Returns the edge created by the vertex <V>. If
  //! none, must return a null shape.
  Standard_EXPORT TopoDS_Edge Generated(const TopoDS_Vertex& V) override;

  //! Returns the face created by the edge <E>. If none,
  //! must return a null shape.
  Standard_EXPORT TopoDS_Face Generated(const TopoDS_Edge& E) override;

  //! Returns the list of correctly oriented generated
  //! faces.
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& OrientedFaces() override;

  DEFINE_STANDARD_RTTIEXT(LocOpe_GluedShape, LocOpe_GeneratedShape)

private:
  Standard_EXPORT void MapEdgeAndVertices();

  TopoDS_Shape                                                             myShape;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>                   myMap;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myGShape;
};

