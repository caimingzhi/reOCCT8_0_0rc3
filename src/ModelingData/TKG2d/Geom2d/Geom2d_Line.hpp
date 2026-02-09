#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Ax2d.hpp>
#include <Geom2d_Curve.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
class gp_Lin2d;
class gp_Pnt2d;
class gp_Dir2d;
class gp_Vec2d;
class gp_Trsf2d;
class Geom2d_Geometry;

class Geom2d_Line : public Geom2d_Curve
{

public:
  Standard_EXPORT Geom2d_Line(const gp_Ax2d& A);

  Standard_EXPORT Geom2d_Line(const gp_Lin2d& L);

  Standard_EXPORT Geom2d_Line(const gp_Pnt2d& P, const gp_Dir2d& V);

  Standard_EXPORT void SetLin2d(const gp_Lin2d& L);

  Standard_EXPORT void SetDirection(const gp_Dir2d& V);

  Standard_EXPORT const gp_Dir2d& Direction() const;

  Standard_EXPORT void SetLocation(const gp_Pnt2d& P);

  Standard_EXPORT const gp_Pnt2d& Location() const;

  Standard_EXPORT void SetPosition(const gp_Ax2d& A);

  Standard_EXPORT const gp_Ax2d& Position() const;

  Standard_EXPORT gp_Lin2d Lin2d() const;

  Standard_EXPORT void Reverse() override;

  Standard_EXPORT double ReversedParameter(const double U) const override;

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT double Distance(const gp_Pnt2d& P) const;

  Standard_EXPORT bool IsCN(const int N) const override;

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

  DEFINE_STANDARD_RTTIEXT(Geom2d_Line, Geom2d_Curve)

private:
  gp_Ax2d pos;
};
