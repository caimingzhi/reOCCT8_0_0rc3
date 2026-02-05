#include <Standard_Transient.hpp>
#include <StepData_SelectMember.hpp>
#include <StepElement_MeasureOrUnspecifiedValue.hpp>
#include <StepElement_MeasureOrUnspecifiedValueMember.hpp>
#include <TCollection_HAsciiString.hpp>

static const char* aCDM = "CONTEXT_DEPENDENT_MEASURE";
static const char* anUV = "UNSPECIFIED_VALUE";

//=================================================================================================

StepElement_MeasureOrUnspecifiedValue::StepElement_MeasureOrUnspecifiedValue() = default;

//=================================================================================================

int StepElement_MeasureOrUnspecifiedValue::CaseNum(
  const occ::handle<Standard_Transient>& /*ent*/) const
{
  return 0;
}

//=================================================================================================

int StepElement_MeasureOrUnspecifiedValue::CaseMem(
  const occ::handle<StepData_SelectMember>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->Matches(aCDM))
    return 1;
  else if (ent->Matches(anUV))
    return 2;
  else
    return 0;
}

//=================================================================================================

occ::handle<StepData_SelectMember> StepElement_MeasureOrUnspecifiedValue::NewMember() const
{
  return new StepElement_MeasureOrUnspecifiedValueMember;
}

//=================================================================================================

void StepElement_MeasureOrUnspecifiedValue::SetContextDependentMeasure(const double val)
{
  occ::handle<StepElement_MeasureOrUnspecifiedValueMember> SelMem =
    occ::down_cast<StepElement_MeasureOrUnspecifiedValueMember>(Value());
  if (SelMem.IsNull())
    return;
  occ::handle<TCollection_HAsciiString> name =
    new TCollection_HAsciiString("CONTEXT_DEPENDENT_MEASURE");
  SelMem->SetName(name->ToCString());
  SelMem->SetReal(val);
}

//=================================================================================================

double StepElement_MeasureOrUnspecifiedValue::ContextDependentMeasure() const
{
  occ::handle<StepElement_MeasureOrUnspecifiedValueMember> SelMem =
    occ::down_cast<StepElement_MeasureOrUnspecifiedValueMember>(Value());
  if (SelMem.IsNull())
    return 0;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString;
  name->AssignCat(SelMem->Name());
  occ::handle<TCollection_HAsciiString> nameitem =
    new TCollection_HAsciiString("CONTEXT_DEPENDENT_MEASURE");
  if (name->IsDifferent(nameitem))
    return 0;
  double val = SelMem->Real();
  return val;
}

//=================================================================================================

void StepElement_MeasureOrUnspecifiedValue::SetUnspecifiedValue(
  const StepElement_UnspecifiedValue val)
{
  occ::handle<StepElement_MeasureOrUnspecifiedValueMember> SelMem =
    occ::down_cast<StepElement_MeasureOrUnspecifiedValueMember>(Value());
  if (SelMem.IsNull())
    return;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("UNSPECIFIED_VALUE");
  SelMem->SetName(name->ToCString());
  SelMem->SetEnum((int)val);
}

//=================================================================================================

StepElement_UnspecifiedValue StepElement_MeasureOrUnspecifiedValue::UnspecifiedValue() const
{
  occ::handle<StepElement_MeasureOrUnspecifiedValueMember> SelMem =
    occ::down_cast<StepElement_MeasureOrUnspecifiedValueMember>(Value());
  if (SelMem.IsNull())
    return StepElement_Unspecified;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString;
  name->AssignCat(SelMem->Name());
  occ::handle<TCollection_HAsciiString> nameitem =
    new TCollection_HAsciiString("UNSPECIFIED_VALUE");
  if (name->IsDifferent(nameitem))
    return StepElement_Unspecified;
  int                          numit = SelMem->Enum();
  StepElement_UnspecifiedValue val;
  switch (numit)
  {
    case 1:
      val = StepElement_Unspecified;
      break;
    default:
      return StepElement_Unspecified;
      break;
  }
  return val;
}
