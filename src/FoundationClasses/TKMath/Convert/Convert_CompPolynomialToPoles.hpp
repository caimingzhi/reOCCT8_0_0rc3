#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>

class Convert_CompPolynomialToPoles
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Convert_CompPolynomialToPoles(
    const int                                       NumCurves,
    const int                                       Continuity,
    const int                                       Dimension,
    const int                                       MaxDegree,
    const occ::handle<NCollection_HArray1<int>>&    NumCoeffPerCurve,
    const occ::handle<NCollection_HArray1<double>>& Coefficients,
    const occ::handle<NCollection_HArray2<double>>& PolynomialIntervals,
    const occ::handle<NCollection_HArray1<double>>& TrueIntervals);

  Standard_EXPORT Convert_CompPolynomialToPoles(
    const int                         NumCurves,
    const int                         Dimension,
    const int                         MaxDegree,
    const NCollection_Array1<int>&    Continuity,
    const NCollection_Array1<int>&    NumCoeffPerCurve,
    const NCollection_Array1<double>& Coefficients,
    const NCollection_Array2<double>& PolynomialIntervals,
    const NCollection_Array1<double>& TrueIntervals);

  Standard_EXPORT Convert_CompPolynomialToPoles(
    const int                         Dimension,
    const int                         MaxDegree,
    const int                         Degree,
    const NCollection_Array1<double>& Coefficients,
    const NCollection_Array1<double>& PolynomialIntervals,
    const NCollection_Array1<double>& TrueIntervals);

  Standard_EXPORT int NbPoles() const;

  Standard_EXPORT void Poles(occ::handle<NCollection_HArray2<double>>& Poles) const;

  Standard_EXPORT int Degree() const;

  Standard_EXPORT int NbKnots() const;

  Standard_EXPORT void Knots(occ::handle<NCollection_HArray1<double>>& K) const;

  Standard_EXPORT void Multiplicities(occ::handle<NCollection_HArray1<int>>& M) const;

  Standard_EXPORT bool IsDone() const;

private:
  Standard_EXPORT void Perform(const int                         NumCurves,
                               const int                         MaxDegree,
                               const int                         Dimension,
                               const NCollection_Array1<int>&    NumCoeffPerCurve,
                               const NCollection_Array1<double>& Coefficients,
                               const NCollection_Array2<double>& PolynomialIntervals,
                               const NCollection_Array1<double>& TrueIntervals);

  occ::handle<NCollection_HArray1<double>> myFlatKnots;
  occ::handle<NCollection_HArray1<double>> myKnots;
  occ::handle<NCollection_HArray1<int>>    myMults;
  occ::handle<NCollection_HArray2<double>> myPoles;
  int                                      myDegree;
  bool                                     myDone;
};
