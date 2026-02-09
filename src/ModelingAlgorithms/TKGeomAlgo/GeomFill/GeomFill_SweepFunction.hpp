#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Mat.hpp>
#include <gp_Vec.hpp>
#include <Approx_SweepFunction.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
class GeomFill_LocationLaw;
class GeomFill_SectionLaw;
class gp_Pnt;

class GeomFill_SweepFunction : public Approx_SweepFunction
{

public:
  Standard_EXPORT GeomFill_SweepFunction(const occ::handle<GeomFill_SectionLaw>&  Section,
                                         const occ::handle<GeomFill_LocationLaw>& Location,
                                         const double                             FirstParameter,
                                         const double                             FirstParameterOnS,
                                         const double RatioParameterOnS);

  Standard_EXPORT bool D0(const double                  Param,
                          const double                  First,
                          const double                  Last,
                          NCollection_Array1<gp_Pnt>&   Poles,
                          NCollection_Array1<gp_Pnt2d>& Poles2d,
                          NCollection_Array1<double>&   Weigths) override;

  Standard_EXPORT bool D1(const double                  Param,
                          const double                  First,
                          const double                  Last,
                          NCollection_Array1<gp_Pnt>&   Poles,
                          NCollection_Array1<gp_Vec>&   DPoles,
                          NCollection_Array1<gp_Pnt2d>& Poles2d,
                          NCollection_Array1<gp_Vec2d>& DPoles2d,
                          NCollection_Array1<double>&   Weigths,
                          NCollection_Array1<double>&   DWeigths) override;

  Standard_EXPORT bool D2(const double                  Param,
                          const double                  First,
                          const double                  Last,
                          NCollection_Array1<gp_Pnt>&   Poles,
                          NCollection_Array1<gp_Vec>&   DPoles,
                          NCollection_Array1<gp_Vec>&   D2Poles,
                          NCollection_Array1<gp_Pnt2d>& Poles2d,
                          NCollection_Array1<gp_Vec2d>& DPoles2d,
                          NCollection_Array1<gp_Vec2d>& D2Poles2d,
                          NCollection_Array1<double>&   Weigths,
                          NCollection_Array1<double>&   DWeigths,
                          NCollection_Array1<double>&   D2Weigths) override;

  Standard_EXPORT int Nb2dCurves() const override;

  Standard_EXPORT void SectionShape(int& NbPoles, int& NbKnots, int& Degree) const override;

  Standard_EXPORT void Knots(NCollection_Array1<double>& TKnots) const override;

  Standard_EXPORT void Mults(NCollection_Array1<int>& TMults) const override;

  Standard_EXPORT bool IsRational() const override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT void SetInterval(const double First, const double Last) override;

  Standard_EXPORT void Resolution(const int    Index,
                                  const double Tol,
                                  double&      TolU,
                                  double&      TolV) const override;

  Standard_EXPORT void GetTolerance(const double                BoundTol,
                                    const double                SurfTol,
                                    const double                AngleTol,
                                    NCollection_Array1<double>& Tol3d) const override;

  Standard_EXPORT void SetTolerance(const double Tol3d, const double Tol2d) override;

  Standard_EXPORT gp_Pnt BarycentreOfSurf() const override;

  Standard_EXPORT double MaximalSection() const override;

  Standard_EXPORT void GetMinimalWeight(NCollection_Array1<double>& Weigths) const override;

  DEFINE_STANDARD_RTTIEXT(GeomFill_SweepFunction, Approx_SweepFunction)

private:
  occ::handle<GeomFill_LocationLaw> myLoc;
  occ::handle<GeomFill_SectionLaw>  mySec;
  double                            myf;
  double                            myfOnS;
  double                            myRatio;
  gp_Mat                            M;
  gp_Mat                            DM;
  gp_Mat                            D2M;
  gp_Vec                            V;
  gp_Vec                            DV;
  gp_Vec                            D2V;
};
