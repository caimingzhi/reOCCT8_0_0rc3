#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <AppParCurves_MultiCurve.hpp>
#include <AppParCurves_MultiPoint.hpp>
#include <Standard_OStream.hpp>
class gp_Pnt;
class gp_Pnt2d;
class gp_Vec;
class gp_Vec2d;

class AppParCurves_MultiBSpCurve : public AppParCurves_MultiCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AppParCurves_MultiBSpCurve();

  Standard_EXPORT AppParCurves_MultiBSpCurve(const int NbPol);

  Standard_EXPORT AppParCurves_MultiBSpCurve(
    const NCollection_Array1<AppParCurves_MultiPoint>& tabMU,
    const NCollection_Array1<double>&                  Knots,
    const NCollection_Array1<int>&                     Mults);

  Standard_EXPORT AppParCurves_MultiBSpCurve(const AppParCurves_MultiCurve&    SC,
                                             const NCollection_Array1<double>& Knots,
                                             const NCollection_Array1<int>&    Mults);

  Standard_EXPORT void SetKnots(const NCollection_Array1<double>& theKnots);

  Standard_EXPORT void SetMultiplicities(const NCollection_Array1<int>& theMults);

  Standard_EXPORT const NCollection_Array1<double>& Knots() const;

  Standard_EXPORT const NCollection_Array1<int>& Multiplicities() const;

  Standard_EXPORT int Degree() const override;

  Standard_EXPORT void Value(const int CuIndex, const double U, gp_Pnt& Pt) const override;

  Standard_EXPORT void Value(const int CuIndex, const double U, gp_Pnt2d& Pt) const override;

  Standard_EXPORT void D1(const int CuIndex, const double U, gp_Pnt& Pt, gp_Vec& V1) const override;

  Standard_EXPORT void D1(const int    CuIndex,
                          const double U,
                          gp_Pnt2d&    Pt,
                          gp_Vec2d&    V1) const override;

  Standard_EXPORT void D2(const int    CuIndex,
                          const double U,
                          gp_Pnt&      Pt,
                          gp_Vec&      V1,
                          gp_Vec&      V2) const override;

  Standard_EXPORT void D2(const int    CuIndex,
                          const double U,
                          gp_Pnt2d&    Pt,
                          gp_Vec2d&    V1,
                          gp_Vec2d&    V2) const override;

  Standard_EXPORT void Dump(Standard_OStream& o) const override;

private:
  occ::handle<NCollection_HArray1<double>> myknots;
  occ::handle<NCollection_HArray1<int>>    mymults;
  int                                      myDegree;
};
