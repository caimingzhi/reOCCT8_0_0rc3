#pragma once

#include <Geom_Curve.hpp>

class gp_Trsf;
class gp_GTrsf2d;
class gp_Pnt;
class gp_Vec;

class Geom_Surface : public Geom_Geometry
{

public:
  Standard_EXPORT virtual void UReverse() = 0;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom_Surface> UReversed() const;

  Standard_EXPORT virtual double UReversedParameter(const double U) const = 0;

  Standard_EXPORT virtual void VReverse() = 0;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom_Surface> VReversed() const;

  Standard_EXPORT virtual double VReversedParameter(const double V) const = 0;

  Standard_EXPORT virtual void TransformParameters(double& U, double& V, const gp_Trsf& T) const;

  Standard_EXPORT virtual gp_GTrsf2d ParametricTransformation(const gp_Trsf& T) const;

  Standard_EXPORT virtual void Bounds(double& U1, double& U2, double& V1, double& V2) const = 0;

  Standard_EXPORT virtual bool IsUClosed() const = 0;

  Standard_EXPORT virtual bool IsVClosed() const = 0;

  Standard_EXPORT virtual bool IsUPeriodic() const = 0;

  Standard_EXPORT virtual double UPeriod() const;

  Standard_EXPORT virtual bool IsVPeriodic() const = 0;

  Standard_EXPORT virtual double VPeriod() const;

  Standard_EXPORT virtual occ::handle<Geom_Curve> UIso(const double U) const = 0;

  Standard_EXPORT virtual occ::handle<Geom_Curve> VIso(const double V) const = 0;

  Standard_EXPORT virtual GeomAbs_Shape Continuity() const = 0;

  Standard_EXPORT virtual bool IsCNu(const int N) const = 0;

  Standard_EXPORT virtual bool IsCNv(const int N) const = 0;

  Standard_EXPORT virtual void D0(const double U, const double V, gp_Pnt& P) const = 0;

  Standard_EXPORT virtual void D1(const double U,
                                  const double V,
                                  gp_Pnt&      P,
                                  gp_Vec&      D1U,
                                  gp_Vec&      D1V) const = 0;

  Standard_EXPORT virtual void D2(const double U,
                                  const double V,
                                  gp_Pnt&      P,
                                  gp_Vec&      D1U,
                                  gp_Vec&      D1V,
                                  gp_Vec&      D2U,
                                  gp_Vec&      D2V,
                                  gp_Vec&      D2UV) const = 0;

  Standard_EXPORT virtual void D3(const double U,
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
                                  gp_Vec&      D3UVV) const = 0;

  Standard_EXPORT virtual gp_Vec DN(const double U,
                                    const double V,
                                    const int    Nu,
                                    const int    Nv) const = 0;

  Standard_EXPORT gp_Pnt Value(const double U, const double V) const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom_Surface, Geom_Geometry)
};
