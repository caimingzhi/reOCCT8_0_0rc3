#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>

class StepData_Factors
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepData_Factors();

  Standard_EXPORT void InitializeFactors(const double theLengthFactor,
                                         const double thePlaneAngleFactor,
                                         const double theSolidAngleFactor);

  Standard_EXPORT void SetCascadeUnit(const double theUnit);

  Standard_EXPORT double CascadeUnit() const;

  Standard_EXPORT double LengthFactor() const;

  Standard_EXPORT double PlaneAngleFactor() const;

  Standard_EXPORT double SolidAngleFactor() const;

  Standard_EXPORT double FactorRadianDegree() const;

  Standard_EXPORT double FactorDegreeRadian() const;

private:
  double myLengthFactor;
  double myPlaneAngleFactor;
  double mySolidAngleFactor;
  double myFactRD;
  double myFactDR;
  double myCascadeUnit;
};
