#pragma once

#include <Adaptor3d_Surface.hpp>
#include <GeomAbs_Shape.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Sequence.hpp>

class Geom_Curve;
class gp_Ax2;
class Geom2d_Curve;
class gp_GTrsf2d;
class Adaptor3d_CurveOnSurface;
class Geom_BoundedCurve;
class gp_Pnt;
class gp_Vec;
class Geom_BoundedSurface;
class gp_Dir;
class Adaptor3d_Curve;
class Geom_BSplineSurface;
class Geom_BezierSurface;
class Geom_Surface;

typedef class Adaptor2d_Curve2d Adaptor2d_Curve2d;

class GeomLib
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Geom_Curve> To3d(const gp_Ax2&                    Position,
                                                      const occ::handle<Geom2d_Curve>& Curve2d);

  Standard_EXPORT static occ::handle<Geom2d_Curve> GTransform(
    const occ::handle<Geom2d_Curve>& Curve,
    const gp_GTrsf2d&                GTrsf);

  Standard_EXPORT static void SameRange(const double                     Tolerance,
                                        const occ::handle<Geom2d_Curve>& Curve2dPtr,
                                        const double                     First,
                                        const double                     Last,
                                        const double                     RequestedFirst,
                                        const double                     RequestedLast,
                                        occ::handle<Geom2d_Curve>&       NewCurve2dPtr);

  Standard_EXPORT static void BuildCurve3d(const double              Tolerance,
                                           Adaptor3d_CurveOnSurface& CurvePtr,
                                           const double              FirstParameter,
                                           const double              LastParameter,
                                           occ::handle<Geom_Curve>&  NewCurvePtr,
                                           double&                   MaxDeviation,
                                           double&                   AverageDeviation,
                                           const GeomAbs_Shape       Continuity = GeomAbs_C1,
                                           const int                 MaxDegree  = 14,
                                           const int                 MaxSegment = 30);

  Standard_EXPORT static void AdjustExtremity(occ::handle<Geom_BoundedCurve>& Curve,
                                              const gp_Pnt&                   P1,
                                              const gp_Pnt&                   P2,
                                              const gp_Vec&                   T1,
                                              const gp_Vec&                   T2);

  Standard_EXPORT static void ExtendCurveToPoint(occ::handle<Geom_BoundedCurve>& Curve,
                                                 const gp_Pnt&                   Point,
                                                 const int                       Cont,
                                                 const bool                      After);

  Standard_EXPORT static void ExtendSurfByLength(occ::handle<Geom_BoundedSurface>& Surf,
                                                 const double                      Length,
                                                 const int                         Cont,
                                                 const bool                        InU,
                                                 const bool                        After);

  Standard_EXPORT static void AxeOfInertia(const NCollection_Array1<gp_Pnt>& Points,
                                           gp_Ax2&                           Axe,
                                           bool&                             IsSingular,
                                           const double                      Tol = 1.0e-7);

  Standard_EXPORT static void Inertia(const NCollection_Array1<gp_Pnt>& Points,
                                      gp_Pnt&                           Bary,
                                      gp_Dir&                           XDir,
                                      gp_Dir&                           YDir,
                                      double&                           Xgap,
                                      double&                           YGap,
                                      double&                           ZGap);

  Standard_EXPORT static void RemovePointsFromArray(
    const int                                 NumPoints,
    const NCollection_Array1<double>&         InParameters,
    occ::handle<NCollection_HArray1<double>>& OutParameters);

  Standard_EXPORT static void DensifyArray1OfReal(
    const int                                 MinNumPoints,
    const NCollection_Array1<double>&         InParameters,
    occ::handle<NCollection_HArray1<double>>& OutParameters);

  Standard_EXPORT static void FuseIntervals(const NCollection_Array1<double>& Interval1,
                                            const NCollection_Array1<double>& Interval2,
                                            NCollection_Sequence<double>&     Fusion,
                                            const double                      Confusion = 1.0e-9,
                                            const bool IsAdjustToFirstInterval          = false);

  Standard_EXPORT static void EvalMaxParametricDistance(
    const Adaptor3d_Curve&            Curve,
    const Adaptor3d_Curve&            AReferenceCurve,
    const double                      Tolerance,
    const NCollection_Array1<double>& Parameters,
    double&                           MaxDistance);

  Standard_EXPORT static void EvalMaxDistanceAlongParameter(
    const Adaptor3d_Curve&            Curve,
    const Adaptor3d_Curve&            AReferenceCurve,
    const double                      Tolerance,
    const NCollection_Array1<double>& Parameters,
    double&                           MaxDistance);

  Standard_EXPORT static void CancelDenominatorDerivative(occ::handle<Geom_BSplineSurface>& BSurf,
                                                          const bool UDirection,
                                                          const bool VDirection);

  Standard_EXPORT static int NormEstim(const occ::handle<Geom_Surface>& theSurf,
                                       const gp_Pnt2d&                  theUV,
                                       const double                     theTol,
                                       gp_Dir&                          theNorm);

  Standard_EXPORT static void IsClosed(const occ::handle<Geom_Surface>& S,
                                       const double                     Tol,
                                       bool&                            isUClosed,
                                       bool&                            isVClosed);

  Standard_EXPORT static bool IsBSplUClosed(const occ::handle<Geom_BSplineSurface>& S,
                                            const double                            U1,
                                            const double                            U2,
                                            const double                            Tol);

  Standard_EXPORT static bool IsBSplVClosed(const occ::handle<Geom_BSplineSurface>& S,
                                            const double                            V1,
                                            const double                            V2,
                                            const double                            Tol);

  Standard_EXPORT static bool IsBzUClosed(const occ::handle<Geom_BezierSurface>& S,
                                          const double                           U1,
                                          const double                           U2,
                                          const double                           Tol);

  Standard_EXPORT static bool IsBzVClosed(const occ::handle<Geom_BezierSurface>& S,
                                          const double                           V1,
                                          const double                           V2,
                                          const double                           Tol);

  Standard_EXPORT static bool isIsoLine(const occ::handle<Adaptor2d_Curve2d>& theC2D,
                                        bool&                                 theIsU,
                                        double&                               theParam,
                                        bool&                                 theIsForward);

  Standard_EXPORT static occ::handle<Geom_Curve> buildC3dOnIsoLine(
    const occ::handle<Adaptor2d_Curve2d>& theC2D,
    const occ::handle<Adaptor3d_Surface>& theSurf,
    const double                          theFirst,
    const double                          theLast,
    const double                          theTolerance,
    const bool                            theIsU,
    const double                          theParam,
    const bool                            theIsForward);
};
