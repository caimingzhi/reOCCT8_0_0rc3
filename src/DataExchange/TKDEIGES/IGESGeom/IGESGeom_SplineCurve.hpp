#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Real.hpp>

class IGESGeom_SplineCurve : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_SplineCurve();

  Standard_EXPORT void Init(const int                                       aType,
                            const int                                       aDegree,
                            const int                                       nbDimensions,
                            const occ::handle<NCollection_HArray1<double>>& allBreakPoints,
                            const occ::handle<NCollection_HArray2<double>>& allXPolynomials,
                            const occ::handle<NCollection_HArray2<double>>& allYPolynomials,
                            const occ::handle<NCollection_HArray2<double>>& allZPolynomials,
                            const occ::handle<NCollection_HArray1<double>>& allXvalues,
                            const occ::handle<NCollection_HArray1<double>>& allYvalues,
                            const occ::handle<NCollection_HArray1<double>>& allZvalues);

  Standard_EXPORT int SplineType() const;

  Standard_EXPORT int Degree() const;

  Standard_EXPORT int NbDimensions() const;

  Standard_EXPORT int NbSegments() const;

  Standard_EXPORT double BreakPoint(const int Index) const;

  Standard_EXPORT void XCoordPolynomial(const int Index,
                                        double&   AX,
                                        double&   BX,
                                        double&   CX,
                                        double&   DX) const;

  Standard_EXPORT void YCoordPolynomial(const int Index,
                                        double&   AY,
                                        double&   BY,
                                        double&   CY,
                                        double&   DY) const;

  Standard_EXPORT void ZCoordPolynomial(const int Index,
                                        double&   AZ,
                                        double&   BZ,
                                        double&   CZ,
                                        double&   DZ) const;

  Standard_EXPORT void XValues(double& TPX0, double& TPX1, double& TPX2, double& TPX3) const;

  Standard_EXPORT void YValues(double& TPY0, double& TPY1, double& TPY2, double& TPY3) const;

  Standard_EXPORT void ZValues(double& TPZ0, double& TPZ1, double& TPZ2, double& TPZ3) const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_SplineCurve, IGESData_IGESEntity)

private:
  int                                      theType;
  int                                      theDegree;
  int                                      theNbDimensions;
  occ::handle<NCollection_HArray1<double>> theBreakPoints;
  occ::handle<NCollection_HArray2<double>> theXCoordsPolynomial;
  occ::handle<NCollection_HArray2<double>> theYCoordsPolynomial;
  occ::handle<NCollection_HArray2<double>> theZCoordsPolynomial;
  occ::handle<NCollection_HArray1<double>> theXvalues;
  occ::handle<NCollection_HArray1<double>> theYvalues;
  occ::handle<NCollection_HArray1<double>> theZvalues;
};
