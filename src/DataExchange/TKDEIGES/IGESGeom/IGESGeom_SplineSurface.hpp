#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Real.hpp>

class IGESGeom_SplineSurface : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_SplineSurface();

  Standard_EXPORT void Init(
    const int                                       aBoundaryType,
    const int                                       aPatchType,
    const occ::handle<NCollection_HArray1<double>>& allUBreakpoints,
    const occ::handle<NCollection_HArray1<double>>& allVBreakpoints,
    const occ::handle<NCollection_HArray2<occ::handle<NCollection_HArray1<double>>>>& allXCoeffs,
    const occ::handle<NCollection_HArray2<occ::handle<NCollection_HArray1<double>>>>& allYCoeffs,
    const occ::handle<NCollection_HArray2<occ::handle<NCollection_HArray1<double>>>>& allZCoeffs);

  Standard_EXPORT int NbUSegments() const;

  Standard_EXPORT int NbVSegments() const;

  Standard_EXPORT int BoundaryType() const;

  Standard_EXPORT int PatchType() const;

  Standard_EXPORT double UBreakPoint(const int anIndex) const;

  Standard_EXPORT double VBreakPoint(const int anIndex) const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> XPolynomial(const int anIndex1,
                                                                       const int anIndex2) const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> YPolynomial(const int anIndex1,
                                                                       const int anIndex2) const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> ZPolynomial(const int anIndex1,
                                                                       const int anIndex2) const;

  Standard_EXPORT void Polynomials(
    occ::handle<NCollection_HArray2<occ::handle<NCollection_HArray1<double>>>>& XCoef,
    occ::handle<NCollection_HArray2<occ::handle<NCollection_HArray1<double>>>>& YCoef,
    occ::handle<NCollection_HArray2<occ::handle<NCollection_HArray1<double>>>>& ZCoef) const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_SplineSurface, IGESData_IGESEntity)

private:
  int                                                                        theBoundaryType;
  int                                                                        thePatchType;
  occ::handle<NCollection_HArray1<double>>                                   theUBreakPoints;
  occ::handle<NCollection_HArray1<double>>                                   theVBreakPoints;
  occ::handle<NCollection_HArray2<occ::handle<NCollection_HArray1<double>>>> theXCoeffs;
  occ::handle<NCollection_HArray2<occ::handle<NCollection_HArray1<double>>>> theYCoeffs;
  occ::handle<NCollection_HArray2<occ::handle<NCollection_HArray1<double>>>> theZCoeffs;
};
