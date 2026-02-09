#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepData_SelectInt.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_CString.hpp>
#include <Standard_Integer.hpp>

enum StepVisual_NullStyle
{
  StepVisual_Null
};

class StepVisual_NullStyleMember : public StepData_SelectInt
{

public:
  Standard_EXPORT StepVisual_NullStyleMember();

  bool HasName() const override { return true; }

  const char* Name() const override { return "NULL_STYLE"; }

  bool SetName(const char*) override { return true; }

  int Kind() const override { return 4; }

  Standard_EXPORT const char* EnumText() const override;

  Standard_EXPORT void SetEnumText(const int theValue, const char* theText) override;

  Standard_EXPORT void SetValue(const StepVisual_NullStyle theValue);

  Standard_EXPORT StepVisual_NullStyle Value() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_NullStyleMember, StepData_SelectInt)
};
