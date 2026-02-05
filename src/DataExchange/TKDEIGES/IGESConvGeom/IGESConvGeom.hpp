#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
class IGESGeom_SplineCurve;
class Geom_BSplineCurve;
class Geom2d_BSplineCurve;
class IGESGeom_SplineSurface;
class Geom_BSplineSurface;

//! This package is intended to gather geometric conversion which
//! are not immediate but can be used for several purposes :
//! mainly, standard conversion to and from CasCade geometric and
//! topologic data, and adaptations of IGES files as required
//! (as replacing Spline entities to BSpline equivalents).
class IGESConvGeom
{
public:
  DEFINE_STANDARD_ALLOC

  //! basic tool to build curves from IGESGeom (arrays of points,
  //! Transformations, evaluation of points in a datum)
  //! Converts a SplineCurve from IGES to a BSplineCurve from CasCade
  //! <epscoef> gives tolerance to consider coefficient to be nul
  //! <epsgeom> gives tolerance to consider poles to be equal
  //! The returned value is a status with these possible values :
  //! - 0  OK, done
  //! - 1  the result is not guaranteed to be C0 (with <epsgeom>)
  //! - 2  SplineType not processed (allowed : max 3)
  //! (no result produced)
  //! - 3  error during creation of control points
  //! (no result produced)
  //! - 4  polynomial equation is not correct (no result produced)
  //! - 5  less than one segment (no result produced)
  Standard_EXPORT static int SplineCurveFromIGES(const occ::handle<IGESGeom_SplineCurve>& igesent,
                                                 const double                             epscoef,
                                                 const double                             epsgeom,
                                                 occ::handle<Geom_BSplineCurve>&          result);

  //! Tries to increase curve continuity with tolerance <epsgeom>
  //! <continuity> is the new desired continuity, can be 1 or 2
  //! (more than 2 is considered as 2).
  //! Returns the new maximum continuity obtained on all knots.
  //! Remark that, for instance with <continuity> = 2, even if not
  //! all the knots can be passed to C2, all knots which can be are.
  Standard_EXPORT static int IncreaseCurveContinuity(const occ::handle<Geom_BSplineCurve>& curve,
                                                     const double                          epsgeom,
                                                     const int continuity = 2);

  Standard_EXPORT static int IncreaseCurveContinuity(const occ::handle<Geom2d_BSplineCurve>& curve,
                                                     const double epsgeom,
                                                     const int    continuity = 2);

  //! Converts a SplineSurface from IGES to a BSplineSurface from CasCade
  //! <epscoef> gives tolerance to consider coefficient to be nul
  //! <epsgeom> gives tolerance to consider poles to be equal
  //! The returned value is a status with these possible values :
  //! - 0  OK, done
  //! - 1  the result is not guaranteed to be C0 (with <epsgeom>)
  //! - 2  degree is not compatible with code boundary type
  //! (warning) but C0 is OK
  //! - 3  idem but C0 is not guaranteed (warning)
  //! - 4  degree has been determined to be nul, either in U or V
  //! (no result produced)
  //! - 5  less than one segment in U or V (no result produced)
  Standard_EXPORT static int SplineSurfaceFromIGES(
    const occ::handle<IGESGeom_SplineSurface>& igesent,
    const double                               epscoef,
    const double                               epsgeom,
    occ::handle<Geom_BSplineSurface>&          result);

  //! Tries to increase Surface continuity with tolerance <epsgeom>
  //! <continuity> is the new desired continuity, can be 1 or 2
  //! (more than 2 is considered as 2).
  //! Returns the new maximum continuity obtained on all knots.
  //! Remark that, for instance with <continuity> = 2, even if not
  //! all the knots can be passed to C2, all knots which can be are.
  Standard_EXPORT static int IncreaseSurfaceContinuity(
    const occ::handle<Geom_BSplineSurface>& surface,
    const double                            epsgeom,
    const int                               continuity = 2);
};
