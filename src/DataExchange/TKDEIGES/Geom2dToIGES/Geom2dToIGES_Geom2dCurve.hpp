#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom2dToIGES_Geom2dEntity.hpp>
class IGESData_IGESEntity;
class Geom2d_Curve;

//! This class implements the transfer of the Curve Entity from Geom2d
//! To IGES. These can be:
//! Curve
//! . BoundedCurve
//! * BSplineCurve
//! * BezierCurve
//! * TrimmedCurve
//! . Conic
//! * Circle
//! * Ellipse
//! * Hyperbloa
//! * Line
//! * Parabola
//! . OffsetCurve
class Geom2dToIGES_Geom2dCurve : public Geom2dToIGES_Geom2dEntity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dToIGES_Geom2dCurve();

  //! Creates a tool Geom2dCurve ready to run and sets its
  //! fields as G2dE's.
  Standard_EXPORT Geom2dToIGES_Geom2dCurve(const Geom2dToIGES_Geom2dEntity& G2dE);

  //! Transfer an Entity from Geom2d to IGES. If this
  //! Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESData_IGESEntity> Transfer2dCurve(
    const occ::handle<Geom2d_Curve>& start,
    const double                     Udeb,
    const double                     Ufin);
};
