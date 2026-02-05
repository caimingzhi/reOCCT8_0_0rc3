#pragma once

#include <Prs3d_Root.hpp>
#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_PointAspect.hpp>
#include <Prs3d_LineAspect.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <NCollection_List.hpp>
#include <TopoDS_Shape.hpp>

class Graphic3d_ArrayOfPoints;

//! Tool for computing wireframe presentation of a TopoDS_Shape.
class StdPrs_WFShape : public Prs3d_Root
{
public:
  //! Computes wireframe presentation of a shape.
  //! @param[in] thePresentation  the presentation.
  //! @param[in] theShape  the shape.
  //! @param[in] theDrawer  the draw settings.
  //! @param[in] theIsParallel  perform algorithm using multiple threads
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& thePresentation,
                                  const TopoDS_Shape&                    theShape,
                                  const occ::handle<Prs3d_Drawer>&       theDrawer,
                                  bool                                   theIsParallel = false);

  //! Compute free and boundary edges on a triangulation of each face in the given shape.
  //! @param[in] theShape               the list of triangulated faces
  //! @param[in] theToExcludeGeometric  flag indicating that Faces with defined Surface should be
  //! skipped
  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfPrimitives> AddEdgesOnTriangulation(
    const TopoDS_Shape& theShape,
    const bool          theToExcludeGeometric = true);

  //! Compute free and boundary edges on a triangulation of each face in the given shape.
  //! @param[in] theSegments            the sequence of points defining segments
  //! @param[in] theShape               the list of triangulated faces
  //! @param[in] theToExcludeGeometric  flag indicating that Faces with defined Surface should be
  //! skipped
  Standard_EXPORT static void AddEdgesOnTriangulation(NCollection_Sequence<gp_Pnt>& theSegments,
                                                      const TopoDS_Shape&           theShape,
                                                      const bool theToExcludeGeometric = true);

  //! Compute all edges (wire, free, unfree) and put them into single primitive array.
  //! @param[in] theShape  the shape
  //! @param[in] theDrawer  the drawer settings (deviation angle and maximal parameter value)
  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfPrimitives> AddAllEdges(
    const TopoDS_Shape&              theShape,
    const occ::handle<Prs3d_Drawer>& theDrawer);

  //! Compute vertex presentation for a shape.
  //! @param[in] theShape  the shape
  //! @param[in] theVertexMode  vertex filter
  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfPoints> AddVertexes(
    const TopoDS_Shape&  theShape,
    Prs3d_VertexDrawMode theVertexMode);

private:
  //! Compute edge presentations for a shape.
  //! @param[in] theShape  the shape
  //! @param[in] theDrawer  the drawer settings (deviation angle and maximal parameter value)
  //! @param[in] theShapeDeflection  the deflection for the wireframe shape
  //! @param[out] theWire  output polylines for lonely wires
  //! @param[out] theFree  output polylines for free edges
  //! @param[out] theUnFree  output polylines for non-free edges
  Standard_EXPORT static void addEdges(
    const TopoDS_Shape&                                           theShape,
    const occ::handle<Prs3d_Drawer>&                              theDrawer,
    double                                                        theShapeDeflection,
    NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>* theWire,
    NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>* theFree,
    NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>* theUnFree);

  //! Compute edge presentations for a shape.
  //! @param[in] theEdges  the list of edges
  //! @param[in] theDrawer  the drawer settings (deviation angle and maximal parameter value)
  //! @param[in] theShapeDeflection  the deflection for the wireframe shape
  //! @param[out] thePolylines  output polylines
  static void addEdges(const NCollection_List<TopoDS_Shape>& theEdges,
                       const occ::handle<Prs3d_Drawer>&      theDrawer,
                       const double                          theShapeDeflection,
                       NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>& thePolylines);
};
