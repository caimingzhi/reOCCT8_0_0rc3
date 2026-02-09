#pragma once

#include <Standard.hpp>

#include <gp_Pnt.hpp>
#include <Geom_Point.hpp>
#include <Standard_Real.hpp>
class gp_Trsf;
class Geom_Geometry;

class Geom_CartesianPoint : public Geom_Point
{

public:
  Standard_EXPORT Geom_CartesianPoint(const gp_Pnt& P);

  Standard_EXPORT Geom_CartesianPoint(const double X, const double Y, const double Z);

  Standard_EXPORT void SetCoord(const double X, const double Y, const double Z);

  Standard_EXPORT void SetPnt(const gp_Pnt& P);

  Standard_EXPORT void SetX(const double X);

  Standard_EXPORT void SetY(const double Y);

  Standard_EXPORT void SetZ(const double Z);

  Standard_EXPORT void Coord(double& X, double& Y, double& Z) const override;

  Standard_EXPORT gp_Pnt Pnt() const override;

  Standard_EXPORT double X() const override;

  Standard_EXPORT double Y() const override;

  Standard_EXPORT double Z() const override;

  Standard_EXPORT void Transform(const gp_Trsf& T) override;

  Standard_EXPORT occ::handle<Geom_Geometry> Copy() const override;

  DEFINE_STANDARD_RTTIEXT(Geom_CartesianPoint, Geom_Point)

private:
  gp_Pnt gpPnt;
};
