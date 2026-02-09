#pragma once

#include <Adaptor3d_Curve.hpp>
#include <GeomAbs_Shape.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <gp_Ax1.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Cone.hpp>
#include <gp_Pln.hpp>
#include <gp_Sphere.hpp>
#include <gp_Torus.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <NCollection_Array1.hpp>

class Geom_BezierSurface;
class Geom_BSplineSurface;

class Adaptor3d_Surface : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Adaptor3d_Surface, Standard_Transient)
public:
  Standard_EXPORT virtual occ::handle<Adaptor3d_Surface> ShallowCopy() const;

  Standard_EXPORT virtual double FirstUParameter() const;

  Standard_EXPORT virtual double LastUParameter() const;

  Standard_EXPORT virtual double FirstVParameter() const;

  Standard_EXPORT virtual double LastVParameter() const;

  Standard_EXPORT virtual GeomAbs_Shape UContinuity() const;

  Standard_EXPORT virtual GeomAbs_Shape VContinuity() const;

  Standard_EXPORT virtual int NbUIntervals(const GeomAbs_Shape S) const;

  Standard_EXPORT virtual int NbVIntervals(const GeomAbs_Shape S) const;

  Standard_EXPORT virtual void UIntervals(NCollection_Array1<double>& T,
                                          const GeomAbs_Shape         S) const;

  Standard_EXPORT virtual void VIntervals(NCollection_Array1<double>& T,
                                          const GeomAbs_Shape         S) const;

  Standard_EXPORT virtual occ::handle<Adaptor3d_Surface> UTrim(const double First,
                                                               const double Last,
                                                               const double Tol) const;

  Standard_EXPORT virtual occ::handle<Adaptor3d_Surface> VTrim(const double First,
                                                               const double Last,
                                                               const double Tol) const;

  Standard_EXPORT virtual bool IsUClosed() const;

  Standard_EXPORT virtual bool IsVClosed() const;

  Standard_EXPORT virtual bool IsUPeriodic() const;

  Standard_EXPORT virtual double UPeriod() const;

  Standard_EXPORT virtual bool IsVPeriodic() const;

  Standard_EXPORT virtual double VPeriod() const;

  Standard_EXPORT virtual gp_Pnt Value(const double U, const double V) const;

  Standard_EXPORT virtual void D0(const double U, const double V, gp_Pnt& P) const;

  Standard_EXPORT virtual void D1(const double U,
                                  const double V,
                                  gp_Pnt&      P,
                                  gp_Vec&      D1U,
                                  gp_Vec&      D1V) const;

  Standard_EXPORT virtual void D2(const double U,
                                  const double V,
                                  gp_Pnt&      P,
                                  gp_Vec&      D1U,
                                  gp_Vec&      D1V,
                                  gp_Vec&      D2U,
                                  gp_Vec&      D2V,
                                  gp_Vec&      D2UV) const;

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
                                  gp_Vec&      D3UVV) const;

  Standard_EXPORT virtual gp_Vec DN(const double U,
                                    const double V,
                                    const int    Nu,
                                    const int    Nv) const;

  Standard_EXPORT virtual double UResolution(const double R3d) const;

  Standard_EXPORT virtual double VResolution(const double R3d) const;

  Standard_EXPORT virtual GeomAbs_SurfaceType GetType() const;

  Standard_EXPORT virtual gp_Pln Plane() const;

  Standard_EXPORT virtual gp_Cylinder Cylinder() const;

  Standard_EXPORT virtual gp_Cone Cone() const;

  Standard_EXPORT virtual gp_Sphere Sphere() const;

  Standard_EXPORT virtual gp_Torus Torus() const;

  Standard_EXPORT virtual int UDegree() const;

  Standard_EXPORT virtual int NbUPoles() const;

  Standard_EXPORT virtual int VDegree() const;

  Standard_EXPORT virtual int NbVPoles() const;

  Standard_EXPORT virtual int NbUKnots() const;

  Standard_EXPORT virtual int NbVKnots() const;

  Standard_EXPORT virtual bool IsURational() const;

  Standard_EXPORT virtual bool IsVRational() const;

  Standard_EXPORT virtual occ::handle<Geom_BezierSurface> Bezier() const;

  Standard_EXPORT virtual occ::handle<Geom_BSplineSurface> BSpline() const;

  Standard_EXPORT virtual gp_Ax1 AxeOfRevolution() const;

  Standard_EXPORT virtual gp_Dir Direction() const;

  Standard_EXPORT virtual occ::handle<Adaptor3d_Curve> BasisCurve() const;

  Standard_EXPORT virtual occ::handle<Adaptor3d_Surface> BasisSurface() const;

  Standard_EXPORT virtual double OffsetValue() const;
  Standard_EXPORT ~Adaptor3d_Surface() override;
};
