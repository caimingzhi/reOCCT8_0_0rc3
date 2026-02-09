#pragma once

#include <Standard.hpp>

#include <gp_Pnt2d.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <math_Vector.hpp>
#include <Standard_Integer.hpp>
#include <GeomFill_TrihedronWithGuide.hpp>
#include <Standard_Real.hpp>
#include <GeomAbs_Shape.hpp>
#include <NCollection_Array1.hpp>

class GeomFill_Frenet;
class GeomFill_TrihedronLaw;
class gp_Vec;

class GeomFill_GuideTrihedronPlan : public GeomFill_TrihedronWithGuide
{

public:
  Standard_EXPORT GeomFill_GuideTrihedronPlan(const occ::handle<Adaptor3d_Curve>& theGuide);

  Standard_EXPORT bool SetCurve(const occ::handle<Adaptor3d_Curve>& thePath) override;

  Standard_EXPORT occ::handle<GeomFill_TrihedronLaw> Copy() const override;

  Standard_EXPORT GeomFill_PipeError ErrorStatus() const override;

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

  Standard_EXPORT void SetInterval(const double First, const double Last) override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT void GetAverageLaw(gp_Vec& ATangent, gp_Vec& ANormal, gp_Vec& ABiNormal) override;

  Standard_EXPORT bool IsConstant() const override;

  Standard_EXPORT bool IsOnlyBy3dCurve() const override;

  Standard_EXPORT void Origine(const double OrACR1, const double OrACR2) override;

  DEFINE_STANDARD_RTTIEXT(GeomFill_GuideTrihedronPlan, GeomFill_TrihedronWithGuide)

private:
  Standard_EXPORT void Init();

  Standard_EXPORT void InitX(const double Param);

  occ::handle<Adaptor3d_Curve>               myTrimmed;
  occ::handle<Adaptor3d_Curve>               myCurve;
  occ::handle<NCollection_HArray2<gp_Pnt2d>> Pole;
  math_Vector                                X;
  math_Vector                                XTol;
  math_Vector                                Inf;
  math_Vector                                Sup;
  occ::handle<GeomFill_Frenet>               frenet;
  int                                        myNbPts;
  GeomFill_PipeError                         myStatus;
};
