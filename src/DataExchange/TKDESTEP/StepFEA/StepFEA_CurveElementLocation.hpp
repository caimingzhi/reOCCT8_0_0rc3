#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepFEA_FeaParametricPoint;

//! Representation of STEP entity CurveElementLocation
class StepFEA_CurveElementLocation : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_CurveElementLocation();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<StepFEA_FeaParametricPoint>& aCoordinate);

  //! Returns field Coordinate
  Standard_EXPORT occ::handle<StepFEA_FeaParametricPoint> Coordinate() const;

  //! Set field Coordinate
  Standard_EXPORT void SetCoordinate(const occ::handle<StepFEA_FeaParametricPoint>& Coordinate);

  DEFINE_STANDARD_RTTIEXT(StepFEA_CurveElementLocation, Standard_Transient)

private:
  occ::handle<StepFEA_FeaParametricPoint> theCoordinate;
};

