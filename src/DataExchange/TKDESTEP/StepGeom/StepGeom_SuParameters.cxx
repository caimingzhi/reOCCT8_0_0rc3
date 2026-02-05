// Created on : Sat May 02 12:41:14 2020

#include <StepGeom_SuParameters.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_SuParameters, StepGeom_GeometricRepresentationItem)

//=================================================================================================

StepGeom_SuParameters::StepGeom_SuParameters() = default;

//=================================================================================================

void StepGeom_SuParameters::Init(
  const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
  const double                                 theA,
  const double                                 theAlpha,
  const double                                 theB,
  const double                                 theBeta,
  const double                                 theC,
  const double                                 theGamma)
{
  StepGeom_GeometricRepresentationItem::Init(theRepresentationItem_Name);

  myA = theA;

  myAlpha = theAlpha;

  myB = theB;

  myBeta = theBeta;

  myC = theC;

  myGamma = theGamma;
}

//=================================================================================================

double StepGeom_SuParameters::A() const
{
  return myA;
}

//=================================================================================================

void StepGeom_SuParameters::SetA(const double theA)
{
  myA = theA;
}

//=================================================================================================

double StepGeom_SuParameters::Alpha() const
{
  return myAlpha;
}

//=================================================================================================

void StepGeom_SuParameters::SetAlpha(const double theAlpha)
{
  myAlpha = theAlpha;
}

//=================================================================================================

double StepGeom_SuParameters::B() const
{
  return myB;
}

//=================================================================================================

void StepGeom_SuParameters::SetB(const double theB)
{
  myB = theB;
}

//=================================================================================================

double StepGeom_SuParameters::Beta() const
{
  return myBeta;
}

//=================================================================================================

void StepGeom_SuParameters::SetBeta(const double theBeta)
{
  myBeta = theBeta;
}

//=================================================================================================

double StepGeom_SuParameters::C() const
{
  return myC;
}

//=================================================================================================

void StepGeom_SuParameters::SetC(const double theC)
{
  myC = theC;
}

//=================================================================================================

double StepGeom_SuParameters::Gamma() const
{
  return myGamma;
}

//=================================================================================================

void StepGeom_SuParameters::SetGamma(const double theGamma)
{
  myGamma = theGamma;
}
