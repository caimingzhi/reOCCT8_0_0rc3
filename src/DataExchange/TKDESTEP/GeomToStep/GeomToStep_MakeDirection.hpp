#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>
class StepGeom_Direction;
class gp_Dir;
class gp_Dir2d;
class Geom_Direction;
class Geom2d_Direction;

//! This class implements the mapping between classes
//! Direction from Geom, Geom2d and Dir, Dir2d from gp, and the
//! class Direction from StepGeom which describes a direction
//! from Prostep.
class GeomToStep_MakeDirection : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeDirection(const gp_Dir& D);

  Standard_EXPORT GeomToStep_MakeDirection(const gp_Dir2d& D);

  Standard_EXPORT GeomToStep_MakeDirection(const occ::handle<Geom_Direction>& D);

  Standard_EXPORT GeomToStep_MakeDirection(const occ::handle<Geom2d_Direction>& D);

  Standard_EXPORT const occ::handle<StepGeom_Direction>& Value() const;

private:
  occ::handle<StepGeom_Direction> theDirection;
};
