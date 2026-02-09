#pragma once

#include <Adaptor3d_Surface.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <gp_Trsf.hpp>

class GeomAdaptor_TransformedSurface : public Adaptor3d_Surface
{
  DEFINE_STANDARD_RTTIEXT(GeomAdaptor_TransformedSurface, Adaptor3d_Surface)
public:
  Standard_EXPORT GeomAdaptor_TransformedSurface();

  Standard_EXPORT GeomAdaptor_TransformedSurface(const occ::handle<Geom_Surface>& theSurface,
                                                 const gp_Trsf&                   theTrsf);

  Standard_EXPORT GeomAdaptor_TransformedSurface(const occ::handle<Geom_Surface>& theSurface,
                                                 const double                     theUFirst,
                                                 const double                     theULast,
                                                 const double                     theVFirst,
                                                 const double                     theVLast,
                                                 const gp_Trsf&                   theTrsf,
                                                 const double                     theTolU = 0.0,
                                                 const double                     theTolV = 0.0);

  Standard_EXPORT occ::handle<Adaptor3d_Surface> ShallowCopy() const override;

  void Load(const occ::handle<Geom_Surface>& theSurface) { mySurf.Load(theSurface); }

  void Load(const occ::handle<Geom_Surface>& theSurface,
            const double                     theUFirst,
            const double                     theULast,
            const double                     theVFirst,
            const double                     theVLast,
            const double                     theTolU = 0.0,
            const double                     theTolV = 0.0)
  {
    mySurf.Load(theSurface, theUFirst, theULast, theVFirst, theVLast, theTolU, theTolV);
  }

  void SetTrsf(const gp_Trsf& theTrsf) { myTrsf = theTrsf; }

  const gp_Trsf& Trsf() const { return myTrsf; }

  const GeomAdaptor_Surface& Surface() const { return mySurf; }

  GeomAdaptor_Surface& ChangeSurface() { return mySurf; }

  const occ::handle<Geom_Surface>& GeomSurface() const { return mySurf.Surface(); }

  double FirstUParameter() const override { return mySurf.FirstUParameter(); }

  double LastUParameter() const override { return mySurf.LastUParameter(); }

  double FirstVParameter() const override { return mySurf.FirstVParameter(); }

  double LastVParameter() const override { return mySurf.LastVParameter(); }

  GeomAbs_Shape UContinuity() const override { return mySurf.UContinuity(); }

  GeomAbs_Shape VContinuity() const override { return mySurf.VContinuity(); }

  int NbUIntervals(const GeomAbs_Shape theS) const override { return mySurf.NbUIntervals(theS); }

  int NbVIntervals(const GeomAbs_Shape theS) const override { return mySurf.NbVIntervals(theS); }

  Standard_EXPORT void UIntervals(NCollection_Array1<double>& theT,
                                  const GeomAbs_Shape         theS) const override;

  Standard_EXPORT void VIntervals(NCollection_Array1<double>& theT,
                                  const GeomAbs_Shape         theS) const override;

  Standard_EXPORT occ::handle<Adaptor3d_Surface> UTrim(const double theFirst,
                                                       const double theLast,
                                                       const double theTol) const override;

  Standard_EXPORT occ::handle<Adaptor3d_Surface> VTrim(const double theFirst,
                                                       const double theLast,
                                                       const double theTol) const override;

  bool IsUClosed() const override { return mySurf.IsUClosed(); }

  bool IsVClosed() const override { return mySurf.IsVClosed(); }

  bool IsUPeriodic() const override { return mySurf.IsUPeriodic(); }

  double UPeriod() const override { return mySurf.UPeriod(); }

  bool IsVPeriodic() const override { return mySurf.IsVPeriodic(); }

  double VPeriod() const override { return mySurf.VPeriod(); }

  Standard_EXPORT gp_Pnt Value(const double theU, const double theV) const final;

  Standard_EXPORT void D0(const double theU, const double theV, gp_Pnt& theP) const final;

  Standard_EXPORT void D1(const double theU,
                          const double theV,
                          gp_Pnt&      theP,
                          gp_Vec&      theD1U,
                          gp_Vec&      theD1V) const final;

  Standard_EXPORT void D2(const double theU,
                          const double theV,
                          gp_Pnt&      theP,
                          gp_Vec&      theD1U,
                          gp_Vec&      theD1V,
                          gp_Vec&      theD2U,
                          gp_Vec&      theD2V,
                          gp_Vec&      theD2UV) const final;

  Standard_EXPORT void D3(const double theU,
                          const double theV,
                          gp_Pnt&      theP,
                          gp_Vec&      theD1U,
                          gp_Vec&      theD1V,
                          gp_Vec&      theD2U,
                          gp_Vec&      theD2V,
                          gp_Vec&      theD2UV,
                          gp_Vec&      theD3U,
                          gp_Vec&      theD3V,
                          gp_Vec&      theD3UUV,
                          gp_Vec&      theD3UVV) const final;

  Standard_EXPORT gp_Vec DN(const double theU,
                            const double theV,
                            const int    theNu,
                            const int    theNv) const final;

  double UResolution(const double theR3d) const override { return mySurf.UResolution(theR3d); }

  double VResolution(const double theR3d) const override { return mySurf.VResolution(theR3d); }

  GeomAbs_SurfaceType GetType() const override { return mySurf.GetType(); }

  Standard_EXPORT gp_Pln Plane() const override;

  Standard_EXPORT gp_Cylinder Cylinder() const override;

  Standard_EXPORT gp_Cone Cone() const override;

  Standard_EXPORT gp_Sphere Sphere() const override;

  Standard_EXPORT gp_Torus Torus() const override;

  int UDegree() const override { return mySurf.UDegree(); }

  int NbUPoles() const override { return mySurf.NbUPoles(); }

  int VDegree() const override { return mySurf.VDegree(); }

  int NbVPoles() const override { return mySurf.NbVPoles(); }

  int NbUKnots() const override { return mySurf.NbUKnots(); }

  int NbVKnots() const override { return mySurf.NbVKnots(); }

  bool IsURational() const override { return mySurf.IsURational(); }

  bool IsVRational() const override { return mySurf.IsVRational(); }

  Standard_EXPORT occ::handle<Geom_BezierSurface> Bezier() const override;

  Standard_EXPORT occ::handle<Geom_BSplineSurface> BSpline() const override;

  Standard_EXPORT gp_Ax1 AxeOfRevolution() const override;

  Standard_EXPORT gp_Dir Direction() const override;

  Standard_EXPORT occ::handle<Adaptor3d_Curve> BasisCurve() const override;

  Standard_EXPORT occ::handle<Adaptor3d_Surface> BasisSurface() const override;

  Standard_EXPORT double OffsetValue() const override;

protected:
  GeomAdaptor_Surface mySurf;
  gp_Trsf             myTrsf;
};
