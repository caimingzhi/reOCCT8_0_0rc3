#pragma once

#include <GeomAdaptor_Surface.hpp>

class gp_Pln;
class gp_Cylinder;
class gp_Cone;
class gp_Sphere;
class gp_Torus;
class Geom_BezierSurface;
class Geom_BSplineSurface;

class GeomAdaptor_SurfaceOfRevolution : public GeomAdaptor_Surface
{
  DEFINE_STANDARD_RTTIEXT(GeomAdaptor_SurfaceOfRevolution, GeomAdaptor_Surface)
public:
  Standard_EXPORT GeomAdaptor_SurfaceOfRevolution();

  Standard_EXPORT GeomAdaptor_SurfaceOfRevolution(const occ::handle<Adaptor3d_Curve>& C);

  Standard_EXPORT GeomAdaptor_SurfaceOfRevolution(const occ::handle<Adaptor3d_Curve>& C,
                                                  const gp_Ax1&                       V);

  Standard_EXPORT occ::handle<Adaptor3d_Surface> ShallowCopy() const override;

  Standard_EXPORT void Load(const occ::handle<Adaptor3d_Curve>& C);

  Standard_EXPORT void Load(const gp_Ax1& V);

  Standard_EXPORT gp_Ax1 AxeOfRevolution() const override;

  Standard_EXPORT double FirstUParameter() const override;

  Standard_EXPORT double LastUParameter() const override;

  Standard_EXPORT double FirstVParameter() const override;

  Standard_EXPORT double LastVParameter() const override;

  Standard_EXPORT GeomAbs_Shape UContinuity() const override;

  Standard_EXPORT GeomAbs_Shape VContinuity() const override;

  Standard_EXPORT int NbUIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT int NbVIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void UIntervals(NCollection_Array1<double>& T,
                                  const GeomAbs_Shape         S) const override;

  Standard_EXPORT void VIntervals(NCollection_Array1<double>& T,
                                  const GeomAbs_Shape         S) const override;

  Standard_EXPORT occ::handle<Adaptor3d_Surface> UTrim(const double First,
                                                       const double Last,
                                                       const double Tol) const override;

  Standard_EXPORT occ::handle<Adaptor3d_Surface> VTrim(const double First,
                                                       const double Last,
                                                       const double Tol) const override;

  Standard_EXPORT bool IsUClosed() const override;

  Standard_EXPORT bool IsVClosed() const override;

  Standard_EXPORT bool IsUPeriodic() const override;

  Standard_EXPORT double UPeriod() const override;

  Standard_EXPORT bool IsVPeriodic() const override;

  Standard_EXPORT double VPeriod() const override;

  Standard_EXPORT double UResolution(const double R3d) const override;

  Standard_EXPORT double VResolution(const double R3d) const override;

  Standard_EXPORT GeomAbs_SurfaceType GetType() const override;

  Standard_EXPORT gp_Pln Plane() const override;

  Standard_EXPORT gp_Cylinder Cylinder() const override;

  Standard_EXPORT gp_Cone Cone() const override;

  Standard_EXPORT gp_Sphere Sphere() const override;

  Standard_EXPORT gp_Torus Torus() const override;

  Standard_EXPORT int VDegree() const override;

  Standard_EXPORT int NbVPoles() const override;

  Standard_EXPORT int NbVKnots() const override;

  Standard_EXPORT bool IsURational() const override;

  Standard_EXPORT bool IsVRational() const override;

  Standard_EXPORT occ::handle<Geom_BezierSurface> Bezier() const override;

  Standard_EXPORT occ::handle<Geom_BSplineSurface> BSpline() const override;

  Standard_EXPORT const gp_Ax3& Axis() const;

  Standard_EXPORT occ::handle<Adaptor3d_Curve> BasisCurve() const override;

private:
  occ::handle<Adaptor3d_Curve> myBasisCurve;
  gp_Ax1                       myAxis;
  bool                         myHaveAxis;
  gp_Ax3                       myAxeRev;
};
