#include <StepDimTol_SimpleDatumReferenceModifierMember.hpp>
#include <StepData_EnumTool.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_SimpleDatumReferenceModifierMember, StepData_SelectInt)

static StepData_EnumTool tool(".ANY_CROSS_SECTION.",
                              ".ANY_LONGITUDINAL_SECTION.",
                              ".BASIC.",
                              ".CONTACTING_FEATURE.",
                              ".DEGREE_OF_FREEDOM_CONSTRAINT_U.",
                              ".DEGREE_OF_FREEDOM_CONSTRAINT_V.",
                              ".DEGREE_OF_FREEDOM_CONSTRAINT_W.",
                              ".DEGREE_OF_FREEDOM_CONSTRAINT_X.",
                              ".DEGREE_OF_FREEDOM_CONSTRAINT_Y.",
                              ".DEGREE_OF_FREEDOM_CONSTRAINT_Z.",
                              ".DISTANCE_VARIABLE.",
                              ".FREE_STATE.",
                              ".LEAST_MATERIAL_REQUIREMENT.",
                              ".LINE.",
                              ".MAJOR_DIAMETER.",
                              ".MAXIMUM_MATERIAL_REQUIREMENT.",
                              ".MINOR_DIAMETER.",
                              ".ORIENTATION.",
                              ".PITCH_DIAMETER.",
                              ".PLANE.",
                              ".POINT.",
                              ".TRANSLATION.");

//=================================================================================================

StepDimTol_SimpleDatumReferenceModifierMember::StepDimTol_SimpleDatumReferenceModifierMember() =
  default;

//=================================================================================================

const char* StepDimTol_SimpleDatumReferenceModifierMember::EnumText() const
{
  return tool.Text(Int()).ToCString();
}

//=================================================================================================

void StepDimTol_SimpleDatumReferenceModifierMember::SetEnumText(const int /*theValue*/,
                                                                const char* theText)
{
  int aVal = tool.Value(theText);
  if (aVal >= 0)
    SetInt(aVal);
}

//=================================================================================================

void StepDimTol_SimpleDatumReferenceModifierMember::SetValue(
  const StepDimTol_SimpleDatumReferenceModifier theValue)
{
  SetInt(int(theValue));
}

//=================================================================================================

StepDimTol_SimpleDatumReferenceModifier StepDimTol_SimpleDatumReferenceModifierMember::Value() const
{
  return StepDimTol_SimpleDatumReferenceModifier(Int());
}
