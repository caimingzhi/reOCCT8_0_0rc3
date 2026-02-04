#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>

//! Class for using units variables
class StepData_Factors
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor
  Standard_EXPORT StepData_Factors();

  //! Initializes the 3 factors for the conversion of units
  Standard_EXPORT void InitializeFactors(const double theLengthFactor,
                                         const double thePlaneAngleFactor,
                                         const double theSolidAngleFactor);

  //! Sets length unit for current transfer process
  Standard_EXPORT void SetCascadeUnit(const double theUnit);

  //! Returns length unit for current transfer process (mm by default)
  Standard_EXPORT double CascadeUnit() const;

  //! Returns transient length factor for scaling of shapes
  //! at one stage of transfer process
  Standard_EXPORT double LengthFactor() const;

  //! Returns transient plane angle factor for conversion of angles
  //! at one stage of transfer process
  Standard_EXPORT double PlaneAngleFactor() const;

  //! Returns transient solid angle factor for conversion of angles
  //! at one stage of transfer process
  Standard_EXPORT double SolidAngleFactor() const;

  //! Returns transient factor radian degree for conversion of angles
  //! at one stage of transfer process
  Standard_EXPORT double FactorRadianDegree() const;

  //! Returns transient factor degree radian for conversion of angles
  //! at one stage of transfer process
  Standard_EXPORT double FactorDegreeRadian() const;

private:
  double myLengthFactor;
  double myPlaneAngleFactor;
  double mySolidAngleFactor;
  double myFactRD;
  double myFactDR;
  double myCascadeUnit;
};

