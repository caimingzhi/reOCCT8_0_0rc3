#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Adaptor3d_Curve.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
#include <NCollection_Array1.hpp>
#include <GeomAbs_CurveType.hpp>

class gp_Pnt;
class gp_Vec;

class GeomFill_SnglrFunc : public Adaptor3d_Curve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_SnglrFunc(const occ::handle<Adaptor3d_Curve>& HC);

  Standard_EXPORT occ::handle<Adaptor3d_Curve> ShallowCopy() const override;

  Standard_EXPORT void SetRatio(const double Ratio);

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT gp_Pnt Value(const double U) const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT double Period() const override;

  Standard_EXPORT void D0(const double U, gp_Pnt& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt& P, gp_Vec& V) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const override;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt&      P,
                          gp_Vec&      V1,
                          gp_Vec&      V2,
                          gp_Vec&      V3) const override;

  Standard_EXPORT gp_Vec DN(const double U, const int N) const override;

  Standard_EXPORT double Resolution(const double R3d) const override;

  Standard_EXPORT GeomAbs_CurveType GetType() const override;

private:
  occ::handle<Adaptor3d_Curve> myHCurve;
  double                       ratio;
};
