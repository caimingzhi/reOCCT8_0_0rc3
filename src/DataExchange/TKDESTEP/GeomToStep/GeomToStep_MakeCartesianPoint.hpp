#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>
class StepGeom_CartesianPoint;
class gp_Pnt;
class gp_Pnt2d;
class Geom_CartesianPoint;
class Geom2d_CartesianPoint;
class StepData_StepModel;

//! This class implements the mapping between classes
//! CartesianPoint from Geom and Pnt from gp, and the class
//! CartesianPoint from StepGeom which describes a point from
//! Prostep.
class GeomToStep_MakeCartesianPoint : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeCartesianPoint(const gp_Pnt& P, const double aFactor);

  Standard_EXPORT GeomToStep_MakeCartesianPoint(const gp_Pnt2d& P, const double aFactor);

  Standard_EXPORT GeomToStep_MakeCartesianPoint(const occ::handle<Geom_CartesianPoint>& P,
                                                const double                            aFactor);

  Standard_EXPORT GeomToStep_MakeCartesianPoint(const occ::handle<Geom2d_CartesianPoint>& P);

  Standard_EXPORT const occ::handle<StepGeom_CartesianPoint>& Value() const;

private:
  occ::handle<StepGeom_CartesianPoint> theCartesianPoint;
};
