#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom2d_Conic.hpp>
#include <Standard_Integer.hpp>
class gp_Parab2d;
class gp_Ax2d;
class gp_Ax22d;
class gp_Pnt2d;
class gp_Vec2d;
class gp_Trsf2d;
class Geom2d_Geometry;

class Geom2d_Parabola : public Geom2d_Conic
{

public:
  Standard_EXPORT Geom2d_Parabola(const gp_Parab2d& Prb);

  Standard_EXPORT Geom2d_Parabola(const gp_Ax2d& MirrorAxis,
                                  const double   Focal,
                                  const bool     Sense = true);

  Standard_EXPORT Geom2d_Parabola(const gp_Ax22d& Axis, const double Focal);

  Standard_EXPORT Geom2d_Parabola(const gp_Ax2d& D, const gp_Pnt2d& F);

  Standard_EXPORT void SetFocal(const double Focal);

  Standard_EXPORT void SetParab2d(const gp_Parab2d& Prb);

  Standard_EXPORT gp_Parab2d Parab2d() const;

  Standard_EXPORT double ReversedParameter(const double U) const override;

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT gp_Ax2d Directrix() const;

  Standard_EXPORT double Eccentricity() const override;

  Standard_EXPORT gp_Pnt2d Focus() const;

  Standard_EXPORT double Focal() const;

  Standard_EXPORT double Parameter() const;

  Standard_EXPORT void D0(const double U, gp_Pnt2d& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt2d& P, gp_Vec2d& V1) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2) const override;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt2d&    P,
                          gp_Vec2d&    V1,
                          gp_Vec2d&    V2,
                          gp_Vec2d&    V3) const override;

  Standard_EXPORT gp_Vec2d DN(const double U, const int N) const override;

  Standard_EXPORT void Transform(const gp_Trsf2d& T) override;

  Standard_EXPORT double TransformedParameter(const double U, const gp_Trsf2d& T) const override;

  Standard_EXPORT double ParametricTransformation(const gp_Trsf2d& T) const override;

  Standard_EXPORT occ::handle<Geom2d_Geometry> Copy() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom2d_Parabola, Geom2d_Conic)

private:
  double focalLength;
};
