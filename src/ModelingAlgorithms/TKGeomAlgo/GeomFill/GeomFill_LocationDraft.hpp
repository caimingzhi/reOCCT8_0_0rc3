#pragma once

#include <Adaptor3d_Surface.hpp>
#include <gp_Mat.hpp>
#include <gp_Dir.hpp>
#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Boolean.hpp>
#include <GeomFill_LocationLaw.hpp>
#include <gp_Vec2d.hpp>
#include <GeomAbs_Shape.hpp>

class GeomFill_DraftTrihedron;

class GeomFill_LocationDraft : public GeomFill_LocationLaw
{

public:
  Standard_EXPORT GeomFill_LocationDraft(const gp_Dir& Direction, const double Angle);

  Standard_EXPORT void SetStopSurf(const occ::handle<Adaptor3d_Surface>& Surf);

  Standard_EXPORT void SetAngle(const double Angle);

  Standard_EXPORT bool SetCurve(const occ::handle<Adaptor3d_Curve>& C) override;

  Standard_EXPORT const occ::handle<Adaptor3d_Curve>& GetCurve() const override;

  Standard_EXPORT void SetTrsf(const gp_Mat& Transfo) override;

  Standard_EXPORT occ::handle<GeomFill_LocationLaw> Copy() const override;

  Standard_EXPORT bool D0(const double Param, gp_Mat& M, gp_Vec& V) override;

  Standard_EXPORT bool D0(const double                  Param,
                          gp_Mat&                       M,
                          gp_Vec&                       V,
                          NCollection_Array1<gp_Pnt2d>& Poles2d) override;

  Standard_EXPORT bool D1(const double                  Param,
                          gp_Mat&                       M,
                          gp_Vec&                       V,
                          gp_Mat&                       DM,
                          gp_Vec&                       DV,
                          NCollection_Array1<gp_Pnt2d>& Poles2d,
                          NCollection_Array1<gp_Vec2d>& DPoles2d) override;

  Standard_EXPORT bool D2(const double                  Param,
                          gp_Mat&                       M,
                          gp_Vec&                       V,
                          gp_Mat&                       DM,
                          gp_Vec&                       DV,
                          gp_Mat&                       D2M,
                          gp_Vec&                       D2V,
                          NCollection_Array1<gp_Pnt2d>& Poles2d,
                          NCollection_Array1<gp_Vec2d>& DPoles2d,
                          NCollection_Array1<gp_Vec2d>& D2Poles2d) override;

  Standard_EXPORT bool HasFirstRestriction() const override;

  Standard_EXPORT bool HasLastRestriction() const override;

  Standard_EXPORT int TraceNumber() const override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT void SetInterval(const double First, const double Last) override;

  Standard_EXPORT void GetInterval(double& First, double& Last) const override;

  Standard_EXPORT void GetDomain(double& First, double& Last) const override;

  Standard_EXPORT void Resolution(const int    Index,
                                  const double Tol,
                                  double&      TolU,
                                  double&      TolV) const override;

  Standard_EXPORT double GetMaximalNorm() override;

  Standard_EXPORT void GetAverageLaw(gp_Mat& AM, gp_Vec& AV) override;

  Standard_EXPORT bool IsTranslation(double& Error) const override;

  Standard_EXPORT bool IsRotation(double& Error) const override;

  Standard_EXPORT void Rotation(gp_Pnt& Center) const override;

  Standard_EXPORT bool IsIntersec() const;

  Standard_EXPORT gp_Dir Direction() const;

  DEFINE_STANDARD_RTTIEXT(GeomFill_LocationDraft, GeomFill_LocationLaw)

protected:
  occ::handle<NCollection_HArray1<gp_Pnt2d>> myPoles2d;

private:
  Standard_EXPORT void Prepare();

  gp_Mat                               Trans;
  occ::handle<GeomFill_DraftTrihedron> myLaw;
  occ::handle<Adaptor3d_Surface>       mySurf;
  occ::handle<Adaptor3d_Curve>         myCurve;
  occ::handle<Adaptor3d_Curve>         myTrimmed;
  gp_Dir                               myDir;
  double                               myAngle;
  int                                  myNbPts;
  bool                                 Intersec;
  bool                                 WithTrans;
};
