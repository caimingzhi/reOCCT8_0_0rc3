#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <StepData_SelectReal.hpp>

//! for Select MeasureValue, i.e. :
//! length_measure,time_measure,plane_angle_measure,
//! solid_angle_measure,ratio_measure,parameter_value,
//! context_dependent_measure,positive_length_measure,
//! positive_plane_angle_measure,positive_ratio_measure,
//! area_measure,volume_measure, count_measure
class StepBasic_MeasureValueMember : public StepData_SelectReal
{

public:
  Standard_EXPORT StepBasic_MeasureValueMember();

  Standard_EXPORT bool HasName() const override;

  Standard_EXPORT const char* Name() const override;

  Standard_EXPORT bool SetName(const char* name) override;

  DEFINE_STANDARD_RTTIEXT(StepBasic_MeasureValueMember, StepData_SelectReal)

private:
  int thecase;
};
