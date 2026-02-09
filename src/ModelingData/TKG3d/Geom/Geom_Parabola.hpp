#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom_Conic.hpp>
#include <Standard_Integer.hpp>
class gp_Parab;
class gp_Ax2;
class gp_Ax1;
class gp_Pnt;
class gp_Vec;
class gp_Trsf;
class Geom_Geometry;

class Geom_Parabola : public Geom_Conic
{

public:
  Standard_EXPORT Geom_Parabola(const gp_Parab& Prb);

  Standard_EXPORT Geom_Parabola(const gp_Ax2& A2, const double Focal);

  Standard_EXPORT Geom_Parabola(const gp_Ax1& D, const gp_Pnt& F);

  Standard_EXPORT void SetFocal(const double Focal);

  Standard_EXPORT void SetParab(const gp_Parab& Prb);

  Standard_EXPORT gp_Parab Parab() const;

  Standard_EXPORT double ReversedParameter(const double U) const override;

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT gp_Ax1 Directrix() const;

  Standard_EXPORT double Eccentricity() const override;

  Standard_EXPORT gp_Pnt Focus() const;

  Standard_EXPORT double Focal() const;

  Standard_EXPORT double Parameter() const;

  Standard_EXPORT void D0(const double U, gp_Pnt& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt& P, gp_Vec& V1) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const override;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt&      P,
                          gp_Vec&      V1,
                          gp_Vec&      V2,
                          gp_Vec&      V3) const override;

  Standard_EXPORT gp_Vec DN(const double U, const int N) const override;

  Standard_EXPORT void Transform(const gp_Trsf& T) override;

  Standard_EXPORT double TransformedParameter(const double U, const gp_Trsf& T) const override;

  Standard_EXPORT double ParametricTransformation(const gp_Trsf& T) const override;

  Standard_EXPORT occ::handle<Geom_Geometry> Copy() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom_Parabola, Geom_Conic)

private:
  double focalLength;
};
