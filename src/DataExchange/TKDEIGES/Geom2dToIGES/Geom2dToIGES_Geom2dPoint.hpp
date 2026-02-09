#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom2dToIGES_Geom2dEntity.hpp>
class IGESGeom_Point;
class Geom2d_Point;
class Geom2d_CartesianPoint;

class Geom2dToIGES_Geom2dPoint : public Geom2dToIGES_Geom2dEntity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dToIGES_Geom2dPoint();

  Standard_EXPORT Geom2dToIGES_Geom2dPoint(const Geom2dToIGES_Geom2dEntity& G2dE);

  Standard_EXPORT occ::handle<IGESGeom_Point> Transfer2dPoint(
    const occ::handle<Geom2d_Point>& start);

  Standard_EXPORT occ::handle<IGESGeom_Point> Transfer2dPoint(
    const occ::handle<Geom2d_CartesianPoint>& start);
};
