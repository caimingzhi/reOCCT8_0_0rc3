#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <StepData_SelectMember.hpp>

//! A SelectInt is a SelectMember specialised for a basic integer
//! type in a select which also accepts entities : this one has
//! NO NAME.
//! For a named select, see SelectNamed
class StepData_SelectInt : public StepData_SelectMember
{

public:
  Standard_EXPORT StepData_SelectInt();

  Standard_EXPORT int Kind() const override;

  Standard_EXPORT void SetKind(const int kind) override;

  Standard_EXPORT int Int() const override;

  Standard_EXPORT void SetInt(const int val) override;

  DEFINE_STANDARD_RTTIEXT(StepData_SelectInt, StepData_SelectMember)

private:
  int thekind;
  int theval;
};

