#pragma once

#include <Adaptor3d_Curve.hpp>
#include <Adaptor3d_Surface.hpp>
#include <BSplSLib_Cache.hpp>
#include <GeomAbs_Shape.hpp>
#include <Geom_Surface.hpp>
#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>
#include <gp_XYZ.hpp>
#include <Standard_NullObject.hpp>
#include <NCollection_Array1.hpp>

#include <variant>

class GeomAdaptor_Curve;
class Geom_OffsetSurface;

class GeomAdaptor_Surface : public Adaptor3d_Surface
{
  DEFINE_STANDARD_RTTIEXT(GeomAdaptor_Surface, Adaptor3d_Surface)
public:
  struct ExtrusionData
  {
    occ::handle<Adaptor3d_Curve> BasisCurve;
    gp_XYZ                       Direction;
  };

  struct RevolutionData
  {
    occ::handle<Adaptor3d_Curve> BasisCurve;
    gp_Ax1                       Axis;
  };

  struct OffsetData
  {
    occ::handle<GeomAdaptor_Surface> BasisAdaptor;
    occ::handle<GeomAdaptor_Surface> EquivalentAdaptor;
    occ::handle<Geom_OffsetSurface>  OffsetSurface;
    double                           Offset = 0.0;
  };

  struct BezierData
  {
    mutable occ::handle<BSplSLib_Cache> Cache;
  };

  struct BSplineData
  {
    occ::handle<Geom_BSplineSurface>    Surface;
    mutable occ::handle<BSplSLib_Cache> Cache;
  };

  using SurfaceDataVariant = std::
    variant<std::monostate, ExtrusionData, RevolutionData, OffsetData, BezierData, BSplineData>;

public:
  GeomAdaptor_Surface()
      : myUFirst(0.),
        myULast(0.),
        myVFirst(0.),
        myVLast(0.),
        myTolU(0.),
        myTolV(0.),
        mySurfaceType(GeomAbs_OtherSurface)
  {
  }

  GeomAdaptor_Surface(const occ::handle<Geom_Surface>& theSurf)
      : myTolU(0.),
        myTolV(0.)
  {
    Load(theSurf);
  }

  GeomAdaptor_Surface(const occ::handle<Geom_Surface>& theSurf,
                      const double                     theUFirst,
                      const double                     theULast,
                      const double                     theVFirst,
                      const double                     theVLast,
                      const double                     theTolU = 0.0,
                      const double                     theTolV = 0.0)
  {
    Load(theSurf, theUFirst, theULast, theVFirst, theVLast, theTolU, theTolV);
  }

  Standard_EXPORT occ::handle<Adaptor3d_Surface> ShallowCopy() const override;

  void Load(const occ::handle<Geom_Surface>& theSurf)
  {
    if (theSurf.IsNull())
    {
      throw Standard_NullObject("GeomAdaptor_Surface::Load");
    }

    double aU1, aU2, aV1, aV2;
    theSurf->Bounds(aU1, aU2, aV1, aV2);
    load(theSurf, aU1, aU2, aV1, aV2);
  }

  void Load(const occ::handle<Geom_Surface>& theSurf,
            const double                     theUFirst,
            const double                     theULast,
            const double                     theVFirst,
            const double                     theVLast,
            const double                     theTolU = 0.0,
            const double                     theTolV = 0.0)
  {
    if (theSurf.IsNull())
    {
      throw Standard_NullObject("GeomAdaptor_Surface::Load");
    }
    if (theUFirst > theULast || theVFirst > theVLast)
    {
      throw Standard_ConstructionError("GeomAdaptor_Surface::Load");
    }

    load(theSurf, theUFirst, theULast, theVFirst, theVLast, theTolU, theTolV);
  }

  const occ::handle<Geom_Surface>& Surface() const { return mySurface; }

  double FirstUParameter() const override { return myUFirst; }

  double LastUParameter() const override { return myULast; }

