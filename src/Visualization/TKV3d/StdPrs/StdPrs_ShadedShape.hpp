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

//! Auxiliary procedures to prepare Shaded presentation of specified shape.
class StdPrs_ShadedShape : public Prs3d_Root
{
public:
  //! Shades <theShape>.
  //! @param theVolumeType defines the way how to interpret input shapes - as Closed volumes (to
  //! activate back-face culling and capping plane algorithms), as Open volumes (shells or solids
  //! with holes) or to perform Autodetection (would split input shape into two groups)
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& thePresentation,
                                  const TopoDS_Shape&                    theShape,
                                  const occ::handle<Prs3d_Drawer>&       theDrawer,
                                  const StdPrs_Volume theVolume = StdPrs_Volume_Autodetection,
                                  const occ::handle<Graphic3d_Group>& theGroup = nullptr);

  //! Shades <theShape> with texture coordinates.
  //! @param theVolumeType defines the way how to interpret input shapes - as Closed volumes (to
  //! activate back-face culling and capping plane algorithms), as Open volumes (shells or solids
  //! with holes) or to perform Autodetection (would split input shape into two groups)
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& thePresentation,
                                  const TopoDS_Shape&                    theShape,
                                  const occ::handle<Prs3d_Drawer>&       theDrawer,
                                  const bool                             theHasTexels,
                                  const gp_Pnt2d&                        theUVOrigin,
                                  const gp_Pnt2d&                        theUVRepeat,
                                  const gp_Pnt2d&                        theUVScale,
                                  const StdPrs_Volume theVolume = StdPrs_Volume_Autodetection,
                                  const occ::handle<Graphic3d_Group>& theGroup = nullptr);

  //! Searches closed and unclosed subshapes in shape structure and puts them
  //! into two compounds for separate processing of closed and unclosed sub-shapes
  Standard_EXPORT static void ExploreSolids(const TopoDS_Shape& theShape,
                                            const BRep_Builder& theBuilder,
                                            TopoDS_Compound&    theClosed,
                                            TopoDS_Compound&    theOpened,
                                            const bool          theIgnore1DSubShape);

  //! Computes wireframe presentation for free wires and vertices
  Standard_EXPORT static void AddWireframeForFreeElements(
    const occ::handle<Prs3d_Presentation>& thePrs,
    const TopoDS_Shape&                    theShape,
    const occ::handle<Prs3d_Drawer>&       theDrawer);

  //! Computes special wireframe presentation for faces without triangulation.
  Standard_EXPORT static void AddWireframeForFacesWithoutTriangles(
    const occ::handle<Prs3d_Presentation>& thePrs,
    const TopoDS_Shape&                    theShape,
    const occ::handle<Prs3d_Drawer>&       theDrawer);

public:
  //! Create primitive array with triangles for specified shape.
  //! @param[in] theShape  the shape with precomputed triangulation
  static occ::handle<Graphic3d_ArrayOfTriangles> FillTriangles(const TopoDS_Shape& theShape)
  {
    gp_Pnt2d aDummy;
    return FillTriangles(theShape, false, aDummy, aDummy, aDummy);
  }

  //! Create primitive array of triangles for specified shape.
  //! @param theShape     the shape with precomputed triangulation
  //! @param theHasTexels define UV coordinates in primitive array
  //! @param theUVOrigin  origin for UV coordinates
  //! @param theUVRepeat  repeat parameters  for UV coordinates
  //! @param theUVScale   scale coefficients for UV coordinates
  //! @return triangles array or NULL if specified face does not have computed triangulation
  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfTriangles> FillTriangles(
    const TopoDS_Shape& theShape,
    const bool          theHasTexels,
    const gp_Pnt2d&     theUVOrigin,
    const gp_Pnt2d&     theUVRepeat,
    const gp_Pnt2d&     theUVScale);

  //! Define primitive array of boundary segments for specified shape.
  //! @param theShape segments array or NULL if specified face does not have computed triangulation
  //! @param theUpperContinuity the most edge continuity class to be included to result (edges with
  //! more continuity will be ignored)
  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfSegments> FillFaceBoundaries(
    const TopoDS_Shape& theShape,
    GeomAbs_Shape       theUpperContinuity = GeomAbs_CN);
};
