#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepFEA_FeaParametricPoint;

class StepFEA_CurveElementLocation : public Standard_Transient
{

public:
  Standard_EXPORT StepFEA_CurveElementLocation();

  Standard_EXPORT void Init(const occ::handle<StepFEA_FeaParametricPoint>& aCoordinate);

  Standard_EXPORT occ::handle<StepFEA_FeaParametricPoint> Coordinate() const;

  Standard_EXPORT void SetCoordinate(const occ::handle<StepFEA_FeaParametricPoint>& Coordinate);

  DEFINE_STANDARD_RTTIEXT(StepFEA_CurveElementLocation, Standard_Transient)

private:
  occ::handle<StepFEA_FeaParametricPoint> theCoordinate;
};
