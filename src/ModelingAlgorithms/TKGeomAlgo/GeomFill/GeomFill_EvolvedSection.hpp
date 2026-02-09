#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <GeomFill_SectionLaw.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Vec.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
class Geom_Curve;
class Law_Function;
class Geom_BSplineCurve;
class Geom_BSplineSurface;
class gp_Pnt;

class GeomFill_EvolvedSection : public GeomFill_SectionLaw
{

public:
  Standard_EXPORT GeomFill_EvolvedSection(const occ::handle<Geom_Curve>&   C,
                                          const occ::handle<Law_Function>& L);

  Standard_EXPORT bool D0(const double                Param,
                          NCollection_Array1<gp_Pnt>& Poles,
                          NCollection_Array1<double>& Weigths) override;

  Standard_EXPORT bool D1(const double                Param,
                          NCollection_Array1<gp_Pnt>& Poles,
                          NCollection_Array1<gp_Vec>& DPoles,
                          NCollection_Array1<double>& Weigths,
                          NCollection_Array1<double>& DWeigths) override;

  Standard_EXPORT bool D2(const double                Param,
                          NCollection_Array1<gp_Pnt>& Poles,
                          NCollection_Array1<gp_Vec>& DPoles,
                          NCollection_Array1<gp_Vec>& D2Poles,
                          NCollection_Array1<double>& Weigths,
                          NCollection_Array1<double>& DWeigths,
                          NCollection_Array1<double>& D2Weigths) override;

  Standard_EXPORT occ::handle<Geom_BSplineSurface> BSplineSurface() const override;

  Standard_EXPORT void SectionShape(int& NbPoles, int& NbKnots, int& Degree) const override;

  Standard_EXPORT void Knots(NCollection_Array1<double>& TKnots) const override;

  Standard_EXPORT void Mults(NCollection_Array1<int>& TMults) const override;

  Standard_EXPORT bool IsRational() const override;

  Standard_EXPORT bool IsUPeriodic() const override;

  Standard_EXPORT bool IsVPeriodic() const override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT void SetInterval(const double First, const double Last) override;

  Standard_EXPORT void GetInterval(double& First, double& Last) const override;

  Standard_EXPORT void GetDomain(double& First, double& Last) const override;

  Standard_EXPORT void GetTolerance(const double                BoundTol,
                                    const double                SurfTol,
                                    const double                AngleTol,
                                    NCollection_Array1<double>& Tol3d) const override;

  Standard_EXPORT gp_Pnt BarycentreOfSurf() const override;

  Standard_EXPORT double MaximalSection() const override;

  Standard_EXPORT void GetMinimalWeight(NCollection_Array1<double>& Weigths) const override;

  Standard_EXPORT bool IsConstant(double& Error) const override;

  Standard_EXPORT occ::handle<Geom_Curve> ConstantSection() const override;

  DEFINE_STANDARD_RTTIEXT(GeomFill_EvolvedSection, GeomFill_SectionLaw)

private:
  double                         First;
  double                         Last;
  occ::handle<Geom_Curve>        mySection;
  occ::handle<Law_Function>      myLaw;
  occ::handle<Law_Function>      TLaw;
  occ::handle<Geom_BSplineCurve> myCurve;
};
