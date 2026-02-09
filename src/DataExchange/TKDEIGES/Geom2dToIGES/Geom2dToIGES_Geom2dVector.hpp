#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom2dToIGES_Geom2dEntity.hpp>
class IGESGeom_Direction;
class Geom2d_Vector;
class Geom2d_VectorWithMagnitude;
class Geom2d_Direction;

class Geom2dToIGES_Geom2dVector : public Geom2dToIGES_Geom2dEntity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dToIGES_Geom2dVector();

  Standard_EXPORT Geom2dToIGES_Geom2dVector(const Geom2dToIGES_Geom2dEntity& G2dE);

  Standard_EXPORT occ::handle<IGESGeom_Direction> Transfer2dVector(
    const occ::handle<Geom2d_Vector>& start);

  Standard_EXPORT occ::handle<IGESGeom_Direction> Transfer2dVector(
    const occ::handle<Geom2d_VectorWithMagnitude>& start);

  Standard_EXPORT occ::handle<IGESGeom_Direction> Transfer2dVector(
    const occ::handle<Geom2d_Direction>& start);
};
