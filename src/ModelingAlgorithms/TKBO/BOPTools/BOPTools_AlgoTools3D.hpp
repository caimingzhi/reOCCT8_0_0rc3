#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class TopoDS_Edge;
class TopoDS_Face;
class gp_Dir;
class Geom_Surface;
class Geom2d_Curve;
class gp_Pnt;
class IntTools_Context;
class gp_Pnt2d;
class TopoDS_Shape;

class BOPTools_AlgoTools3D
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool DoSplitSEAMOnFace(const TopoDS_Edge& theESplit,
                                                const TopoDS_Face& theFace);

  Standard_EXPORT static bool DoSplitSEAMOnFace(const TopoDS_Edge& theEOrigin,
                                                const TopoDS_Edge& theESplit,
                                                const TopoDS_Face& theFace);

  Standard_EXPORT static void GetNormalToFaceOnEdge(
    const TopoDS_Edge&                   aE,
    const TopoDS_Face&                   aF,
    const double                         aT,
    gp_Dir&                              aD,
    const occ::handle<IntTools_Context>& theContext = occ::handle<IntTools_Context>());

  Standard_EXPORT static void GetNormalToFaceOnEdge(
    const TopoDS_Edge&                   aE,
    const TopoDS_Face&                   aF,
    gp_Dir&                              aD,
    const occ::handle<IntTools_Context>& theContext = occ::handle<IntTools_Context>());

  Standard_EXPORT static int SenseFlag(const gp_Dir& aNF1, const gp_Dir& aNF2);

  Standard_EXPORT static bool GetNormalToSurface(const occ::handle<Geom_Surface>& aS,
                                                 const double                     U,
                                                 const double                     V,
                                                 gp_Dir&                          aD);

  Standard_EXPORT static bool GetApproxNormalToFaceOnEdge(
    const TopoDS_Edge&                   aE,
    const TopoDS_Face&                   aF,
    const double                         aT,
    gp_Pnt&                              aPx,
    gp_Dir&                              aD,
    const occ::handle<IntTools_Context>& theContext);

  Standard_EXPORT static bool GetApproxNormalToFaceOnEdge(const TopoDS_Edge& theE,
                                                          const TopoDS_Face& theF,
                                                          const double       aT,
                                                          gp_Pnt&            aP,
                                                          gp_Dir&            aDNF,
                                                          const double       aDt2D);

  Standard_EXPORT static bool GetApproxNormalToFaceOnEdge(
    const TopoDS_Edge&                   theE,
    const TopoDS_Face&                   theF,
    const double                         aT,
    const double                         aDt2D,
    gp_Pnt&                              aP,
    gp_Dir&                              aDNF,
    const occ::handle<IntTools_Context>& theContext);

  Standard_EXPORT static int PointNearEdge(const TopoDS_Edge&                   aE,
                                           const TopoDS_Face&                   aF,
                                           const double                         aT,
                                           const double                         aDt2D,
                                           gp_Pnt2d&                            aP2D,
                                           gp_Pnt&                              aPx,
                                           const occ::handle<IntTools_Context>& theContext);

  Standard_EXPORT static int PointNearEdge(const TopoDS_Edge& aE,
                                           const TopoDS_Face& aF,
                                           const double       aT,
                                           const double       aDt2D,
                                           gp_Pnt2d&          aP2D,
                                           gp_Pnt&            aPx);

  Standard_EXPORT static int PointNearEdge(const TopoDS_Edge&                   aE,
                                           const TopoDS_Face&                   aF,
                                           const double                         aT,
                                           gp_Pnt2d&                            aP2D,
                                           gp_Pnt&                              aPx,
                                           const occ::handle<IntTools_Context>& theContext);

  Standard_EXPORT static int PointNearEdge(const TopoDS_Edge&                   aE,
                                           const TopoDS_Face&                   aF,
                                           gp_Pnt2d&                            aP2D,
                                           gp_Pnt&                              aPx,
                                           const occ::handle<IntTools_Context>& theContext);

  Standard_EXPORT static double MinStepIn2d();

  Standard_EXPORT static bool IsEmptyShape(const TopoDS_Shape& aS);

  Standard_EXPORT static void OrientEdgeOnFace(const TopoDS_Edge& aE,
                                               const TopoDS_Face& aF,
                                               TopoDS_Edge&       aER);

  Standard_EXPORT static int PointInFace(const TopoDS_Face&                   theF,
                                         gp_Pnt&                              theP,
                                         gp_Pnt2d&                            theP2D,
                                         const occ::handle<IntTools_Context>& theContext);

  Standard_EXPORT static int PointInFace(const TopoDS_Face&                   theF,
                                         const TopoDS_Edge&                   theE,
                                         const double                         theT,
                                         const double                         theDt2D,
                                         gp_Pnt&                              theP,
                                         gp_Pnt2d&                            theP2D,
                                         const occ::handle<IntTools_Context>& theContext);

  Standard_EXPORT static int PointInFace(const TopoDS_Face&                   theF,
                                         const occ::handle<Geom2d_Curve>&     theL,
                                         gp_Pnt&                              theP,
                                         gp_Pnt2d&                            theP2D,
                                         const occ::handle<IntTools_Context>& theContext,
                                         const double                         theDt2D = 0.0);
};
