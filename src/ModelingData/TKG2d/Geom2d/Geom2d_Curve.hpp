#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom2d_Geometry.hpp>
#include <Standard_Real.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
class gp_Trsf2d;
class gp_Pnt2d;
class gp_Vec2d;

class Geom2d_Curve : public Geom2d_Geometry
{

public:
  Standard_EXPORT virtual void Reverse() = 0;

  Standard_EXPORT virtual double ReversedParameter(const double U) const = 0;

  Standard_EXPORT virtual double TransformedParameter(const double U, const gp_Trsf2d& T) const;

  Standard_EXPORT virtual double ParametricTransformation(const gp_Trsf2d& T) const;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_Curve> Reversed() const;

  Standard_EXPORT virtual double FirstParameter() const = 0;

  Standard_EXPORT virtual double LastParameter() const = 0;

  Standard_EXPORT virtual bool IsClosed() const = 0;

  Standard_EXPORT virtual bool IsPeriodic() const = 0;

  Standard_EXPORT virtual double Period() const;

  Standard_EXPORT virtual GeomAbs_Shape Continuity() const = 0;

  Standard_EXPORT virtual bool IsCN(const int N) const = 0;

  Standard_EXPORT virtual void D0(const double U, gp_Pnt2d& P) const = 0;

  Standard_EXPORT virtual void D1(const double U, gp_Pnt2d& P, gp_Vec2d& V1) const = 0;

  Standard_EXPORT virtual void D2(const double U,
                                  gp_Pnt2d&    P,
                                  gp_Vec2d&    V1,
                                  gp_Vec2d&    V2) const = 0;

  Standard_EXPORT virtual void D3(const double U,
                                  gp_Pnt2d&    P,
                                  gp_Vec2d&    V1,
                                  gp_Vec2d&    V2,
                                  gp_Vec2d&    V3) const = 0;

  Standard_EXPORT virtual gp_Vec2d DN(const double U, const int N) const = 0;

  Standard_EXPORT gp_Pnt2d Value(const double U) const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom2d_Curve, Geom2d_Geometry)
};
