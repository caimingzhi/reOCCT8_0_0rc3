#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepData_SelectMember;
class StepGeom_CartesianPoint;

class StepGeom_TrimmingSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepGeom_TrimmingSelect();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepData_SelectMember> NewMember() const override;

  Standard_EXPORT int CaseMem(const occ::handle<StepData_SelectMember>& ent) const override;

  Standard_EXPORT occ::handle<StepGeom_CartesianPoint> CartesianPoint() const;

  Standard_EXPORT void SetParameterValue(const double aParameterValue);

  Standard_EXPORT double ParameterValue() const;
};
