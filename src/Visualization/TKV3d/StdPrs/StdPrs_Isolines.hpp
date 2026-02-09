#pragma once

#include <BRepAdaptor_Surface.hpp>
#include <Geom_Surface.hpp>
#include <gp_Lin2d.hpp>
#include <Prs3d_LineAspect.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <NCollection_List.hpp>
#include <StdPrs_DeflectionCurve.hpp>
#include <StdPrs_ToolTriangulatedShape.hpp>

class TopLoc_Location;

class StdPrs_Isolines : public Prs3d_Root
{
public:
  inline static void Add(const occ::handle<Prs3d_Presentation>& thePresentation,
                         const TopoDS_Face&                     theFace,
                         const occ::handle<Prs3d_Drawer>&       theDrawer,
                         const double                           theDeflection)
  {
    if (theDrawer->IsoOnTriangulation() && StdPrs_ToolTriangulatedShape::IsTriangulated(theFace))
    {
      AddOnTriangulation(thePresentation, theFace, theDrawer);
    }
    else
    {
      AddOnSurface(thePresentation, theFace, theDrawer, theDeflection);
    }
  }

  static void Add(const TopoDS_Face&                                            theFace,
                  const occ::handle<Prs3d_Drawer>&                              theDrawer,
                  const double                                                  theDeflection,
                  NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>& theUPolylines,
                  NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>& theVPolylines)
  {
    if (theDrawer->IsoOnTriangulation() && StdPrs_ToolTriangulatedShape::IsTriangulated(theFace))
    {
      AddOnTriangulation(theFace, theDrawer, theUPolylines, theVPolylines);
    }
    else
    {
      AddOnSurface(theFace, theDrawer, theDeflection, theUPolylines, theVPolylines);
    }
  }

  Standard_EXPORT static void AddOnTriangulation(
    const occ::handle<Prs3d_Presentation>& thePresentation,
    const TopoDS_Face&                     theFace,
    const occ::handle<Prs3d_Drawer>&       theDrawer);

  Standard_EXPORT static void AddOnTriangulation(
    const TopoDS_Face&                                            theFace,
    const occ::handle<Prs3d_Drawer>&                              theDrawer,
    NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>& theUPolylines,
    NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>& theVPolylines);

  Standard_EXPORT static void AddOnTriangulation(
    const occ::handle<Prs3d_Presentation>& thePresentation,
    const occ::handle<Poly_Triangulation>& theTriangulation,
    const occ::handle<Geom_Surface>&       theSurface,
    const TopLoc_Location&                 theLocation,
    const occ::handle<Prs3d_Drawer>&       theDrawer,
    const NCollection_Sequence<double>&    theUIsoParams,
    const NCollection_Sequence<double>&    theVIsoParams);

  Standard_EXPORT static void AddOnSurface(const occ::handle<Prs3d_Presentation>& thePresentation,
                                           const TopoDS_Face&                     theFace,
                                           const occ::handle<Prs3d_Drawer>&       theDrawer,
                                           const double                           theDeflection);

  Standard_EXPORT static void AddOnSurface(
    const TopoDS_Face&                                            theFace,
    const occ::handle<Prs3d_Drawer>&                              theDrawer,
    const double                                                  theDeflection,
    NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>& theUPolylines,
    NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>& theVPolylines);

  Standard_EXPORT static void AddOnSurface(const occ::handle<Prs3d_Presentation>&  thePresentation,
                                           const occ::handle<BRepAdaptor_Surface>& theSurface,
                                           const occ::handle<Prs3d_Drawer>&        theDrawer,
                                           const double                            theDeflection,
                                           const NCollection_Sequence<double>&     theUIsoParams,
                                           const NCollection_Sequence<double>&     theVIsoParams);

  Standard_EXPORT static void UVIsoParameters(const TopoDS_Face&            theFace,
                                              const int                     theNbIsoU,
                                              const int                     theNbIsoV,
                                              const double                  theUVLimit,
                                              NCollection_Sequence<double>& theUIsoParams,
                                              NCollection_Sequence<double>& theVIsoParams,
                                              double&                       theUmin,
                                              double&                       theUmax,
                                              double&                       theVmin,
                                              double&                       theVmax);

public:
  struct PntOnIso
  {
    gp_Pnt Pnt;
    double Param;
  };

  struct SegOnIso
  {

    PntOnIso Pnts[2];

    operator PntOnIso*() { return Pnts; }

    operator const PntOnIso*() const { return Pnts; }

    bool operator<(const SegOnIso& theOther) const
    {
      return Pnts[1].Param < theOther.Pnts[0].Param;
    }
  };

private:
  Standard_EXPORT static void addOnSurface(
    const occ::handle<BRepAdaptor_Surface>&                       theSurface,
    const occ::handle<Prs3d_Drawer>&                              theDrawer,
    const double                                                  theDeflection,
    const NCollection_Sequence<double>&                           theUIsoParams,
    const NCollection_Sequence<double>&                           theVIsoParams,
    NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>& theUPolylines,
    NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>& theVPolylines);

  Standard_EXPORT static void addOnTriangulation(
    const occ::handle<Poly_Triangulation>&                        theTriangulation,
    const occ::handle<Geom_Surface>&                              theSurface,
    const TopLoc_Location&                                        theLocation,
    const NCollection_Sequence<double>&                           theUIsoParams,
    const NCollection_Sequence<double>&                           theVIsoParams,
    NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>& theUPolylines,
    NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>& theVPolylines);

  Standard_EXPORT static bool findSegmentOnTriangulation(
    const occ::handle<Geom_Surface>& theSurface,
    const bool                       theIsU,
    const gp_Lin2d&                  theIsoline,
    const gp_Pnt*                    theNodesXYZ,
    const gp_Pnt2d*                  theNodesUV,
    SegOnIso&                        theSegment);
};
