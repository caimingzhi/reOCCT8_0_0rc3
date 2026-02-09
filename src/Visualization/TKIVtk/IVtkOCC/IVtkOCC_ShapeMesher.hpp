#pragma once

#include <IVtkOCC_Shape.hpp>
#include <IVtk_IShapeMesher.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopTools_ShapeMapHasher.hpp>

class Prs3d_Drawer;

class IVtkOCC_ShapeMesher : public IVtk_IShapeMesher
{
public:
  Standard_EXPORT IVtkOCC_ShapeMesher();

  Standard_EXPORT ~IVtkOCC_ShapeMesher() override;

  Standard_EXPORT double GetDeflection() const;

  Standard_EXPORT double GetDeviationCoeff() const;

  Standard_EXPORT double GetDeviationAngle() const;

protected:
  Standard_EXPORT void internalBuild() override;

private:
  void addFreeVertices();

  void addEdges();

  void addVertex(const TopoDS_Vertex& theVertex,
                 const IVtk_IdType    theShapeId,
                 const IVtk_MeshType  theMeshType);

  void addEdge(const TopoDS_Edge&  theEdge,
               const IVtk_IdType   theShapeId,
               const IVtk_MeshType theMeshType);

  void addWFFace(const TopoDS_Face& theFace,
                 const IVtk_IdType  theShapeId,
                 const double       theDeflection);

  void addShadedFace(const TopoDS_Face& theFace, const IVtk_IdType theShapeId);

  const IVtkOCC_Shape::Handle GetShapeObj() const;

  DEFINE_STANDARD_RTTIEXT(IVtkOCC_ShapeMesher, IVtk_IShapeMesher)

private:
  NCollection_DataMap<TopoDS_Shape, IVtk_MeshType, TopTools_ShapeMapHasher> myEdgesTypes;
};
