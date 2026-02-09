#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom_Surface.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

enum ShapeExtend_Parametrisation
{
  ShapeExtend_Natural,
  ShapeExtend_Uniform,
  ShapeExtend_Unitary
};

#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
class gp_Pnt2d;
class gp_Trsf2d;
class gp_Trsf;
class Geom_Geometry;
class Geom_Curve;
class gp_Pnt;
class gp_Vec;

class ShapeExtend_CompositeSurface : public Geom_Surface
{

public:
  Standard_EXPORT ShapeExtend_CompositeSurface();

  Standard_EXPORT ShapeExtend_CompositeSurface(
    const occ::handle<NCollection_HArray2<occ::handle<Geom_Surface>>>& GridSurf,
    const ShapeExtend_Parametrisation                                  param = ShapeExtend_Natural);

  Standard_EXPORT ShapeExtend_CompositeSurface(
    const occ::handle<NCollection_HArray2<occ::handle<Geom_Surface>>>& GridSurf,
    const NCollection_Array1<double>&                                  UJoints,
    const NCollection_Array1<double>&                                  VJoints);

  Standard_EXPORT bool Init(
    const occ::handle<NCollection_HArray2<occ::handle<Geom_Surface>>>& GridSurf,
    const ShapeExtend_Parametrisation                                  param = ShapeExtend_Natural);

  Standard_EXPORT bool Init(
    const occ::handle<NCollection_HArray2<occ::handle<Geom_Surface>>>& GridSurf,
    const NCollection_Array1<double>&                                  UJoints,
    const NCollection_Array1<double>&                                  VJoints);

  Standard_EXPORT int NbUPatches() const;

  Standard_EXPORT int NbVPatches() const;

  Standard_EXPORT const occ::handle<Geom_Surface>& Patch(const int i, const int j) const;

  Standard_EXPORT const occ::handle<NCollection_HArray2<occ::handle<Geom_Surface>>>& Patches()
    const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> UJointValues() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> VJointValues() const;

  Standard_EXPORT double UJointValue(const int i) const;

  Standard_EXPORT double VJointValue(const int j) const;

  Standard_EXPORT bool SetUJointValues(const NCollection_Array1<double>& UJoints);

  Standard_EXPORT bool SetVJointValues(const NCollection_Array1<double>& VJoints);

  Standard_EXPORT void SetUFirstValue(const double UFirst);

  Standard_EXPORT void SetVFirstValue(const double VFirst);

  Standard_EXPORT int LocateUParameter(const double U) const;

  Standard_EXPORT int LocateVParameter(const double V) const;

  Standard_EXPORT void LocateUVPoint(const gp_Pnt2d& pnt, int& i, int& j) const;

  Standard_EXPORT const occ::handle<Geom_Surface>& Patch(const double U, const double V) const;

  Standard_EXPORT const occ::handle<Geom_Surface>& Patch(const gp_Pnt2d& pnt) const;

  Standard_EXPORT double ULocalToGlobal(const int i, const int j, const double u) const;

  Standard_EXPORT double VLocalToGlobal(const int i, const int j, const double v) const;

  Standard_EXPORT gp_Pnt2d LocalToGlobal(const int i, const int j, const gp_Pnt2d& uv) const;

  Standard_EXPORT double UGlobalToLocal(const int i, const int j, const double U) const;

  Standard_EXPORT double VGlobalToLocal(const int i, const int j, const double V) const;

  Standard_EXPORT gp_Pnt2d GlobalToLocal(const int i, const int j, const gp_Pnt2d& UV) const;

  Standard_EXPORT bool GlobalToLocalTransformation(const int  i,
                                                   const int  j,
                                                   double&    uFact,
                                                   gp_Trsf2d& Trsf) const;

  Standard_EXPORT void Transform(const gp_Trsf& T) override;

  Standard_EXPORT occ::handle<Geom_Geometry> Copy() const override;

  Standard_EXPORT void UReverse() override;

  Standard_EXPORT double UReversedParameter(const double U) const override;

  Standard_EXPORT void VReverse() override;

  Standard_EXPORT double VReversedParameter(const double V) const override;

  Standard_EXPORT void Bounds(double& U1, double& U2, double& V1, double& V2) const override;

  Standard_EXPORT bool IsUClosed() const override;

  Standard_EXPORT bool IsVClosed() const override;

  Standard_EXPORT bool IsUPeriodic() const override;

  Standard_EXPORT bool IsVPeriodic() const override;

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

  Standard_EXPORT gp_Pnt Value(const gp_Pnt2d& pnt) const;

  Standard_EXPORT void ComputeJointValues(
    const ShapeExtend_Parametrisation param = ShapeExtend_Natural);

  Standard_EXPORT bool CheckConnectivity(const double prec);

  DEFINE_STANDARD_RTTIEXT(ShapeExtend_CompositeSurface, Geom_Surface)

private:
  occ::handle<NCollection_HArray2<occ::handle<Geom_Surface>>> myPatches;
  occ::handle<NCollection_HArray1<double>>                    myUJointValues;
  occ::handle<NCollection_HArray1<double>>                    myVJointValues;
  bool                                                        myUClosed;
  bool                                                        myVClosed;
};
