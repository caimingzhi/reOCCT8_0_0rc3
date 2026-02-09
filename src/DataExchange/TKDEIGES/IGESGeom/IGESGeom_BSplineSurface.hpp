#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;

class IGESGeom_BSplineSurface : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_BSplineSurface();

  Standard_EXPORT void Init(const int                                       anIndexU,
                            const int                                       anIndexV,
                            const int                                       aDegU,
                            const int                                       aDegV,
                            const bool                                      aCloseU,
                            const bool                                      aCloseV,
                            const bool                                      aPolynom,
                            const bool                                      aPeriodU,
                            const bool                                      aPeriodV,
                            const occ::handle<NCollection_HArray1<double>>& allKnotsU,
                            const occ::handle<NCollection_HArray1<double>>& allKnotsV,
                            const occ::handle<NCollection_HArray2<double>>& allWeights,
                            const occ::handle<NCollection_HArray2<gp_XYZ>>& allPoles,
                            const double                                    aUmin,
                            const double                                    aUmax,
                            const double                                    aVmin,
                            const double                                    aVmax);

  Standard_EXPORT void SetFormNumber(const int form);

  Standard_EXPORT int UpperIndexU() const;

  Standard_EXPORT int UpperIndexV() const;

  Standard_EXPORT int DegreeU() const;

  Standard_EXPORT int DegreeV() const;

  Standard_EXPORT bool IsClosedU() const;

  Standard_EXPORT bool IsClosedV() const;

  Standard_EXPORT bool IsPolynomial(const bool flag = false) const;

  Standard_EXPORT bool IsPeriodicU() const;

  Standard_EXPORT bool IsPeriodicV() const;

  Standard_EXPORT int NbKnotsU() const;

  Standard_EXPORT int NbKnotsV() const;

  Standard_EXPORT double KnotU(const int anIndex) const;

  Standard_EXPORT double KnotV(const int anIndex) const;

  Standard_EXPORT int NbPolesU() const;

  Standard_EXPORT int NbPolesV() const;

  Standard_EXPORT double Weight(const int anIndex1, const int anIndex2) const;

  Standard_EXPORT gp_Pnt Pole(const int anIndex1, const int anIndex2) const;

  Standard_EXPORT gp_Pnt TransformedPole(const int anIndex1, const int anIndex2) const;

  Standard_EXPORT double UMin() const;

  Standard_EXPORT double UMax() const;

  Standard_EXPORT double VMin() const;

  Standard_EXPORT double VMax() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_BSplineSurface, IGESData_IGESEntity)

private:
  int                                      theIndexU;
  int                                      theIndexV;
  int                                      theDegreeU;
  int                                      theDegreeV;
  bool                                     isClosedU;
  bool                                     isClosedV;
  bool                                     isPolynomial;
  bool                                     isPeriodicU;
  bool                                     isPeriodicV;
  occ::handle<NCollection_HArray1<double>> theKnotsU;
  occ::handle<NCollection_HArray1<double>> theKnotsV;
  occ::handle<NCollection_HArray2<double>> theWeights;
  occ::handle<NCollection_HArray2<gp_XYZ>> thePoles;
  double                                   theUmin;
  double                                   theUmax;
  double                                   theVmin;
  double                                   theVmax;
};
