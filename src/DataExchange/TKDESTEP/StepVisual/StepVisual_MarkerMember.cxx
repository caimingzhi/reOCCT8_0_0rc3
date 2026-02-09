

#include <StepData_EnumTool.hpp>
#include <StepVisual_MarkerMember.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_MarkerMember, StepData_SelectInt)

static StepData_EnumTool tool(".DOT.",
                              ".X.",
                              ".PLUS.",
                              ".ASTERISK.",
                              ".RING.",
                              ".SQUARE.",
                              ".TRIANGLE.");

StepVisual_MarkerMember::StepVisual_MarkerMember() = default;

bool StepVisual_MarkerMember::HasName() const
{
  return true;
}

const char* StepVisual_MarkerMember::Name() const
{
  return "MARKER_TYPE";
}

bool StepVisual_MarkerMember::SetName(const char*)
{
  return true;
}

const char* StepVisual_MarkerMember::EnumText() const
{
  return tool.Text(Int()).ToCString();
}

void StepVisual_MarkerMember::SetEnumText(const int, const char* text)
{
  int vl = tool.Value(text);
  if (vl >= 0)
    SetInt(vl);
}

void StepVisual_MarkerMember::SetValue(const StepVisual_MarkerType val)
{
  SetInt(int(val));
}

StepVisual_MarkerType StepVisual_MarkerMember::Value() const
{
  return StepVisual_MarkerType(Int());
}
