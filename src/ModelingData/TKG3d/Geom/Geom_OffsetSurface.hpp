#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <GeomAbs_Shape.hpp>
#include <Geom_BSplineSurface.hpp>
#include <Geom_Surface.hpp>
#include <Standard_Integer.hpp>

#include <memory>

class Geom_Curve;
class Geom_OsculatingSurface;
class gp_Pnt;
class gp_Vec;
class gp_Trsf;
class gp_GTrsf2d;
class Geom_Geometry;

class Geom_OffsetSurface : public Geom_Surface
{

public:
  Standard_EXPORT Geom_OffsetSurface(const occ::handle<Geom_Surface>& S,
                                     const double                     Offset,
                                     const bool                       isNotCheckC0 = false);

  Standard_EXPORT void SetBasisSurface(const occ::handle<Geom_Surface>& S,
                                       const bool                       isNotCheckC0 = false);

  Standard_EXPORT Geom_OffsetSurface(const Geom_OffsetSurface& theOther);

  Standard_EXPORT ~Geom_OffsetSurface() override;

  Standard_EXPORT void SetOffsetValue(const double D);

  inline double Offset() const { return offsetValue; }

  inline const occ::handle<Geom_Surface>& BasisSurface() const { return basisSurf; }

  Standard_EXPORT void UReverse() override;

  Standard_EXPORT double UReversedParameter(const double U) const override;

  Standard_EXPORT void VReverse() override;

  Standard_EXPORT double VReversedParameter(const double V) const override;

  Standard_EXPORT void Bounds(double& U1, double& U2, double& V1, double& V2) const override;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT bool IsCNu(const int N) const override;

  Standard_EXPORT bool IsCNv(const int N) const override;

  Standard_EXPORT bool IsUClosed() const override;

  Standard_EXPORT bool IsVClosed() const override;

  Standard_EXPORT bool IsUPeriodic() const override;

  Standard_EXPORT double UPeriod() const override;

  Standard_EXPORT bool IsVPeriodic() const override;

  Standard_EXPORT double VPeriod() const override;

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

  Standard_EXPORT void TransformParameters(double& U, double& V, const gp_Trsf& T) const override;

  Standard_EXPORT gp_GTrsf2d ParametricTransformation(const gp_Trsf& T) const override;

  Standard_EXPORT occ::handle<Geom_Geometry> Copy() const override;

  Standard_EXPORT occ::handle<Geom_Surface> Surface() const;

  Standard_EXPORT bool UOsculatingSurface(const double                      U,
                                          const double                      V,
                                          bool&                             IsOpposite,
                                          occ::handle<Geom_BSplineSurface>& UOsculSurf) const;

  Standard_EXPORT bool VOsculatingSurface(const double                      U,
                                          const double                      V,
                                          bool&                             IsOpposite,
                                          occ::handle<Geom_BSplineSurface>& VOsculSurf) const;

  inline GeomAbs_Shape GetBasisSurfContinuity() const { return myBasisSurfContinuity; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom_OffsetSurface, Geom_Surface)

private:
  occ::handle<Geom_Surface>               basisSurf;
  occ::handle<Geom_Surface>               equivSurf;
  double                                  offsetValue;
  std::unique_ptr<Geom_OsculatingSurface> myOscSurf;
  GeomAbs_Shape                           myBasisSurfContinuity;
};
