#pragma once

#include <Standard.hpp>

#include <gp_Trsf2d.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Real.hpp>
#include <gp_TrsfForm.hpp>
#include <Standard_Integer.hpp>
class gp_Pnt2d;
class gp_Ax2d;
class gp_Vec2d;

class Geom2d_Transformation : public Standard_Transient
{

public:
  Standard_EXPORT Geom2d_Transformation();

  Standard_EXPORT Geom2d_Transformation(const gp_Trsf2d& T);

  Standard_EXPORT void SetMirror(const gp_Pnt2d& P);

  Standard_EXPORT void SetMirror(const gp_Ax2d& A);

  Standard_EXPORT void SetRotation(const gp_Pnt2d& P, const double Ang);

  Standard_EXPORT void SetScale(const gp_Pnt2d& P, const double S);

  Standard_EXPORT void SetTransformation(const gp_Ax2d& FromSystem1, const gp_Ax2d& ToSystem2);

  Standard_EXPORT void SetTransformation(const gp_Ax2d& ToSystem);

  Standard_EXPORT void SetTranslation(const gp_Vec2d& V);

  Standard_EXPORT void SetTranslation(const gp_Pnt2d& P1, const gp_Pnt2d& P2);

  Standard_EXPORT void SetTrsf2d(const gp_Trsf2d& T);

  Standard_EXPORT bool IsNegative() const;

  Standard_EXPORT gp_TrsfForm Form() const;

  Standard_EXPORT double ScaleFactor() const;

  Standard_EXPORT gp_Trsf2d Trsf2d() const;

  Standard_EXPORT double Value(const int Row, const int Col) const;

  Standard_EXPORT void Invert();

  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_Transformation> Inverted() const;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_Transformation> Multiplied(
    const occ::handle<Geom2d_Transformation>& Other) const;

  [[nodiscard]] occ::handle<Geom2d_Transformation> operator*(
    const occ::handle<Geom2d_Transformation>& Other) const
  {
    return Multiplied(Other);
  }

  Standard_EXPORT void Multiply(const occ::handle<Geom2d_Transformation>& Other);

  void operator*=(const occ::handle<Geom2d_Transformation>& Other) { Multiply(Other); }

  Standard_EXPORT void Power(const int N);

  Standard_EXPORT occ::handle<Geom2d_Transformation> Powered(const int N) const;

  Standard_EXPORT void PreMultiply(const occ::handle<Geom2d_Transformation>& Other);

  Standard_EXPORT void Transforms(double& X, double& Y) const;

  Standard_EXPORT occ::handle<Geom2d_Transformation> Copy() const;

  DEFINE_STANDARD_RTTIEXT(Geom2d_Transformation, Standard_Transient)

private:
  gp_Trsf2d gpTrsf2d;
};
