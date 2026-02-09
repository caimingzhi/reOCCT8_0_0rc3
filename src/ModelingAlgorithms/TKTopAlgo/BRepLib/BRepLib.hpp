#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>

class Geom2d_Curve;
class Adaptor3d_Curve;
class Geom_Plane;
class TopoDS_Shape;
class TopoDS_Solid;
class TopoDS_Face;
class BRepTools_ReShape;

class BRepLib
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Precision(const double P);

  Standard_EXPORT static double Precision();

  Standard_EXPORT static void Plane(const occ::handle<Geom_Plane>& P);

  Standard_EXPORT static const occ::handle<Geom_Plane>& Plane();

  Standard_EXPORT static bool CheckSameRange(const TopoDS_Edge& E,
                                             const double       Confusion = 1.0e-12);

  Standard_EXPORT static void SameRange(const TopoDS_Edge& E, const double Tolerance = 1.0e-5);

  Standard_EXPORT static bool BuildCurve3d(const TopoDS_Edge&  E,
                                           const double        Tolerance  = 1.0e-5,
                                           const GeomAbs_Shape Continuity = GeomAbs_C1,
                                           const int           MaxDegree  = 14,
                                           const int           MaxSegment = 0);

  Standard_EXPORT static bool BuildCurves3d(const TopoDS_Shape& S,
                                            const double        Tolerance,
                                            const GeomAbs_Shape Continuity = GeomAbs_C1,
                                            const int           MaxDegree  = 14,
                                            const int           MaxSegment = 0);

  Standard_EXPORT static bool BuildCurves3d(const TopoDS_Shape& S);

  Standard_EXPORT static void BuildPCurveForEdgeOnPlane(const TopoDS_Edge& theE,
                                                        const TopoDS_Face& theF);

  Standard_EXPORT static void BuildPCurveForEdgeOnPlane(const TopoDS_Edge&         theE,
                                                        const TopoDS_Face&         theF,
                                                        occ::handle<Geom2d_Curve>& aC2D,
                                                        bool&                      bToUpdate);

  template <class TCont>
  static void BuildPCurveForEdgesOnPlane(const TCont& theLE, const TopoDS_Face& theF)
  {
    for (typename TCont::Iterator aIt(theLE); aIt.More(); aIt.Next())
    {
      const TopoDS_Edge& aE = TopoDS::Edge(aIt.Value());
      if (!aE.IsNull())
        BRepLib::BuildPCurveForEdgeOnPlane(aE, theF);
    }
  }

  Standard_EXPORT static bool UpdateEdgeTol(const TopoDS_Edge& E,
                                            const double       MinToleranceRequest,
                                            const double       MaxToleranceToCheck);

  Standard_EXPORT static bool UpdateEdgeTolerance(const TopoDS_Shape& S,
                                                  const double        MinToleranceRequest,
                                                  const double        MaxToleranceToCheck);

  Standard_EXPORT static void SameParameter(const TopoDS_Edge& theEdge,
                                            const double       Tolerance = 1.0e-5);

  Standard_EXPORT static TopoDS_Edge SameParameter(const TopoDS_Edge& theEdge,
                                                   const double       theTolerance,
                                                   double&            theNewTol,
                                                   const bool         IsUseOldEdge);

  Standard_EXPORT static void SameParameter(const TopoDS_Shape& S,
                                            const double        Tolerance = 1.0e-5,
                                            const bool          forced    = false);

  Standard_EXPORT static void SameParameter(const TopoDS_Shape& S,
                                            BRepTools_ReShape&  theReshaper,
                                            const double        Tolerance = 1.0e-5,
                                            const bool          forced    = false);

  Standard_EXPORT static void UpdateTolerances(const TopoDS_Shape& S,
                                               const bool          verifyFaceTolerance = false);

  Standard_EXPORT static void UpdateTolerances(const TopoDS_Shape& S,
                                               BRepTools_ReShape&  theReshaper,
                                               const bool          verifyFaceTolerance = false);

  Standard_EXPORT static void UpdateInnerTolerances(const TopoDS_Shape& S);

  Standard_EXPORT static bool OrientClosedSolid(TopoDS_Solid& solid);

  Standard_EXPORT static GeomAbs_Shape ContinuityOfFaces(const TopoDS_Edge& theEdge,
                                                         const TopoDS_Face& theFace1,
                                                         const TopoDS_Face& theFace2,
                                                         const double       theAngleTol);

  Standard_EXPORT static void EncodeRegularity(const TopoDS_Shape& S,
                                               const double        TolAng = 1.0e-10);

  Standard_EXPORT static void EncodeRegularity(const TopoDS_Shape&                   S,
                                               const NCollection_List<TopoDS_Shape>& LE,
                                               const double TolAng = 1.0e-10);

  Standard_EXPORT static void EncodeRegularity(TopoDS_Edge&       E,
                                               const TopoDS_Face& F1,
                                               const TopoDS_Face& F2,
                                               const double       TolAng = 1.0e-10);

  Standard_EXPORT static void SortFaces(const TopoDS_Shape& S, NCollection_List<TopoDS_Shape>& LF);

  Standard_EXPORT static void ReverseSortFaces(const TopoDS_Shape&             S,
                                               NCollection_List<TopoDS_Shape>& LF);

  Standard_EXPORT static bool EnsureNormalConsistency(const TopoDS_Shape& S,
                                                      const double        theAngTol  = 0.001,
                                                      const bool ForceComputeNormals = false);

  Standard_EXPORT static void UpdateDeflection(const TopoDS_Shape& S);

  Standard_EXPORT static void BoundingVertex(const NCollection_List<TopoDS_Shape>& theLV,
                                             gp_Pnt&                               theNewCenter,
                                             double&                               theNewTol);

  Standard_EXPORT static bool FindValidRange(const Adaptor3d_Curve& theCurve,
                                             const double           theTolE,
                                             const double           theParV1,
                                             const gp_Pnt&          thePntV1,
                                             const double           theTolV1,
                                             const double           theParV2,
                                             const gp_Pnt&          thePntV2,
                                             const double           theTolV2,
                                             double&                theFirst,
                                             double&                theLast);

  Standard_EXPORT static bool FindValidRange(const TopoDS_Edge& theEdge,
                                             double&            theFirst,
                                             double&            theLast);

  Standard_EXPORT static void ExtendFace(const TopoDS_Face& theF,
                                         const double       theExtVal,
                                         const bool         theExtUMin,
                                         const bool         theExtUMax,
                                         const bool         theExtVMin,
                                         const bool         theExtVMax,
                                         TopoDS_Face&       theFExtended);
};
