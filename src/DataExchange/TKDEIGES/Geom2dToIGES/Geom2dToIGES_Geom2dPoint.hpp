#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom2dToIGES_Geom2dEntity.hpp>
class IGESGeom_Point;
class Geom2d_Point;
class Geom2d_CartesianPoint;

//! This class implements the transfer of the Point Entity from Geom2d
//! to IGES. These are:
//! . 2dPoint
//! * 2dCartesianPoint
class Geom2dToIGES_Geom2dPoint : public Geom2dToIGES_Geom2dEntity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dToIGES_Geom2dPoint();

  //! Creates a tool Geom2dPoint ready to run and sets its
  //! fields as G2dE's.
  Standard_EXPORT Geom2dToIGES_Geom2dPoint(const Geom2dToIGES_Geom2dEntity& G2dE);

  //! Transfer a Point from Geom to IGES. If this
  //! Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESGeom_Point> Transfer2dPoint(
    const occ::handle<Geom2d_Point>& start);

  //! Transfer a CartesianPoint from Geom to IGES. If this
  //! Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESGeom_Point> Transfer2dPoint(
    const occ::handle<Geom2d_CartesianPoint>& start);
};

