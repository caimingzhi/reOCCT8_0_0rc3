#include <Standard_Transient.hpp>
#include <StepData_SelectMember.hpp>
#include <StepElement_CurveElementFreedom.hpp>
#include <StepElement_CurveElementFreedomMember.hpp>
#include <TCollection_HAsciiString.hpp>

static const char* anEnum = "ENUMERATED_CURVE_ELEMENT_FREEDOM";
static const char* anApp  = "APPLICATION_DEFINED_DEGREE_OF_FREEDOM";

//=================================================================================================

StepElement_CurveElementFreedom::StepElement_CurveElementFreedom() = default;

//=================================================================================================

int StepElement_CurveElementFreedom::CaseNum(const occ::handle<Standard_Transient>& /*ent*/) const
{
  return 0;
}

//=================================================================================================

int StepElement_CurveElementFreedom::CaseMem(const occ::handle<StepData_SelectMember>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->Matches(anEnum))
    return 1;
  else if (ent->Matches(anApp))
    return 2;
  else
    return 0;
}

//=================================================================================================

occ::handle<StepData_SelectMember> StepElement_CurveElementFreedom::NewMember() const
{
  return new StepElement_CurveElementFreedomMember;
}

//=================================================================================================

void StepElement_CurveElementFreedom::SetEnumeratedCurveElementFreedom(
  const StepElement_EnumeratedCurveElementFreedom val)
{
  occ::handle<StepElement_CurveElementFreedomMember> SelMem =
    occ::down_cast<StepElement_CurveElementFreedomMember>(Value());
  if (SelMem.IsNull())
    return;
  occ::handle<TCollection_HAsciiString> name =
    new TCollection_HAsciiString("ENUMERATED_CURVE_ELEMENT_FREEDOM");
  SelMem->SetName(name->ToCString());
  SelMem->SetEnum((int)val);
}

//=================================================================================================

StepElement_EnumeratedCurveElementFreedom StepElement_CurveElementFreedom::
  EnumeratedCurveElementFreedom() const
{
  occ::handle<StepElement_CurveElementFreedomMember> SelMem =
    occ::down_cast<StepElement_CurveElementFreedomMember>(Value());
  if (SelMem.IsNull())
    return StepElement_None;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString;
  name->AssignCat(SelMem->Name());
  occ::handle<TCollection_HAsciiString> nameitem =
    new TCollection_HAsciiString("ENUMERATED_CURVE_ELEMENT_FREEDOM");
  if (name->IsDifferent(nameitem))
    return StepElement_None;
  int                                       numit = SelMem->Enum();
  StepElement_EnumeratedCurveElementFreedom val;
  switch (numit)
  {
    case 1:
      val = StepElement_XTranslation;
      break;
    case 2:
      val = StepElement_YTranslation;
      break;
    case 3:
      val = StepElement_ZTranslation;
      break;
    case 4:
      val = StepElement_XRotation;
      break;
    case 5:
      val = StepElement_YRotation;
      break;
    case 6:
      val = StepElement_ZRotation;
      break;
    case 7:
      val = StepElement_Warp;
      break;
    case 8:
      val = StepElement_None;
      break;
    default:
      return StepElement_None;
      break;
  }
  return val;
}

//=================================================================================================

void StepElement_CurveElementFreedom::SetApplicationDefinedDegreeOfFreedom(
  const occ::handle<TCollection_HAsciiString>& val)
{
  occ::handle<StepElement_CurveElementFreedomMember> SelMem =
    occ::down_cast<StepElement_CurveElementFreedomMember>(Value());
  if (SelMem.IsNull())
    return;
  occ::handle<TCollection_HAsciiString> name =
    new TCollection_HAsciiString("APPLICATION_DEFINED_DEGREE_OF_FREEDOM");
  SelMem->SetName(name->ToCString());
  SelMem->SetString(val->ToCString());
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepElement_CurveElementFreedom::
  ApplicationDefinedDegreeOfFreedom() const
{
  occ::handle<StepElement_CurveElementFreedomMember> SelMem =
    occ::down_cast<StepElement_CurveElementFreedomMember>(Value());
  if (SelMem.IsNull())
    return nullptr;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString;
  name->AssignCat(SelMem->Name());
  occ::handle<TCollection_HAsciiString> nameitem =
    new TCollection_HAsciiString("APPLICATION_DEFINED_DEGREE_OF_FREEDOM");
  if (name->IsDifferent(nameitem))
    return nullptr;
  occ::handle<TCollection_HAsciiString> val = new TCollection_HAsciiString;
  val->AssignCat(SelMem->String());
  return val;
}
