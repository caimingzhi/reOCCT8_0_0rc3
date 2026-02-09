#pragma once

#include <PrsDim_KindOfSurface.hpp>
#include <gp_Elips.hpp>
#include <gp_Pnt.hpp>
#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Bnd_Box;
class Geom_Curve;
class Geom_Plane;
class Geom_Surface;
class TopoDS_Edge;
class TopoDS_Face;
class TopoDS_Shape;
class TopoDS_Vertex;

class PrsDim
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static gp_Pnt Nearest(const TopoDS_Shape& aShape, const gp_Pnt& aPoint);

  Standard_EXPORT static gp_Pnt Nearest(const gp_Lin& theLine, const gp_Pnt& thePoint);

  Standard_EXPORT static bool Nearest(const occ::handle<Geom_Curve>& theCurve,
                                      const gp_Pnt&                  thePoint,
                                      const gp_Pnt&                  theFirstPoint,
                                      const gp_Pnt&                  theLastPoint,
                                      gp_Pnt&                        theNearestPoint);

  Standard_EXPORT static gp_Pnt Farest(const TopoDS_Shape& aShape, const gp_Pnt& aPoint);

  Standard_EXPORT static bool ComputeGeometry(const TopoDS_Edge&       theEdge,
                                              occ::handle<Geom_Curve>& theCurve,
                                              gp_Pnt&                  theFirstPnt,
                                              gp_Pnt&                  theLastPnt);

  Standard_EXPORT static bool ComputeGeometry(const TopoDS_Edge&       theEdge,
                                              occ::handle<Geom_Curve>& theCurve,
                                              gp_Pnt&                  theFirstPnt,
                                              gp_Pnt&                  theLastPnt,
                                              bool&                    theIsInfinite);

  Standard_EXPORT static bool ComputeGeometry(const TopoDS_Edge&             theEdge,
                                              occ::handle<Geom_Curve>&       theCurve,
                                              gp_Pnt&                        theFirstPnt,
                                              gp_Pnt&                        theLastPnt,
                                              occ::handle<Geom_Curve>&       theExtCurve,
                                              bool&                          theIsInfinite,
                                              bool&                          theIsOnPlane,
                                              const occ::handle<Geom_Plane>& thePlane);

  Standard_EXPORT static bool ComputeGeometry(const TopoDS_Edge&             theFirstEdge,
                                              const TopoDS_Edge&             theSecondEdge,
                                              occ::handle<Geom_Curve>&       theFirstCurve,
                                              occ::handle<Geom_Curve>&       theSecondCurve,
                                              gp_Pnt&                        theFirstPnt1,
                                              gp_Pnt&                        theLastPnt1,
                                              gp_Pnt&                        theFirstPnt2,
                                              gp_Pnt&                        theLastPnt2,
                                              const occ::handle<Geom_Plane>& thePlane);

  Standard_EXPORT static bool ComputeGeometry(const TopoDS_Edge&       theFirstEdge,
                                              const TopoDS_Edge&       theSecondEdge,
                                              occ::handle<Geom_Curve>& theFirstCurve,
                                              occ::handle<Geom_Curve>& theSecondCurve,
                                              gp_Pnt&                  theFirstPnt1,
                                              gp_Pnt&                  theLastPnt1,
                                              gp_Pnt&                  theFirstPnt2,
                                              gp_Pnt&                  theLastPnt2,
                                              bool&                    theIsinfinite1,
                                              bool&                    theIsinfinite2);

  Standard_EXPORT static bool ComputeGeometry(const TopoDS_Edge&             theFirstEdge,
                                              const TopoDS_Edge&             theSecondEdge,
                                              int&                           theExtIndex,
                                              occ::handle<Geom_Curve>&       theFirstCurve,
                                              occ::handle<Geom_Curve>&       theSecondCurve,
                                              gp_Pnt&                        theFirstPnt1,
                                              gp_Pnt&                        theLastPnt1,
                                              gp_Pnt&                        theFirstPnt2,
                                              gp_Pnt&                        theLastPnt2,
                                              occ::handle<Geom_Curve>&       theExtCurve,
                                              bool&                          theIsinfinite1,
                                              bool&                          theIsinfinite2,
                                              const occ::handle<Geom_Plane>& thePlane);

  Standard_EXPORT static bool ComputeGeomCurve(occ::handle<Geom_Curve>&       aCurve,
                                               const double                   first1,
                                               const double                   last1,
                                               gp_Pnt&                        FirstPnt1,
                                               gp_Pnt&                        LastPnt1,
                                               const occ::handle<Geom_Plane>& aPlane,
                                               bool&                          isOnPlane);

  Standard_EXPORT static bool ComputeGeometry(const TopoDS_Vertex&           aVertex,
                                              gp_Pnt&                        point,
                                              const occ::handle<Geom_Plane>& aPlane,
                                              bool&                          isOnPlane);

  Standard_EXPORT static bool GetPlaneFromFace(const TopoDS_Face&         aFace,
                                               gp_Pln&                    aPlane,
                                               occ::handle<Geom_Surface>& aSurf,
                                               PrsDim_KindOfSurface&      aSurfType,
                                               double&                    Offset);

  Standard_EXPORT static void InitFaceLength(const TopoDS_Face&         aFace,
                                             gp_Pln&                    aPlane,
                                             occ::handle<Geom_Surface>& aSurface,
                                             PrsDim_KindOfSurface&      aSurfaceType,
                                             double&                    anOffset);

  Standard_EXPORT static void InitLengthBetweenCurvilinearFaces(
    const TopoDS_Face&         theFirstFace,
    const TopoDS_Face&         theSecondFace,
    occ::handle<Geom_Surface>& theFirstSurf,
    occ::handle<Geom_Surface>& theSecondSurf,
    gp_Pnt&                    theFirstAttach,
    gp_Pnt&                    theSecondAttach,
    gp_Dir&                    theDirOnPlane);

  Standard_EXPORT static bool InitAngleBetweenPlanarFaces(const TopoDS_Face& theFirstFace,
                                                          const TopoDS_Face& theSecondFace,
                                                          gp_Pnt&            theCenter,
                                                          gp_Pnt&            theFirstAttach,
                                                          gp_Pnt&            theSecondAttach,
                                                          const bool theIsFirstPointSet = false);

  Standard_EXPORT static bool InitAngleBetweenCurvilinearFaces(
    const TopoDS_Face&         theFirstFace,
    const TopoDS_Face&         theSecondFace,
    const PrsDim_KindOfSurface theFirstSurfType,
    const PrsDim_KindOfSurface theSecondSurfType,
    gp_Pnt&                    theCenter,
    gp_Pnt&                    theFirstAttach,
    gp_Pnt&                    theSecondAttach,
    const bool                 theIsFirstPointSet = false);

  Standard_EXPORT static gp_Pnt ProjectPointOnPlane(const gp_Pnt& aPoint, const gp_Pln& aPlane);

  Standard_EXPORT static gp_Pnt ProjectPointOnLine(const gp_Pnt& aPoint, const gp_Lin& aLine);

  Standard_EXPORT static gp_Pnt TranslatePointToBound(const gp_Pnt&  aPoint,
                                                      const gp_Dir&  aDir,
                                                      const Bnd_Box& aBndBox);

  Standard_EXPORT static bool InDomain(const double aFirstPar,
                                       const double aLastPar,
                                       const double anAttachPar);

  Standard_EXPORT static gp_Pnt NearestApex(const gp_Elips& elips,
                                            const gp_Pnt&   pApex,
                                            const gp_Pnt&   nApex,
                                            const double    fpara,
                                            const double    lpara,
                                            bool&           IsInDomain);

  Standard_EXPORT static double DistanceFromApex(const gp_Elips& elips,
                                                 const gp_Pnt&   Apex,
                                                 const double    par);

  Standard_EXPORT static void ComputeProjEdgePresentation(
    const occ::handle<Prs3d_Presentation>& aPres,
    const occ::handle<Prs3d_Drawer>&       aDrawer,
    const TopoDS_Edge&                     anEdge,
    const occ::handle<Geom_Curve>&         ProjCurve,
    const gp_Pnt&                          FirstP,
    const gp_Pnt&                          LastP,
    const Quantity_NameOfColor             aColor   = Quantity_NOC_PURPLE,
    const double                           aWidth   = 2,
    const Aspect_TypeOfLine                aProjTOL = Aspect_TOL_DASH,
    const Aspect_TypeOfLine                aCallTOL = Aspect_TOL_DOT);

  Standard_EXPORT static void ComputeProjVertexPresentation(
    const occ::handle<Prs3d_Presentation>& aPres,
    const occ::handle<Prs3d_Drawer>&       aDrawer,
    const TopoDS_Vertex&                   aVertex,
    const gp_Pnt&                          ProjPoint,
    const Quantity_NameOfColor             aColor   = Quantity_NOC_PURPLE,
    const double                           aWidth   = 2,
    const Aspect_TypeOfMarker              aProjTOM = Aspect_TOM_PLUS,
    const Aspect_TypeOfLine                aCallTOL = Aspect_TOL_DOT);
};
