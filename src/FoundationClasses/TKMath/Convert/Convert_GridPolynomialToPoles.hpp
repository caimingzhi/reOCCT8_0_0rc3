#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>

class Convert_GridPolynomialToPoles
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Convert_GridPolynomialToPoles(
    const int                                       MaxUDegree,
    const int                                       MaxVDegree,
    const occ::handle<NCollection_HArray1<int>>&    NumCoeff,
    const occ::handle<NCollection_HArray1<double>>& Coefficients,
    const occ::handle<NCollection_HArray1<double>>& PolynomialUIntervals,
    const occ::handle<NCollection_HArray1<double>>& PolynomialVIntervals);

  Standard_EXPORT Convert_GridPolynomialToPoles(
    const int                                       NbUSurfaces,
    const int                                       NBVSurfaces,
    const int                                       UContinuity,
    const int                                       VContinuity,
    const int                                       MaxUDegree,
    const int                                       MaxVDegree,
    const occ::handle<NCollection_HArray2<int>>&    NumCoeffPerSurface,
    const occ::handle<NCollection_HArray1<double>>& Coefficients,
    const occ::handle<NCollection_HArray1<double>>& PolynomialUIntervals,
    const occ::handle<NCollection_HArray1<double>>& PolynomialVIntervals,
    const occ::handle<NCollection_HArray1<double>>& TrueUIntervals,
    const occ::handle<NCollection_HArray1<double>>& TrueVIntervals);

  Standard_EXPORT void Perform(const int                                       UContinuity,
                               const int                                       VContinuity,
                               const int                                       MaxUDegree,
                               const int                                       MaxVDegree,
                               const occ::handle<NCollection_HArray2<int>>&    NumCoeffPerSurface,
                               const occ::handle<NCollection_HArray1<double>>& Coefficients,
                               const occ::handle<NCollection_HArray1<double>>& PolynomialUIntervals,
                               const occ::handle<NCollection_HArray1<double>>& PolynomialVIntervals,
                               const occ::handle<NCollection_HArray1<double>>& TrueUIntervals,
                               const occ::handle<NCollection_HArray1<double>>& TrueVIntervals);

  Standard_EXPORT int NbUPoles() const;

  Standard_EXPORT int NbVPoles() const;

  Standard_EXPORT const occ::handle<NCollection_HArray2<gp_Pnt>>& Poles() const;

  Standard_EXPORT int UDegree() const;

  Standard_EXPORT int VDegree() const;

  Standard_EXPORT int NbUKnots() const;

  Standard_EXPORT int NbVKnots() const;

  Standard_EXPORT const occ::handle<NCollection_HArray1<double>>& UKnots() const;

  Standard_EXPORT const occ::handle<NCollection_HArray1<double>>& VKnots() const;

  Standard_EXPORT const occ::handle<NCollection_HArray1<int>>& UMultiplicities() const;

  Standard_EXPORT const occ::handle<NCollection_HArray1<int>>& VMultiplicities() const;

  Standard_EXPORT bool IsDone() const;

private:
  Standard_EXPORT void BuildArray(const int                                       Degree,
                                  const occ::handle<NCollection_HArray1<double>>& Knots,
                                  const int                                       Continuty,
                                  occ::handle<NCollection_HArray1<double>>&       FlatKnots,
                                  occ::handle<NCollection_HArray1<int>>&          Mults,
                                  occ::handle<NCollection_HArray1<double>>&       Parameters) const;

  occ::handle<NCollection_HArray1<double>> myUFlatKnots;
  occ::handle<NCollection_HArray1<double>> myVFlatKnots;
  occ::handle<NCollection_HArray1<double>> myUKnots;
  occ::handle<NCollection_HArray1<double>> myVKnots;
  occ::handle<NCollection_HArray1<int>>    myUMults;
  occ::handle<NCollection_HArray1<int>>    myVMults;
  occ::handle<NCollection_HArray2<gp_Pnt>> myPoles;
  int                                      myUDegree;
  int                                      myVDegree;
  bool                                     myDone;
};
