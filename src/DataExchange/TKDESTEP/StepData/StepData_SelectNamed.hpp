#pragma once

#include <Standard.hpp>

#include <TCollection_AsciiString.hpp>
#include <StepData_Field.hpp>
#include <StepData_SelectMember.hpp>
#include <Standard_CString.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>

class StepData_SelectNamed : public StepData_SelectMember
{

public:
  Standard_EXPORT StepData_SelectNamed();

  Standard_EXPORT bool HasName() const override;

  Standard_EXPORT const char* Name() const override;

  Standard_EXPORT bool SetName(const char* name) override;

  Standard_EXPORT const StepData_Field& Field() const;

  Standard_EXPORT StepData_Field& CField();

  Standard_EXPORT int Kind() const override;

  Standard_EXPORT void SetKind(const int kind) override;

  Standard_EXPORT int Int() const override;

  Standard_EXPORT void SetInt(const int val) override;

  Standard_EXPORT double Real() const override;

  Standard_EXPORT void SetReal(const double val) override;

  Standard_EXPORT const char* String() const override;

  Standard_EXPORT void SetString(const char* val) override;

  DEFINE_STANDARD_RTTIEXT(StepData_SelectNamed, StepData_SelectMember)

private:
  TCollection_AsciiString thename;
  StepData_Field          theval;
};
