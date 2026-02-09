#pragma once

#include <Prs3d_Root.hpp>
#include <Prs3d_Drawer.hpp>

enum StdPrs_Volume
{
  StdPrs_Volume_Autodetection,
  StdPrs_Volume_Closed,
  StdPrs_Volume_Opened
};

class Graphic3d_ArrayOfSegments;
class Graphic3d_ArrayOfTriangles;
class TopoDS_Shape;
class BRep_Builder;
class TopoDS_Compound;

class StdPrs_ShadedShape : public Prs3d_Root
{
public:
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& thePresentation,
                                  const TopoDS_Shape&                    theShape,
                                  const occ::handle<Prs3d_Drawer>&       theDrawer,
                                  const StdPrs_Volume theVolume = StdPrs_Volume_Autodetection,
                                  const occ::handle<Graphic3d_Group>& theGroup = nullptr);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& thePresentation,
                                  const TopoDS_Shape&                    theShape,
                                  const occ::handle<Prs3d_Drawer>&       theDrawer,
                                  const bool                             theHasTexels,
                                  const gp_Pnt2d&                        theUVOrigin,
                                  const gp_Pnt2d&                        theUVRepeat,
                                  const gp_Pnt2d&                        theUVScale,
                                  const StdPrs_Volume theVolume = StdPrs_Volume_Autodetection,
                                  const occ::handle<Graphic3d_Group>& theGroup = nullptr);

  Standard_EXPORT static void ExploreSolids(const TopoDS_Shape& theShape,
                                            const BRep_Builder& theBuilder,
                                            TopoDS_Compound&    theClosed,
                                            TopoDS_Compound&    theOpened,
                                            const bool          theIgnore1DSubShape);

  Standard_EXPORT static void AddWireframeForFreeElements(
    const occ::handle<Prs3d_Presentation>& thePrs,
    const TopoDS_Shape&                    theShape,
    const occ::handle<Prs3d_Drawer>&       theDrawer);

  Standard_EXPORT static void AddWireframeForFacesWithoutTriangles(
    const occ::handle<Prs3d_Presentation>& thePrs,
    const TopoDS_Shape&                    theShape,
    const occ::handle<Prs3d_Drawer>&       theDrawer);

public:
  static occ::handle<Graphic3d_ArrayOfTriangles> FillTriangles(const TopoDS_Shape& theShape)
  {
    gp_Pnt2d aDummy;
    return FillTriangles(theShape, false, aDummy, aDummy, aDummy);
  }

  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfTriangles> FillTriangles(
    const TopoDS_Shape& theShape,
    const bool          theHasTexels,
    const gp_Pnt2d&     theUVOrigin,
    const gp_Pnt2d&     theUVRepeat,
    const gp_Pnt2d&     theUVScale);

  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfSegments> FillFaceBoundaries(
    const TopoDS_Shape& theShape,
    GeomAbs_Shape       theUpperContinuity = GeomAbs_CN);
};
