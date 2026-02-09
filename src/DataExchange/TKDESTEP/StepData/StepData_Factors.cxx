

#include <StepData_Factors.hpp>

StepData_Factors::StepData_Factors()
    : myLengthFactor(1.),
      myPlaneAngleFactor(1.),
      mySolidAngleFactor(1.),
      myFactRD(1.),
      myFactDR(1.),
      myCascadeUnit(1.)
{
}

void StepData_Factors::InitializeFactors(const double theLengthFactor,
                                         const double thePlaneAngleFactor,
                                         const double theSolidAngleFactor)
{
  myLengthFactor     = theLengthFactor;
  myPlaneAngleFactor = thePlaneAngleFactor;
  mySolidAngleFactor = theSolidAngleFactor;
  myFactRD           = 1. / thePlaneAngleFactor;
  myFactDR           = thePlaneAngleFactor;
}

double StepData_Factors::LengthFactor() const
{
  return myLengthFactor;
}

double StepData_Factors::PlaneAngleFactor() const
{
  return myPlaneAngleFactor;
}

double StepData_Factors::SolidAngleFactor() const
{
  return mySolidAngleFactor;
}

double StepData_Factors::FactorRadianDegree() const
{
  return myFactRD;
}

double StepData_Factors::FactorDegreeRadian() const
{
  return myFactDR;
}

void StepData_Factors::SetCascadeUnit(const double theUnit)
{
  myCascadeUnit = theUnit;
}

double StepData_Factors::CascadeUnit() const
{
  return myCascadeUnit;
}
