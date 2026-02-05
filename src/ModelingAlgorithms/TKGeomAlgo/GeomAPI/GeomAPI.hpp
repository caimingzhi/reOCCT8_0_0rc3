#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom2d_Curve.hpp>
#include <Geom_Curve.hpp>

class gp_Pln;

//! The GeomAPI package provides an Application
//! Programming Interface for the Geometry.
//!
//! The API is a set of classes and methods aiming to
//! provide :
//!
//! * High level and simple calls for the most common
//! operations.
//!
//! * Keeping an access on the low-level
//! implementation of high-level calls.
//!
//! The API provides classes to call the algorithms
//! of the Geometry
//!
//! * The constructors of the classes provides the
//! different constructions methods.
//!
//! * The class keeps as fields the different tools
//! used by the algorithms
//!
//! * The class provides a casting method to get
//! automatically the result with a function-like
//! call.
//!
//! For example to evaluate the distance <D> between a
//! point <P> and a curve <C>, one can writes :
//!
//! D = GeomAPI_ProjectPointOnCurve(P,C);
//!
//! or
//!
//! GeomAPI_ProjectPointOnCurve PonC(P,C);
//! D = PonC.LowerDistance();
class GeomAPI
{
public:
  DEFINE_STANDARD_ALLOC

  //! This function builds (in the
  //! parametric space of the plane P) a 2D curve equivalent to the 3D curve
  //! C. The 3D curve C is considered to be located in the plane P.
  //! Warning
  //! The 3D curve C must be of one of the following types:
  //! -      a line
  //! -      a circle
  //! -      an ellipse
  //! -      a hyperbola
  //! -      a parabola
  //! -      a Bezier curve
  //! -      a BSpline curve
  //! Exceptions Standard_NoSuchObject if C is not a defined type curve.
  Standard_EXPORT static occ::handle<Geom2d_Curve> To2d(const occ::handle<Geom_Curve>& C,
                                                        const gp_Pln&                  P);

  //! Builds a 3D curve equivalent to the 2D curve C
  //! described in the parametric space defined by the local
  //! coordinate system of plane P.
  //! The resulting 3D curve is of the same nature as that of the curve C.
  Standard_EXPORT static occ::handle<Geom_Curve> To3d(const occ::handle<Geom2d_Curve>& C,
                                                      const gp_Pln&                    P);
};
