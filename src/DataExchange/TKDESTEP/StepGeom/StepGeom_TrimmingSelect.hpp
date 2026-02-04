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

  //! Returns a TrimmingSelect SelectType
  Standard_EXPORT StepGeom_TrimmingSelect();

  //! Recognizes a TrimmingSelect Kind Entity that is :
  //! 1 -> CartesianPoint
  //! 0 else (i.e. Real)
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns a TrimmingMember (for PARAMETER_VALUE) as preferred
  Standard_EXPORT occ::handle<StepData_SelectMember> NewMember() const override;

  //! Recognizes a SelectMember as Real, named as PARAMETER_VALUE
  //! 1 -> ParameterValue i.e. Real
  //! 0 else (i.e. Entity)
  Standard_EXPORT int CaseMem(const occ::handle<StepData_SelectMember>& ent) const override;

  //! returns Value as a CartesianPoint (Null if another type)
  Standard_EXPORT occ::handle<StepGeom_CartesianPoint> CartesianPoint() const;

  //! sets the ParameterValue as Real
  Standard_EXPORT void SetParameterValue(const double aParameterValue);

  //! returns Value as a Real (0.0 if not a Real)
  Standard_EXPORT double ParameterValue() const;
};

