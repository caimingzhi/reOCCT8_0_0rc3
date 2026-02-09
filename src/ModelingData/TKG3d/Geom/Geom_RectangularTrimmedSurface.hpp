#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom_BoundedSurface.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
class Geom_Surface;
class Geom_Curve;
class gp_Pnt;
class gp_Vec;
class gp_Trsf;
class gp_GTrsf2d;
class Geom_Geometry;

class Geom_RectangularTrimmedSurface : public Geom_BoundedSurface
{

public:
  Standard_EXPORT Geom_RectangularTrimmedSurface(const occ::handle<Geom_Surface>& S,
                                                 const double                     U1,
                                                 const double                     U2,
                                                 const double                     V1,
                                                 const double                     V2,
                                                 const bool                       USense = true,
                                                 const bool                       VSense = true);

  Standard_EXPORT Geom_RectangularTrimmedSurface(const occ::handle<Geom_Surface>& S,
                                                 const double                     Param1,
                                                 const double                     Param2,
                                                 const bool                       UTrim,
                                                 const bool                       Sense = true);

  Standard_EXPORT void SetTrim(const double U1,
                               const double U2,
                               const double V1,
                               const double V2,
                               const bool   USense = true,
                               const bool   VSense = true);

  Standard_EXPORT void SetTrim(const double Param1,
                               const double Param2,
                               const bool   UTrim,
                               const bool   Sense = true);

  Standard_EXPORT occ::handle<Geom_Surface> BasisSurface() const;

  Standard_EXPORT void UReverse() override;

  Standard_EXPORT double UReversedParameter(const double U) const override;

  Standard_EXPORT void VReverse() override;

  Standard_EXPORT double VReversedParameter(const double V) const override;

  Standard_EXPORT void Bounds(double& U1, double& U2, double& V1, double& V2) const override;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT bool IsUClosed() const override;

  Standard_EXPORT bool IsVClosed() const override;

  Standard_EXPORT bool IsCNu(const int N) const override;

  Standard_EXPORT bool IsCNv(const int N) const override;

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

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom_RectangularTrimmedSurface, Geom_BoundedSurface)

private:
  Standard_EXPORT void SetTrim(const double U1,
                               const double U2,
                               const double V1,
                               const double V2,
                               const bool   UTrim,
                               const bool   VTrim,
                               const bool   USense,
                               const bool   VSense);

  occ::handle<Geom_Surface> basisSurf;
  double                    utrim1;
  double                    vtrim1;
  double                    utrim2;
  double                    vtrim2;
  bool                      isutrimmed;
  bool                      isvtrimmed;
};
