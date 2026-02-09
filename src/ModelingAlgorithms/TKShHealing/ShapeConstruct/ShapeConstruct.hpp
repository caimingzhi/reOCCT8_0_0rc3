#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TopAbs_Orientation.hpp>
class Geom_BSplineCurve;
class Geom_Curve;
class Geom2d_BSplineCurve;
class Geom2d_Curve;
class Geom_BSplineSurface;
class Geom_Surface;
class TopoDS_Face;
class TopoDS_Edge;

class ShapeConstruct
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Geom_BSplineCurve> ConvertCurveToBSpline(
    const occ::handle<Geom_Curve>& C3D,
    const double                   First,
    const double                   Last,
    const double                   Tol3d,
    const GeomAbs_Shape            Continuity,
    const int                      MaxSegments,
    const int                      MaxDegree);

  Standard_EXPORT static occ::handle<Geom2d_BSplineCurve> ConvertCurveToBSpline(
    const occ::handle<Geom2d_Curve>& C2D,
    const double                     First,
    const double                     Last,
    const double                     Tol2d,
    const GeomAbs_Shape              Continuity,
    const int                        MaxSegments,
    const int                        MaxDegree);

  Standard_EXPORT static occ::handle<Geom_BSplineSurface> ConvertSurfaceToBSpline(
    const occ::handle<Geom_Surface>& surf,
    const double                     UF,
    const double                     UL,
    const double                     VF,
    const double                     VL,
    const double                     Tol3d,
    const GeomAbs_Shape              Continuity,
    const int                        MaxSegments,
    const int                        MaxDegree);

  Standard_EXPORT static bool JoinPCurves(
    const occ::handle<NCollection_HSequence<TopoDS_Shape>>& theEdges,
    const TopoDS_Face&                                      theFace,
    TopoDS_Edge&                                            theEdge);

  Standard_EXPORT static bool JoinCurves(const occ::handle<Geom_Curve>& c3d1,
                                         const occ::handle<Geom_Curve>& ac3d2,
                                         const TopAbs_Orientation       Orient1,
                                         const TopAbs_Orientation       Orient2,
                                         double&                        first1,
                                         double&                        last1,
                                         double&                        first2,
                                         double&                        last2,
                                         occ::handle<Geom_Curve>&       c3dOut,
                                         bool&                          isRev1,
                                         bool&                          isRev2);

  Standard_EXPORT static bool JoinCurves(const occ::handle<Geom2d_Curve>& c2d1,
                                         const occ::handle<Geom2d_Curve>& ac2d2,
                                         const TopAbs_Orientation         Orient1,
                                         const TopAbs_Orientation         Orient2,
                                         double&                          first1,
                                         double&                          last1,
                                         double&                          first2,
                                         double&                          last2,
                                         occ::handle<Geom2d_Curve>&       c2dOut,
                                         bool&                            isRev1,
                                         bool&                            isRev2,
                                         const bool                       isError = false);
};