  double FirstVParameter() const override { return myVFirst; }

  double LastVParameter() const override { return myVLast; }

  void Bounds(double& theU1, double& theU2, double& theV1, double& theV2) const
  {
    theU1 = FirstUParameter();
    theU2 = LastUParameter();
    theV1 = FirstVParameter();
    theV2 = LastVParameter();
  }

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

  Standard_EXPORT gp_Pnt Value(const double U, const double V) const final;

  Standard_EXPORT void D0(const double U, const double V, gp_Pnt& P) const final;

  Standard_EXPORT void D1(const double U,
                          const double V,
                          gp_Pnt&      P,
                          gp_Vec&      D1U,
                          gp_Vec&      D1V) const final;

  Standard_EXPORT void D2(const double U,
                          const double V,
                          gp_Pnt&      P,
                          gp_Vec&      D1U,
                          gp_Vec&      D1V,
                          gp_Vec&      D2U,
                          gp_Vec&      D2V,
                          gp_Vec&      D2UV) const final;

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
                          gp_Vec&      D3UVV) const final;

  Standard_EXPORT gp_Vec DN(const double U, const double V, const int Nu, const int Nv) const final;

  Standard_EXPORT double UResolution(const double R3d) const override;

  Standard_EXPORT double VResolution(const double R3d) const override;

  GeomAbs_SurfaceType GetType() const override { return mySurfaceType; }

  Standard_EXPORT gp_Pln Plane() const override;

  Standard_EXPORT gp_Cylinder Cylinder() const override;

  Standard_EXPORT gp_Cone Cone() const override;

  Standard_EXPORT gp_Sphere Sphere() const override;

  Standard_EXPORT gp_Torus Torus() const override;

  Standard_EXPORT int UDegree() const override;

  Standard_EXPORT int NbUPoles() const override;

  Standard_EXPORT int VDegree() const override;

  Standard_EXPORT int NbVPoles() const override;

  Standard_EXPORT int NbUKnots() const override;

  Standard_EXPORT int NbVKnots() const override;

  Standard_EXPORT bool IsURational() const override;

  Standard_EXPORT bool IsVRational() const override;

  Standard_EXPORT occ::handle<Geom_BezierSurface> Bezier() const override;

  Standard_EXPORT occ::handle<Geom_BSplineSurface> BSpline() const override;

  Standard_EXPORT gp_Ax1 AxeOfRevolution() const override;

  Standard_EXPORT gp_Dir Direction() const override;

  Standard_EXPORT occ::handle<Adaptor3d_Curve> BasisCurve() const override;

  Standard_EXPORT occ::handle<Adaptor3d_Surface> BasisSurface() const override;

  Standard_EXPORT double OffsetValue() const override;

private:
  Standard_EXPORT void Span(const int Side,
                            const int Ideb,
                            const int Ifin,
                            int&      OutIdeb,
                            int&      OutIfin,
                            const int FKIndx,
                            const int LKIndx) const;

  Standard_EXPORT bool IfUVBound(const double U,
                                 const double V,
                                 int&         Ideb,
                                 int&         Ifin,
                                 int&         IVdeb,
                                 int&         IVfin,
                                 const int    USide,
                                 const int    VSide) const;

  Standard_EXPORT void load(const occ::handle<Geom_Surface>& S,
                            const double                     UFirst,
                            const double                     ULast,
                            const double                     VFirst,
                            const double                     VLast,
                            const double                     TolU = 0.0,
                            const double                     TolV = 0.0);

  Standard_EXPORT void RebuildCache(const double theU, const double theV) const;

protected:
  occ::handle<Geom_Surface> mySurface;
  double                    myUFirst;
  double                    myULast;
  double                    myVFirst;
  double                    myVLast;
  double                    myTolU;
  double                    myTolV;
  GeomAbs_SurfaceType       mySurfaceType;
  SurfaceDataVariant        mySurfaceData;
};
