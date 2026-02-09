#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <GeomFill_TrihedronWithGuide.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
#include <NCollection_Array1.hpp>
class Approx_CurvlinFunc;
class GeomFill_TrihedronLaw;
class gp_Vec;

class GeomFill_GuideTrihedronAC : public GeomFill_TrihedronWithGuide
{

public:
  Standard_EXPORT GeomFill_GuideTrihedronAC(const occ::handle<Adaptor3d_Curve>& guide);

  Standard_EXPORT bool SetCurve(const occ::handle<Adaptor3d_Curve>& C) override;

  Standard_EXPORT occ::handle<GeomFill_TrihedronLaw> Copy() const override;

  Standard_EXPORT occ::handle<Adaptor3d_Curve> Guide() const override;

  Standard_EXPORT bool D0(const double Param,
                          gp_Vec&      Tangent,
                          gp_Vec&      Normal,
                          gp_Vec&      BiNormal) override;

  Standard_EXPORT bool D1(const double Param,
                          gp_Vec&      Tangent,
                          gp_Vec&      DTangent,
                          gp_Vec&      Normal,
                          gp_Vec&      DNormal,
                          gp_Vec&      BiNormal,
                          gp_Vec&      DBiNormal) override;

  Standard_EXPORT bool D2(const double Param,
                          gp_Vec&      Tangent,
                          gp_Vec&      DTangent,
                          gp_Vec&      D2Tangent,
                          gp_Vec&      Normal,
                          gp_Vec&      DNormal,
                          gp_Vec&      D2Normal,
                          gp_Vec&      BiNormal,
                          gp_Vec&      DBiNormal,
                          gp_Vec&      D2BiNormal) override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT void SetInterval(const double First, const double Last) override;

  Standard_EXPORT void GetAverageLaw(gp_Vec& ATangent, gp_Vec& ANormal, gp_Vec& ABiNormal) override;

  Standard_EXPORT bool IsConstant() const override;

  Standard_EXPORT bool IsOnlyBy3dCurve() const override;

  Standard_EXPORT void Origine(const double OrACR1, const double OrACR2) override;

  DEFINE_STANDARD_RTTIEXT(GeomFill_GuideTrihedronAC, GeomFill_TrihedronWithGuide)

private:
  occ::handle<Approx_CurvlinFunc> myGuideAC;
  double                          Lguide;
  occ::handle<Approx_CurvlinFunc> myCurveAC;
  double                          L;
  occ::handle<Adaptor3d_Curve>    myCurve;
  double                          UTol;
  double                          STol;
  double                          Orig1;
  double                          Orig2;
};
