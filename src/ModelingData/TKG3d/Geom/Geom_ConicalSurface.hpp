#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom_ElementarySurface.hpp>
#include <Standard_Integer.hpp>
class gp_Ax3;
class gp_Cone;
class gp_Trsf;
class gp_GTrsf2d;
class gp_Pnt;
class Geom_Curve;
class gp_Vec;
class Geom_Geometry;

class Geom_ConicalSurface : public Geom_ElementarySurface
{

public:
  Standard_EXPORT Geom_ConicalSurface(const gp_Ax3& A3, const double Ang, const double Radius);

  Standard_EXPORT Geom_ConicalSurface(const gp_Cone& C);

  Standard_EXPORT void SetCone(const gp_Cone& C);

  Standard_EXPORT void SetRadius(const double R);

  Standard_EXPORT void SetSemiAngle(const double Ang);

  Standard_EXPORT gp_Cone Cone() const;

  Standard_EXPORT double UReversedParameter(const double U) const override;

  Standard_EXPORT double VReversedParameter(const double V) const override;

  Standard_EXPORT void VReverse() override;

  Standard_EXPORT void TransformParameters(double& U, double& V, const gp_Trsf& T) const override;

  Standard_EXPORT gp_GTrsf2d ParametricTransformation(const gp_Trsf& T) const override;

  Standard_EXPORT gp_Pnt Apex() const;

  Standard_EXPORT void Bounds(double& U1, double& U2, double& V1, double& V2) const override;

  Standard_EXPORT void Coefficients(double& A1,
                                    double& A2,
                                    double& A3,
                                    double& B1,
                                    double& B2,
                                    double& B3,
                                    double& C1,
                                    double& C2,
                                    double& C3,
                                    double& D) const;

  Standard_EXPORT double RefRadius() const;

  Standard_EXPORT double SemiAngle() const;

  Standard_EXPORT bool IsUClosed() const override;

  Standard_EXPORT bool IsVClosed() const override;

  Standard_EXPORT bool IsUPeriodic() const override;

  Standard_EXPORT bool IsVPeriodic() const override;

  Standard_EXPORT occ::handle<Geom_Curve> UIso(const double U) const override;

  Standard_EXPORT occ::handle<Geom_Curve> VIso(const double V) const override;

  Standard_EXPORT void D0(const double U, const double V, gp_Pnt& P) const override;

  Standard_EXPORT void D1(const double U,
                          const double V,
                          gp_Pnt&      P,
                          gp_Vec&      D1U,
                          gp_Vec&      D1V) const override;

  Standard_EXPORT void D2(const double U,
                          const double V,
                          gp_Pnt&      P,
                          gp_Vec&      D1U,
                          gp_Vec&      D1V,
                          gp_Vec&      D2U,
                          gp_Vec&      D2V,
                          gp_Vec&      D2UV) const override;

  Standard_EXPORT void D3(const double U,
                          const double V,
                          gp_Pnt&      P,
                          gp_Vec&      D1U,
                          gp_Vec&      D1V,
                          gp_Vec&      D2U,
                          gp_Vec&      D2V,
                          gp_Vec&      D2UV,
                          gp_Vec&      D3U,
                          gp_Vec&      D3V,
                          gp_Vec&      D3UUV,
                          gp_Vec&      D3UVV) const override;

  Standard_EXPORT gp_Vec DN(const double U,
                            const double V,
                            const int    Nu,
                            const int    Nv) const override;

  Standard_EXPORT void Transform(const gp_Trsf& T) override;

  Standard_EXPORT occ::handle<Geom_Geometry> Copy() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom_ConicalSurface, Geom_ElementarySurface)

private:
  double radius;
  double semiAngle;
};
