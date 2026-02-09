#pragma once

#include <Standard.hpp>

#include <gp_Mat.hpp>
#include <GeomFill_LocationLaw.hpp>
#include <Standard_Real.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Vec2d.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
class GeomFill_TrihedronLaw;

class GeomFill_CurveAndTrihedron : public GeomFill_LocationLaw
{

public:
  Standard_EXPORT GeomFill_CurveAndTrihedron(const occ::handle<GeomFill_TrihedronLaw>& Trihedron);

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

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT void SetInterval(const double First, const double Last) override;

  Standard_EXPORT void GetInterval(double& First, double& Last) const override;

  Standard_EXPORT void GetDomain(double& First, double& Last) const override;

  Standard_EXPORT double GetMaximalNorm() override;

  Standard_EXPORT void GetAverageLaw(gp_Mat& AM, gp_Vec& AV) override;

  Standard_EXPORT bool IsTranslation(double& Error) const override;

  Standard_EXPORT bool IsRotation(double& Error) const override;

  Standard_EXPORT void Rotation(gp_Pnt& Center) const override;

  DEFINE_STANDARD_RTTIEXT(GeomFill_CurveAndTrihedron, GeomFill_LocationLaw)

private:
  bool                               WithTrans;
  occ::handle<GeomFill_TrihedronLaw> myLaw;
  occ::handle<Adaptor3d_Curve>       myCurve;
  occ::handle<Adaptor3d_Curve>       myTrimmed;
  gp_Pnt                             Point;
  gp_Vec                             V1;
  gp_Vec                             V2;
  gp_Vec                             V3;
  gp_Mat                             Trans;
};
