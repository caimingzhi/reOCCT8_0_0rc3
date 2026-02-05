#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToIGES_GeomEntity.hpp>
class IGESGeom_Direction;
class Geom_Vector;
class Geom_VectorWithMagnitude;
class Geom_Direction;

//! This class implements the transfer of the Vector from Geom
//! to IGES. These can be:
//! . Vector
//! * Direction
//! * VectorWithMagnitude
class GeomToIGES_GeomVector : public GeomToIGES_GeomEntity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToIGES_GeomVector();

  //! Creates a tool GeomVector ready to run and sets its
  //! fields as GE's.
  Standard_EXPORT GeomToIGES_GeomVector(const GeomToIGES_GeomEntity& GE);

  //! Transfer a GeometryEntity which answer True to the
  //! member : BRepToIGES::IsGeomVector(Geometry). If this
  //! Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESGeom_Direction> TransferVector(
    const occ::handle<Geom_Vector>& start);

  Standard_EXPORT occ::handle<IGESGeom_Direction> TransferVector(
    const occ::handle<Geom_VectorWithMagnitude>& start);

  Standard_EXPORT occ::handle<IGESGeom_Direction> TransferVector(
    const occ::handle<Geom_Direction>& start);
};
