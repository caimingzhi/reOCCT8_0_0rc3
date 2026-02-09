#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToIGES_GeomEntity.hpp>
class IGESGeom_Point;
class Geom_Point;
class Geom_CartesianPoint;

class GeomToIGES_GeomPoint : public GeomToIGES_GeomEntity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToIGES_GeomPoint();

  Standard_EXPORT GeomToIGES_GeomPoint(const GeomToIGES_GeomEntity& GE);

  Standard_EXPORT occ::handle<IGESGeom_Point> TransferPoint(const occ::handle<Geom_Point>& start);

  Standard_EXPORT occ::handle<IGESGeom_Point> TransferPoint(
    const occ::handle<Geom_CartesianPoint>& start);
};
