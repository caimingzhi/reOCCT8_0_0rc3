#pragma once

#include <Standard.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>

#include <TCollection_HAsciiString.hpp>

class StepGeom_SuParameters : public StepGeom_GeometricRepresentationItem
{
public:
  Standard_EXPORT StepGeom_SuParameters();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
                            const double                                 theA,
                            const double                                 theAlpha,
                            const double                                 theB,
                            const double                                 theBeta,
                            const double                                 theC,
                            const double                                 theGamma);

  Standard_EXPORT double A() const;

  Standard_EXPORT void SetA(const double theA);

  Standard_EXPORT double Alpha() const;

  Standard_EXPORT void SetAlpha(const double theAlpha);

  Standard_EXPORT double B() const;

  Standard_EXPORT void SetB(const double theB);

  Standard_EXPORT double Beta() const;

  Standard_EXPORT void SetBeta(const double theBeta);

  Standard_EXPORT double C() const;

  Standard_EXPORT void SetC(const double theC);

  Standard_EXPORT double Gamma() const;

  Standard_EXPORT void SetGamma(const double theGamma);

  DEFINE_STANDARD_RTTIEXT(StepGeom_SuParameters, StepGeom_GeometricRepresentationItem)

private:
  double myA;
  double myAlpha;
  double myB;
  double myBeta;
  double myC;
  double myGamma;
};
