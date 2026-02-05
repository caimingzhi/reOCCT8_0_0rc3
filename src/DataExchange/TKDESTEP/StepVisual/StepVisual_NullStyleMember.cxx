#include <StepVisual_NullStyleMember.hpp>
#include <StepData_EnumTool.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_NullStyleMember, StepData_SelectInt)

static StepData_EnumTool tool(".NULL.");

//=================================================================================================

StepVisual_NullStyleMember::StepVisual_NullStyleMember() = default;

//=================================================================================================

const char* StepVisual_NullStyleMember::EnumText() const
{
  return tool.Text(Int()).ToCString();
}

//=================================================================================================

void StepVisual_NullStyleMember::SetEnumText(const int /*theValue*/, const char* theText)
{
  int aVal = tool.Value(theText);
  if (aVal >= 0)
    SetInt(aVal);
}

//=================================================================================================

void StepVisual_NullStyleMember::SetValue(const StepVisual_NullStyle theValue)
{
  SetInt(int(theValue));
}

//=================================================================================================

StepVisual_NullStyle StepVisual_NullStyleMember::Value() const
{
  return StepVisual_NullStyle(Int());
}
