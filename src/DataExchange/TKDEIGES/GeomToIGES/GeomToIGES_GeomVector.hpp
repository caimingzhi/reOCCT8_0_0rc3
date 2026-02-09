#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToIGES_GeomEntity.hpp>
class IGESGeom_Direction;
class Geom_Vector;
class Geom_VectorWithMagnitude;
class Geom_Direction;

class GeomToIGES_GeomVector : public GeomToIGES_GeomEntity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToIGES_GeomVector();

  Standard_EXPORT GeomToIGES_GeomVector(const GeomToIGES_GeomEntity& GE);

  Standard_EXPORT occ::handle<IGESGeom_Direction> TransferVector(
    const occ::handle<Geom_Vector>& start);

  Standard_EXPORT occ::handle<IGESGeom_Direction> TransferVector(
    const occ::handle<Geom_VectorWithMagnitude>& start);

  Standard_EXPORT occ::handle<IGESGeom_Direction> TransferVector(
    const occ::handle<Geom_Direction>& start);
};
