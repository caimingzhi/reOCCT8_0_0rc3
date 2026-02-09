#pragma once

#include <Standard.hpp>

#include <Standard_Real.hpp>
#include <Geom_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Trsf.hpp>
#include <GeomFill_SectionLaw.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Vec.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
class Geom_BSplineSurface;
class gp_Pnt;
class Geom_Curve;

class GeomFill_NSections : public GeomFill_SectionLaw
{

public:
  Standard_EXPORT GeomFill_NSections(const NCollection_Sequence<occ::handle<Geom_Curve>>& NC);

  Standard_EXPORT GeomFill_NSections(const NCollection_Sequence<occ::handle<Geom_Curve>>& NC,
                                     const NCollection_Sequence<double>&                  NP);

  Standard_EXPORT GeomFill_NSections(const NCollection_Sequence<occ::handle<Geom_Curve>>& NC,
                                     const NCollection_Sequence<double>&                  NP,
                                     const double                                         UF,
                                     const double                                         UL);

  Standard_EXPORT GeomFill_NSections(const NCollection_Sequence<occ::handle<Geom_Curve>>& NC,
                                     const NCollection_Sequence<double>&                  NP,
                                     const double                                         UF,
                                     const double                                         UL,
                                     const double                                         VF,
                                     const double                                         VL);

  Standard_EXPORT GeomFill_NSections(const NCollection_Sequence<occ::handle<Geom_Curve>>& NC,
                                     const NCollection_Sequence<gp_Trsf>&                 Trsfs,
                                     const NCollection_Sequence<double>&                  NP,
                                     const double                                         UF,
                                     const double                                         UL,
                                     const double                                         VF,
                                     const double                                         VL,
                                     const occ::handle<Geom_BSplineSurface>&              Surf);

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

  Standard_EXPORT void SetSurface(const occ::handle<Geom_BSplineSurface>& RefSurf);

  Standard_EXPORT void ComputeSurface();

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

  Standard_EXPORT bool IsConicalLaw(double& Error) const override;

  Standard_EXPORT occ::handle<Geom_Curve> CirclSection(const double Param) const override;

  DEFINE_STANDARD_RTTIEXT(GeomFill_NSections, GeomFill_SectionLaw)

private:
  double                                        UFirst;
  double                                        ULast;
  double                                        VFirst;
  double                                        VLast;
  NCollection_Sequence<occ::handle<Geom_Curve>> mySections;
  NCollection_Sequence<gp_Trsf>                 myTrsfs;
  NCollection_Sequence<double>                  myParams;
  occ::handle<Geom_BSplineSurface>              mySurface;
  occ::handle<Geom_BSplineSurface>              myRefSurf;
};
