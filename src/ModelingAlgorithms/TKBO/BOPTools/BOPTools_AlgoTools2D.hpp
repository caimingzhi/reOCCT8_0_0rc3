#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
class TopoDS_Edge;
class TopoDS_Face;
class gp_Vec;
class Geom2d_Curve;
class Geom_Curve;
class BRepAdaptor_Surface;
class IntTools_Context;

class BOPTools_AlgoTools2D
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void BuildPCurveForEdgeOnFace(
    const TopoDS_Edge&                   aE,
    const TopoDS_Face&                   aF,
    const occ::handle<IntTools_Context>& theContext = occ::handle<IntTools_Context>());

  Standard_EXPORT static bool EdgeTangent(const TopoDS_Edge& anE, const double aT, gp_Vec& Tau);

  Standard_EXPORT static void PointOnSurface(
    const TopoDS_Edge&                   aE,
    const TopoDS_Face&                   aF,
    const double                         aT,
    double&                              U,
    double&                              V,
    const occ::handle<IntTools_Context>& theContext = occ::handle<IntTools_Context>());

  Standard_EXPORT static void CurveOnSurface(
    const TopoDS_Edge&                   aE,
    const TopoDS_Face&                   aF,
    occ::handle<Geom2d_Curve>&           aC,
    double&                              aToler,
    const occ::handle<IntTools_Context>& theContext = occ::handle<IntTools_Context>());

  Standard_EXPORT static void CurveOnSurface(
    const TopoDS_Edge&                   aE,
    const TopoDS_Face&                   aF,
    occ::handle<Geom2d_Curve>&           aC,
    double&                              aFirst,
    double&                              aLast,
    double&                              aToler,
    const occ::handle<IntTools_Context>& theContext = occ::handle<IntTools_Context>());

  Standard_EXPORT static bool HasCurveOnSurface(const TopoDS_Edge&         aE,
                                                const TopoDS_Face&         aF,
                                                occ::handle<Geom2d_Curve>& aC,
                                                double&                    aFirst,
                                                double&                    aLast,
                                                double&                    aToler);

  Standard_EXPORT static bool HasCurveOnSurface(const TopoDS_Edge& aE, const TopoDS_Face& aF);

  Standard_EXPORT static void AdjustPCurveOnFace(
    const TopoDS_Face&                   theF,
    const occ::handle<Geom_Curve>&       theC3D,
    const occ::handle<Geom2d_Curve>&     theC2D,
    occ::handle<Geom2d_Curve>&           theC2DA,
    const occ::handle<IntTools_Context>& theContext = occ::handle<IntTools_Context>());

  Standard_EXPORT static void AdjustPCurveOnFace(
    const TopoDS_Face&                   theF,
    const double                         theFirst,
    const double                         theLast,
    const occ::handle<Geom2d_Curve>&     theC2D,
    occ::handle<Geom2d_Curve>&           theC2DA,
    const occ::handle<IntTools_Context>& theContext = occ::handle<IntTools_Context>());

  Standard_EXPORT static void AdjustPCurveOnSurf(const BRepAdaptor_Surface&       aF,
                                                 const double                     aT1,
                                                 const double                     aT2,
                                                 const occ::handle<Geom2d_Curve>& aC2D,
                                                 occ::handle<Geom2d_Curve>&       aC2DA);

  Standard_EXPORT static double IntermediatePoint(const double aFirst, const double aLast);

  Standard_EXPORT static double IntermediatePoint(const TopoDS_Edge& anE);

  Standard_EXPORT static void Make2D(
    const TopoDS_Edge&                   aE,
    const TopoDS_Face&                   aF,
    occ::handle<Geom2d_Curve>&           aC,
    double&                              aFirst,
    double&                              aLast,
    double&                              aToler,
    const occ::handle<IntTools_Context>& theContext = occ::handle<IntTools_Context>());

  Standard_EXPORT static void MakePCurveOnFace(
    const TopoDS_Face&                   aF,
    const occ::handle<Geom_Curve>&       C3D,
    occ::handle<Geom2d_Curve>&           aC,
    double&                              aToler,
    const occ::handle<IntTools_Context>& theContext = occ::handle<IntTools_Context>());

  Standard_EXPORT static void MakePCurveOnFace(
    const TopoDS_Face&                   aF,
    const occ::handle<Geom_Curve>&       C3D,
    const double                         aT1,
    const double                         aT2,
    occ::handle<Geom2d_Curve>&           aC,
    double&                              aToler,
    const occ::handle<IntTools_Context>& theContext = occ::handle<IntTools_Context>());

  Standard_EXPORT static int AttachExistingPCurve(const TopoDS_Edge&                   aEold,
                                                  const TopoDS_Edge&                   aEnew,
                                                  const TopoDS_Face&                   aF,
                                                  const occ::handle<IntTools_Context>& aCtx);

  Standard_EXPORT static void IsEdgeIsoline(const TopoDS_Edge& theE,
                                            const TopoDS_Face& theF,
                                            bool&              isTheUIso,
                                            bool&              isTheVIso);
};
