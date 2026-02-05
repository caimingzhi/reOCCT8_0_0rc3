#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom2dToIGES_Geom2dEntity.hpp>
class IGESGeom_Direction;
class Geom2d_Vector;
class Geom2d_VectorWithMagnitude;
class Geom2d_Direction;

//! This class implements the transfer of the Vector from Geom2d
//! to IGES. These can be:
//! . Vector
//! * Direction
//! * VectorWithMagnitude
class Geom2dToIGES_Geom2dVector : public Geom2dToIGES_Geom2dEntity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dToIGES_Geom2dVector();

  //! Creates a tool Geom2dVector ready to run and sets its
  //! fields as G2dE's.
  Standard_EXPORT Geom2dToIGES_Geom2dVector(const Geom2dToIGES_Geom2dEntity& G2dE);

  //! Transfer a GeometryEntity which answer True to the
  //! member : BRepToIGES::IsGeomVector(Geometry). If this
  //! Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESGeom_Direction> Transfer2dVector(
    const occ::handle<Geom2d_Vector>& start);

  Standard_EXPORT occ::handle<IGESGeom_Direction> Transfer2dVector(
    const occ::handle<Geom2d_VectorWithMagnitude>& start);

  Standard_EXPORT occ::handle<IGESGeom_Direction> Transfer2dVector(
    const occ::handle<Geom2d_Direction>& start);
};
