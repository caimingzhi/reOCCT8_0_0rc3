#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom_ElementarySurface.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
class gp_Ax3;
class gp_Torus;
class Geom_Curve;
class gp_Pnt;
class gp_Vec;
class gp_Trsf;
class Geom_Geometry;

class Geom_ToroidalSurface : public Geom_ElementarySurface
{

public:
  Standard_EXPORT Geom_ToroidalSurface(const gp_Ax3& A3,
                                       const double  MajorRadius,
                                       const double  MinorRadius);

  Standard_EXPORT Geom_ToroidalSurface(const gp_Torus& T);

  Standard_EXPORT void SetMajorRadius(const double MajorRadius);

  Standard_EXPORT void SetMinorRadius(const double MinorRadius);

  Standard_EXPORT void SetTorus(const gp_Torus& T);

  Standard_EXPORT gp_Torus Torus() const;

  Standard_EXPORT double UReversedParameter(const double U) const override;

  Standard_EXPORT double VReversedParameter(const double U) const override;

  Standard_EXPORT double Area() const;

  Standard_EXPORT void Bounds(double& U1, double& U2, double& V1, double& V2) const override;

  Standard_EXPORT void Coefficients(NCollection_Array1<double>& Coef) const;

  Standard_EXPORT double MajorRadius() const;

  Standard_EXPORT double MinorRadius() const;

  Standard_EXPORT double Volume() const;

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

  DEFINE_STANDARD_RTTIEXT(Geom_ToroidalSurface, Geom_ElementarySurface)

private:
  double majorRadius;
  double minorRadius;
};
