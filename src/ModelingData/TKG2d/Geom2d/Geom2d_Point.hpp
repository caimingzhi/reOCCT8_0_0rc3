#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom2d_Geometry.hpp>
#include <Standard_Real.hpp>
class gp_Pnt2d;

class Geom2d_Point : public Geom2d_Geometry
{

public:
  Standard_EXPORT virtual void Coord(double& X, double& Y) const = 0;

  Standard_EXPORT virtual gp_Pnt2d Pnt2d() const = 0;

  Standard_EXPORT virtual double X() const = 0;

  Standard_EXPORT virtual double Y() const = 0;

  Standard_EXPORT double Distance(const occ::handle<Geom2d_Point>& Other) const;

  Standard_EXPORT double SquareDistance(const occ::handle<Geom2d_Point>& Other) const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom2d_Point, Geom2d_Geometry)
};
