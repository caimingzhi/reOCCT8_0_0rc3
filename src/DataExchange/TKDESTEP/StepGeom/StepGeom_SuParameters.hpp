#pragma once

#include <Standard.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>

#include <TCollection_HAsciiString.hpp>

//! Representation of STEP entity SuParameters
class StepGeom_SuParameters : public StepGeom_GeometricRepresentationItem
{
public:
  //! default constructor
  Standard_EXPORT StepGeom_SuParameters();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
                            const double                                 theA,
                            const double                                 theAlpha,
                            const double                                 theB,
                            const double                                 theBeta,
                            const double                                 theC,
                            const double                                 theGamma);

  //! Returns field A
  Standard_EXPORT double A() const;
  //! Sets field A
  Standard_EXPORT void SetA(const double theA);

  //! Returns field Alpha
  Standard_EXPORT double Alpha() const;
  //! Sets field Alpha
  Standard_EXPORT void SetAlpha(const double theAlpha);

  //! Returns field B
  Standard_EXPORT double B() const;
  //! Sets field B
  Standard_EXPORT void SetB(const double theB);

  //! Returns field Beta
  Standard_EXPORT double Beta() const;
  //! Sets field Beta
  Standard_EXPORT void SetBeta(const double theBeta);

  //! Returns field C
  Standard_EXPORT double C() const;
  //! Sets field C
  Standard_EXPORT void SetC(const double theC);

  //! Returns field Gamma
  Standard_EXPORT double Gamma() const;
  //! Sets field Gamma
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
