#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom_Geometry.hpp>
#include <Standard_Real.hpp>
class gp_Pnt;

class Geom_Point : public Geom_Geometry
{

public:
  Standard_EXPORT virtual void Coord(double& X, double& Y, double& Z) const = 0;

  Standard_EXPORT virtual gp_Pnt Pnt() const = 0;

  Standard_EXPORT virtual double X() const = 0;

  Standard_EXPORT virtual double Y() const = 0;

  Standard_EXPORT virtual double Z() const = 0;

  Standard_EXPORT double Distance(const occ::handle<Geom_Point>& Other) const;

  Standard_EXPORT double SquareDistance(const occ::handle<Geom_Point>& Other) const;

  DEFINE_STANDARD_RTTIEXT(Geom_Point, Geom_Geometry)
};
