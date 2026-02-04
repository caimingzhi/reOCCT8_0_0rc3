#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_CartesianTransformationOperator.hpp>

//! Added from StepGeom Rev2 to Rev4
class StepGeom_CartesianTransformationOperator2d : public StepGeom_CartesianTransformationOperator
{

public:
  Standard_EXPORT StepGeom_CartesianTransformationOperator2d();

  DEFINE_STANDARD_RTTIEXT(StepGeom_CartesianTransformationOperator2d,
                          StepGeom_CartesianTransformationOperator)
};

