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

class StdPrs_WFShape : public Prs3d_Root
{
public:
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& thePresentation,
                                  const TopoDS_Shape&                    theShape,
                                  const occ::handle<Prs3d_Drawer>&       theDrawer,
                                  bool                                   theIsParallel = false);

  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfPrimitives> AddEdgesOnTriangulation(
    const TopoDS_Shape& theShape,
    const bool          theToExcludeGeometric = true);

  Standard_EXPORT static void AddEdgesOnTriangulation(NCollection_Sequence<gp_Pnt>& theSegments,
                                                      const TopoDS_Shape&           theShape,
                                                      const bool theToExcludeGeometric = true);

  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfPrimitives> AddAllEdges(
    const TopoDS_Shape&              theShape,
    const occ::handle<Prs3d_Drawer>& theDrawer);

  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfPoints> AddVertexes(
    const TopoDS_Shape&  theShape,
    Prs3d_VertexDrawMode theVertexMode);

private:
  Standard_EXPORT static void addEdges(
    const TopoDS_Shape&                                           theShape,
    const occ::handle<Prs3d_Drawer>&                              theDrawer,
    double                                                        theShapeDeflection,
    NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>* theWire,
    NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>* theFree,
    NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>* theUnFree);

  static void addEdges(const NCollection_List<TopoDS_Shape>& theEdges,
                       const occ::handle<Prs3d_Drawer>&      theDrawer,
                       const double                          theShapeDeflection,
                       NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>& thePolylines);
};
