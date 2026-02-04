#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToIGES_GeomEntity.hpp>
class IGESGeom_Point;
class Geom_Point;
class Geom_CartesianPoint;

//! This class implements the transfer of the Point Entity from Geom
//! to IGES. These are:
//! . Point
//! * CartesianPoint
class GeomToIGES_GeomPoint : public GeomToIGES_GeomEntity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToIGES_GeomPoint();

  //! Creates a tool GeomPoint ready to run and sets its
  //! fields as GE's.
  Standard_EXPORT GeomToIGES_GeomPoint(const GeomToIGES_GeomEntity& GE);

  //! Transfer a Point from Geom to IGES. If this
  //! Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESGeom_Point> TransferPoint(const occ::handle<Geom_Point>& start);

  //! Transfer a CartesianPoint from Geom to IGES. If this
  //! Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESGeom_Point> TransferPoint(
    const occ::handle<Geom_CartesianPoint>& start);
};

