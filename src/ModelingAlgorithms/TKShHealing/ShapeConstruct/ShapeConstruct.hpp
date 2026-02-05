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

//! This package provides new algorithms for constructing
//! new geometrical objects and topological shapes. It
//! complements and extends algorithms available in Open
//! CASCADE topological and geometrical toolkist.
//! The functionality provided by this package are the
//! following:
//! projecting curves on surface,
//! adjusting curve to have given start and end points. P
class ShapeConstruct
{
public:
  DEFINE_STANDARD_ALLOC

  //! Tool for wire triangulation
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

  //! join pcurves of the <theEdge> on the <theFace>
  //! try to use pcurves from originas edges <theEdges>
  //! Returns false if cannot join pcurves
  Standard_EXPORT static bool JoinPCurves(
    const occ::handle<NCollection_HSequence<TopoDS_Shape>>& theEdges,
    const TopoDS_Face&                                      theFace,
    TopoDS_Edge&                                            theEdge);

  //! Method for joininig curves 3D.
  //! Parameters : c3d1,ac3d2 - initial curves
  //! Orient1, Orient2 - initial edges orientations.
  //! first1,last1,first2,last2 - parameters for trimming curves
  //! (re-calculate with account of orientation edges)
  //! c3dOut - result curve
  //! isRev1,isRev2 - out parameters indicative on possible errors.
  //! Return value : True - if curves were joined successfully,
  //! else - False.
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

  //! Method for joininig curves 3D.
  //! Parameters : c3d1,ac3d2 - initial curves
  //! Orient1, Orient2 - initial edges orientations.
  //! first1,last1,first2,last2 - parameters for trimming curves
  //! (re-calculate with account of orientation edges)
  //! c3dOut - result curve
  //! isRev1,isRev2 - out parameters indicative on possible errors.
  //! isError - input parameter indicative possible errors due to that one from edges have one
  //! vertex Return value : True - if curves were joined successfully, else - False.
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
