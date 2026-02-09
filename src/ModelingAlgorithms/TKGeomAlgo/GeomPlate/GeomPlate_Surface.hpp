#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Plate_Plate.hpp>
#include <Geom_Surface.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <gp_XY.hpp>
#include <NCollection_Sequence.hpp>
class gp_Trsf;
class gp_GTrsf2d;
class Geom_Curve;
class gp_Pnt;
class gp_Vec;
class Geom_Geometry;

class GeomPlate_Surface : public Geom_Surface
{

public:
  Standard_EXPORT GeomPlate_Surface(const occ::handle<Geom_Surface>& Surfinit,
                                    const Plate_Plate&               Surfinter);

  Standard_EXPORT void UReverse() override;

  Standard_EXPORT double UReversedParameter(const double U) const override;

  Standard_EXPORT void VReverse() override;

  Standard_EXPORT double VReversedParameter(const double V) const override;

  Standard_EXPORT void TransformParameters(double& U, double& V, const gp_Trsf& T) const override;

  Standard_EXPORT gp_GTrsf2d ParametricTransformation(const gp_Trsf& T) const override;

  Standard_EXPORT void Bounds(double& U1, double& U2, double& V1, double& V2) const override;

  Standard_EXPORT bool IsUClosed() const override;

  Standard_EXPORT bool IsVClosed() const override;

  Standard_EXPORT bool IsUPeriodic() const override;

  Standard_EXPORT double UPeriod() const override;

  Standard_EXPORT bool IsVPeriodic() const override;

  Standard_EXPORT double VPeriod() const override;

  Standard_EXPORT occ::handle<Geom_Curve> UIso(const double U) const override;

  Standard_EXPORT occ::handle<Geom_Curve> VIso(const double V) const override;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT bool IsCNu(const int N) const override;

  Standard_EXPORT bool IsCNv(const int N) const override;

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

  Standard_EXPORT occ::handle<Geom_Geometry> Copy() const override;

  Standard_EXPORT void Transform(const gp_Trsf& T) override;

  Standard_EXPORT occ::handle<Geom_Surface> CallSurfinit() const;

  Standard_EXPORT void SetBounds(const double Umin,
                                 const double Umax,
                                 const double Vmin,
                                 const double Vmax);

  Standard_EXPORT void RealBounds(double& U1, double& U2, double& V1, double& V2) const;

  Standard_EXPORT void Constraints(NCollection_Sequence<gp_XY>& Seq) const;

  DEFINE_STANDARD_RTTIEXT(GeomPlate_Surface, Geom_Surface)

private:
  Plate_Plate               mySurfinter;
  occ::handle<Geom_Surface> mySurfinit;
  double                    myUmin;
  double                    myUmax;
  double                    myVmin;
  double                    myVmax;
};
