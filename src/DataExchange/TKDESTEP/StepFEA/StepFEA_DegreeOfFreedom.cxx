#include <Standard_Transient.hpp>
#include <StepData_SelectMember.hpp>
#include <StepFEA_DegreeOfFreedom.hpp>
#include <StepFEA_DegreeOfFreedomMember.hpp>
#include <TCollection_HAsciiString.hpp>

//=================================================================================================

StepFEA_DegreeOfFreedom::StepFEA_DegreeOfFreedom() = default;

//=================================================================================================

int StepFEA_DegreeOfFreedom::CaseNum(const occ::handle<Standard_Transient>& /*ent*/) const
{
  return 0;
}

//=================================================================================================

int StepFEA_DegreeOfFreedom::CaseMem(const occ::handle<StepData_SelectMember>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->Matches("ENUMERATED_DEGREE_OF_FREEDOM"))
    return 1;
  else if (ent->Matches("APPLICATION_DEFINED_DEGREE_OF_FREEDOM"))
    return 2;
  else
    return 0;
}

//=================================================================================================

occ::handle<StepData_SelectMember> StepFEA_DegreeOfFreedom::NewMember() const
{
  return new StepFEA_DegreeOfFreedomMember;
}

//=================================================================================================

void StepFEA_DegreeOfFreedom::SetEnumeratedDegreeOfFreedom(
  const StepFEA_EnumeratedDegreeOfFreedom val)
{
  occ::handle<StepFEA_DegreeOfFreedomMember> SelMem =
    occ::down_cast<StepFEA_DegreeOfFreedomMember>(Value());
  if (SelMem.IsNull())
    return;
  occ::handle<TCollection_HAsciiString> name =
    new TCollection_HAsciiString("ENUMERATED_DEGREE_OF_FREEDOM");
  SelMem->SetName(name->ToCString());
  SelMem->SetEnum((int)val);
}

//=================================================================================================

StepFEA_EnumeratedDegreeOfFreedom StepFEA_DegreeOfFreedom::EnumeratedDegreeOfFreedom() const
{
  occ::handle<StepFEA_DegreeOfFreedomMember> SelMem =
    occ::down_cast<StepFEA_DegreeOfFreedomMember>(Value());
  if (SelMem.IsNull())
    return StepFEA_XTranslation;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString;
  name->AssignCat(SelMem->Name());
  occ::handle<TCollection_HAsciiString> nameitem =
    new TCollection_HAsciiString("ENUMERATED_DEGREE_OF_FREEDOM");
  if (name->IsDifferent(nameitem))
    return StepFEA_XTranslation;
  int                               numit = SelMem->Enum();
  StepFEA_EnumeratedDegreeOfFreedom val;
  switch (numit)
  {
    case 1:
      val = StepFEA_XTranslation;
      break;
      //  case 2 : val = StepElement_YTranslation; break;
      //  case 3 : val = StepElement_ZTranslation; break;
      //  case 4 : val = StepElement_XRotation; break;
      //  case 5 : val = StepElement_YRotation; break;
      //  case 6 : val = StepElement_ZRotation; break;
      //  case 7 : val = StepElement_Warp; break;
      //  case 8 : val = StepElement_None; break;
    default:
      return StepFEA_XTranslation;
      break;
  }
  return val;
}

//=================================================================================================

void StepFEA_DegreeOfFreedom::SetApplicationDefinedDegreeOfFreedom(
  const occ::handle<TCollection_HAsciiString>& val)
{
  occ::handle<StepFEA_DegreeOfFreedomMember> SelMem =
    occ::down_cast<StepFEA_DegreeOfFreedomMember>(Value());
  if (SelMem.IsNull())
    return;
  occ::handle<TCollection_HAsciiString> name =
    new TCollection_HAsciiString("APPLICATION_DEFINED_DEGREE_OF_FREEDOM");
  SelMem->SetName(name->ToCString());
  SelMem->SetString(val->ToCString());
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepFEA_DegreeOfFreedom::ApplicationDefinedDegreeOfFreedom()
  const
{
  occ::handle<StepFEA_DegreeOfFreedomMember> SelMem =
    occ::down_cast<StepFEA_DegreeOfFreedomMember>(Value());
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
