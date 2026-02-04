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

//! @class IVtkOCC_ShapeMesher
//! @brief OCC implementation of IMesher interface.
//!
//! Mesher produces shape data using implementation of IShapeData interface for
//! VTK and then result can be retrieved from this implementation as a vtkPolyData:
//! @image html doc/img/image002.gif
//! Then the resulting vtkPolyData can be used for initialization of VTK pipeline.
class IVtkOCC_ShapeMesher : public IVtk_IShapeMesher
{
public:
  //! Main constructor.
  Standard_EXPORT IVtkOCC_ShapeMesher();

  //! Destructor.
  Standard_EXPORT ~IVtkOCC_ShapeMesher() override;

  //! Returns absolute deflection used by this algorithm.
  //! This value is calculated on the basis of the shape's bounding box.
  //! Zero might be returned in case if the underlying OCCT shape
  //! is empty or invalid. Thus check the returned value before
  //! passing it to OCCT meshing algorithms!
  //! @return absolute deflection value
  Standard_EXPORT double GetDeflection() const;

  //! Returns relative deviation coefficient used by this algorithm.
  //! @return relative deviation coefficient
  Standard_EXPORT double GetDeviationCoeff() const;

  //! Returns deviation angle used by this algorithm.
  //! This is the maximum allowed angle between the normals to the
  //! curve/surface and the normals to polyline/faceted representation.
  //! @return deviation angle (in radians)
  Standard_EXPORT double GetDeviationAngle() const;

protected:
  //! Executes the mesh generation algorithms. To be defined in implementation class.
  Standard_EXPORT void internalBuild() override;

private:
  //! Extracts free vertices from the shape (i.e. those not belonging to any edge)
  //! and passes the geometry to IPolyData.
  //! Each vertex is associated with its sub-shape ID.
  void addFreeVertices();

  //! Adds all the edges (free and non-free) to IPolyData.
  void addEdges();

  //! Adds the point coordinates, connectivity info and
  //! sub-shape ID for the OCCT vertex.
  //!
  //! @param theVertex OCCT vertex to be added to the mesh
  //! @param theShapeId global point ID needed for connectivity data creation
  void addVertex(const TopoDS_Vertex& theVertex,
                 const IVtk_IdType    theShapeId,
                 const IVtk_MeshType  theMeshType);

  //! Adds the point coordinates and a polyline for the OCCT edge.
  //! Note that the edge should be triangulated in advance.
  //!
  //! @param theEdge OCCT edge to be meshed
  //! @param theShapeId the edge's subshape ID
  //! @see IVtkOCC_ShapeMesher::meshShape
  void addEdge(const TopoDS_Edge&  theEdge,
               const IVtk_IdType   theShapeId,
               const IVtk_MeshType theMeshType);

  //! Generates wireframe representation of the given TopoDS_Face object
  //! with help of OCCT algorithms. The resulting polylines are passed to IPolyData
  //! interface and associated with the given sub-shape ID.
  //! @param[in]  theFace TopoDS_Face object to build wireframe representation for
  //! @param[in]  theShapeId The face' sub-shape ID
  //! @param[in]  theDeflection curve deflection
  void addWFFace(const TopoDS_Face& theFace,
                 const IVtk_IdType  theShapeId,
                 const double       theDeflection);

  //! Creates shaded representation of the given TopoDS_Face object
  //! starting from OCCT triangulation that should be created in advance.
  //! The resulting triangles are passed to IPolyData
  //! interface and associated with the given sub-shape ID.
  //! @param[in]  theFace    TopoDS_Face object to build shaded representation for
  //! @param[in]  theShapeId the face' sub-shape ID
  //! @see IVtkOCC_ShapeMesher::meshShape, IVtkOCC_ShapeMesher::addEdge
  void addShadedFace(const TopoDS_Face& theFace, const IVtk_IdType theShapeId);

  //! Get the IShape as OCC implementation
  const IVtkOCC_Shape::Handle GetShapeObj() const;

  DEFINE_STANDARD_RTTIEXT(IVtkOCC_ShapeMesher, IVtk_IShapeMesher)

private:
  NCollection_DataMap<TopoDS_Shape, IVtk_MeshType, TopTools_ShapeMapHasher> myEdgesTypes;
};

