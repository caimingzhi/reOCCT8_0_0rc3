#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <TopAbs_State.hpp>
#include <IntTools_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <Precision.hpp>
class TopoDS_Vertex;
class TopoDS_Wire;
class TopoDS_Face;
class gp_Pnt2d;
class TopoDS_Edge;
class IntTools_CommonPrt;
class gp_Pnt;
class IntTools_Curve;
class gp_Dir;
class Geom_Curve;
class Bnd_Box;
class IntTools_Range;
class gp_Lin;
class gp_Pln;
class Geom2d_Curve;
class Geom_Surface;

class IntTools_Tools
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static int ComputeVV(const TopoDS_Vertex& V1, const TopoDS_Vertex& V2);

  Standard_EXPORT static bool HasInternalEdge(const TopoDS_Wire& aW);

  Standard_EXPORT static void MakeFaceFromWireAndFace(const TopoDS_Wire& aW,
                                                      const TopoDS_Face& aF,
                                                      TopoDS_Face&       aFNew);

  Standard_EXPORT static TopAbs_State ClassifyPointByFace(const TopoDS_Face& aF, const gp_Pnt2d& P);

  Standard_EXPORT static bool IsVertex(const TopoDS_Edge& E, const double t);

  Standard_EXPORT static bool IsVertex(const TopoDS_Edge&   E,
                                       const TopoDS_Vertex& V,
                                       const double         t);

  Standard_EXPORT static bool IsVertex(const IntTools_CommonPrt& aCmnPrt);

  Standard_EXPORT static bool IsMiddlePointsEqual(const TopoDS_Edge& E1, const TopoDS_Edge& E2);

  Standard_EXPORT static bool IsVertex(const gp_Pnt&        aP,
                                       const double         aTolPV,
                                       const TopoDS_Vertex& aV);

  Standard_EXPORT static double IntermediatePoint(const double aFirst, const double aLast);

  Standard_EXPORT static int SplitCurve(const IntTools_Curve&                 aC,
                                        NCollection_Sequence<IntTools_Curve>& aS);

  Standard_EXPORT static void RejectLines(const NCollection_Sequence<IntTools_Curve>& aSIn,
                                          NCollection_Sequence<IntTools_Curve>&       aSOut);

  Standard_EXPORT static bool IsDirsCoinside(const gp_Dir& D1, const gp_Dir& D2);

  Standard_EXPORT static bool IsDirsCoinside(const gp_Dir& D1, const gp_Dir& D2, const double aTol);

  Standard_EXPORT static bool IsClosed(const occ::handle<Geom_Curve>& aC);

  Standard_EXPORT static double CurveTolerance(const occ::handle<Geom_Curve>& aC,
                                               const double                   aTolBase);

  Standard_EXPORT static bool CheckCurve(const IntTools_Curve& theCurve, Bnd_Box& theBox);

  Standard_EXPORT static bool IsOnPave(const double          theT,
                                       const IntTools_Range& theRange,
                                       const double          theTol);

  Standard_EXPORT static void VertexParameters(const IntTools_CommonPrt& theCP,
                                               double&                   theT1,
                                               double&                   theT2);

  Standard_EXPORT static void VertexParameter(const IntTools_CommonPrt& theCP, double& theT);

  Standard_EXPORT static bool IsOnPave1(const double          theT,
                                        const IntTools_Range& theRange,
                                        const double          theTol);

  Standard_EXPORT static bool IsInRange(const IntTools_Range& theRRef,
                                        const IntTools_Range& theR,
                                        const double          theTol);

  Standard_EXPORT static int SegPln(const gp_Lin& theLin,
                                    const double  theTLin1,
                                    const double  theTLin2,
                                    const double  theTolLin,
                                    const gp_Pln& thePln,
                                    const double  theTolPln,
                                    gp_Pnt&       theP,
                                    double&       theT,
                                    double&       theTolP,
                                    double&       theTmin,
                                    double&       theTmax);

  Standard_EXPORT static bool ComputeTolerance(const occ::handle<Geom_Curve>&   theCurve3D,
                                               const occ::handle<Geom2d_Curve>& theCurve2D,
                                               const occ::handle<Geom_Surface>& theSurf,
                                               const double                     theFirst,
                                               const double                     theLast,
                                               double&                          theMaxDist,
                                               double&                          theMaxPar,
                                               const double theTolRange = Precision::PConfusion(),
                                               const bool   theToRunParallel = false);

  Standard_EXPORT static double ComputeIntRange(const double theTol1,
                                                const double theTol2,
                                                const double theAngle);
};
