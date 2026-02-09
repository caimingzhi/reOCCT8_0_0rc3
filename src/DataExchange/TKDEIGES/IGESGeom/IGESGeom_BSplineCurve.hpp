#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;

class IGESGeom_BSplineCurve : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_BSplineCurve();

  Standard_EXPORT void Init(const int                                       anIndex,
                            const int                                       aDegree,
                            const bool                                      aPlanar,
                            const bool                                      aClosed,
                            const bool                                      aPolynom,
                            const bool                                      aPeriodic,
                            const occ::handle<NCollection_HArray1<double>>& allKnots,
                            const occ::handle<NCollection_HArray1<double>>& allWeights,
                            const occ::handle<NCollection_HArray1<gp_XYZ>>& allPoles,
                            const double                                    aUmin,
                            const double                                    aUmax,
                            const gp_XYZ&                                   aNorm);

  Standard_EXPORT void SetFormNumber(const int form);

  Standard_EXPORT int UpperIndex() const;

  Standard_EXPORT int Degree() const;

  Standard_EXPORT bool IsPlanar() const;

  Standard_EXPORT bool IsClosed() const;

  Standard_EXPORT bool IsPolynomial(const bool flag = false) const;

  Standard_EXPORT bool IsPeriodic() const;

  Standard_EXPORT int NbKnots() const;

  Standard_EXPORT double Knot(const int anIndex) const;

  Standard_EXPORT int NbPoles() const;

  Standard_EXPORT double Weight(const int anIndex) const;

  Standard_EXPORT gp_Pnt Pole(const int anIndex) const;

  Standard_EXPORT gp_Pnt TransformedPole(const int anIndex) const;

  Standard_EXPORT double UMin() const;

  Standard_EXPORT double UMax() const;

  Standard_EXPORT gp_XYZ Normal() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_BSplineCurve, IGESData_IGESEntity)

private:
  int                                      theIndex;
  int                                      theDegree;
  bool                                     isPlanar;
  bool                                     isClosed;
  bool                                     isPolynomial;
  bool                                     isPeriodic;
  occ::handle<NCollection_HArray1<double>> theKnots;
  occ::handle<NCollection_HArray1<double>> theWeights;
  occ::handle<NCollection_HArray1<gp_XYZ>> thePoles;
  double                                   theUmin;
  double                                   theUmax;
  gp_XYZ                                   theNorm;
};
