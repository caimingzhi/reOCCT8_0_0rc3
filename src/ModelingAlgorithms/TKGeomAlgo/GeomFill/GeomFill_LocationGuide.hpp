#pragma once

#include <Standard.hpp>

#include <gp_Pnt2d.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <gp_Mat.hpp>
#include <math_Vector.hpp>
#include <GeomFill_LocationLaw.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Vec2d.hpp>
#include <GeomAbs_Shape.hpp>
#include <NCollection_HArray1.hpp>
class GeomFill_TrihedronWithGuide;
class GeomFill_SectionLaw;
class gp_Vec;
class gp_Pnt;
class Geom_Curve;

class GeomFill_LocationGuide : public GeomFill_LocationLaw
{

public:
  Standard_EXPORT GeomFill_LocationGuide(const occ::handle<GeomFill_TrihedronWithGuide>& Triedre);

  Standard_EXPORT void Set(const occ::handle<GeomFill_SectionLaw>& Section,
                           const bool                              rotat,
                           const double                            SFirst,
                           const double                            SLast,
                           const double                            PrecAngle,
                           double&                                 LastAngle);

  Standard_EXPORT void EraseRotation();

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

  Standard_EXPORT GeomFill_PipeError ErrorStatus() const override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT void SetInterval(const double First, const double Last) override;

  Standard_EXPORT void GetInterval(double& First, double& Last) const override;

  Standard_EXPORT void GetDomain(double& First, double& Last) const override;

  Standard_EXPORT void SetTolerance(const double Tol3d, const double Tol2d) override;

  Standard_EXPORT void Resolution(const int    Index,
                                  const double Tol,
                                  double&      TolU,
                                  double&      TolV) const override;

  Standard_EXPORT double GetMaximalNorm() override;

  Standard_EXPORT void GetAverageLaw(gp_Mat& AM, gp_Vec& AV) override;

  Standard_EXPORT bool IsTranslation(double& Error) const override;

  Standard_EXPORT bool IsRotation(double& Error) const override;

  Standard_EXPORT void Rotation(gp_Pnt& Center) const override;

  Standard_EXPORT occ::handle<Geom_Curve> Section() const;

  Standard_EXPORT occ::handle<Adaptor3d_Curve> Guide() const;

  Standard_EXPORT void SetOrigine(const double Param1, const double Param2);

  Standard_EXPORT GeomFill_PipeError
    ComputeAutomaticLaw(occ::handle<NCollection_HArray1<gp_Pnt2d>>& ParAndRad) const;

  DEFINE_STANDARD_RTTIEXT(GeomFill_LocationGuide, GeomFill_LocationLaw)

protected:
  occ::handle<NCollection_HArray2<gp_Pnt2d>> myPoles2d;

private:
  Standard_EXPORT void SetRotation(const double PrecAngle, double& LastAngle);

  Standard_EXPORT void InitX(const double Param);

  occ::handle<GeomFill_TrihedronWithGuide> myLaw;
  occ::handle<GeomFill_SectionLaw>         mySec;
  occ::handle<Adaptor3d_Curve>             myCurve;
  occ::handle<Adaptor3d_Curve>             myGuide;
  occ::handle<Adaptor3d_Curve>             myTrimmed;
  int                                      myNbPts;
  bool                                     rotation;
  double                                   OrigParam1;
  double                                   OrigParam2;
  double                                   Uf;
  double                                   Ul;
  double                                   myFirstS;
  double                                   myLastS;
  double                                   ratio;
  bool                                     WithTrans;
  gp_Mat                                   Trans;
  math_Vector                              TolRes;
  math_Vector                              Inf;
  math_Vector                              Sup;
  math_Vector                              X;
  math_Vector                              R;
  GeomFill_PipeError                       myStatus;
};
