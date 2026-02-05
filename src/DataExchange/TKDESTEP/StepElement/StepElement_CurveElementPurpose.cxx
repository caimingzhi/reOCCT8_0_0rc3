#include <Standard_Transient.hpp>
#include <StepData_SelectMember.hpp>
#include <StepElement_CurveElementPurpose.hpp>
#include <StepElement_CurveElementPurposeMember.hpp>
#include <TCollection_HAsciiString.hpp>

//=================================================================================================

StepElement_CurveElementPurpose::StepElement_CurveElementPurpose() = default;

//=================================================================================================

int StepElement_CurveElementPurpose::CaseNum(const occ::handle<Standard_Transient>& /*ent*/) const
{
  return 0;
}

//=================================================================================================

int StepElement_CurveElementPurpose::CaseMem(const occ::handle<StepData_SelectMember>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->Matches("EnumeratedCurveElementPurpose"))
    return 1;
  else if (ent->Matches("ApplicationDefinedElementPurpose"))
    return 2;
  else
    return 0;
}

//=================================================================================================

occ::handle<StepData_SelectMember> StepElement_CurveElementPurpose::NewMember() const
{
  return new StepElement_CurveElementPurposeMember;
}

//=================================================================================================

void StepElement_CurveElementPurpose::SetEnumeratedCurveElementPurpose(
  const StepElement_EnumeratedCurveElementPurpose val)
{
  occ::handle<StepElement_CurveElementPurposeMember> SelMem =
    occ::down_cast<StepElement_CurveElementPurposeMember>(Value());
  if (SelMem.IsNull())
    return;
  occ::handle<TCollection_HAsciiString> name =
    new TCollection_HAsciiString("ENUMERATED_CURVE_ELEMENT_PURPOSE");
  SelMem->SetName(name->ToCString());
  SelMem->SetEnum((int)val);
}

//=================================================================================================

StepElement_EnumeratedCurveElementPurpose StepElement_CurveElementPurpose::
  EnumeratedCurveElementPurpose() const
{
  occ::handle<StepElement_CurveElementPurposeMember> SelMem =
    occ::down_cast<StepElement_CurveElementPurposeMember>(Value());
  if (SelMem.IsNull())
    return StepElement_Axial;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString;
  name->AssignCat(SelMem->Name());
  occ::handle<TCollection_HAsciiString> nameitem =
    new TCollection_HAsciiString("ENUMERATED_CURVEELEMENT_PURPOSE");
  if (name->IsDifferent(nameitem))
    return StepElement_Axial;
  int                                       numit = SelMem->Enum();
  StepElement_EnumeratedCurveElementPurpose val;
  switch (numit)
  {
    case 1:
      val = StepElement_Axial;
      break;
    case 2:
      val = StepElement_YYBending;
      break;
    case 3:
      val = StepElement_ZZBending;
      break;
    case 4:
      val = StepElement_Torsion;
      break;
    case 5:
      val = StepElement_XYShear;
      break;
    case 6:
      val = StepElement_XZShear;
      break;
    case 7:
      val = StepElement_Warping;
      break;
    default:
      return StepElement_Axial;
      break;
  }
  return val;
}

//=================================================================================================

void StepElement_CurveElementPurpose::SetApplicationDefinedElementPurpose(
  const occ::handle<TCollection_HAsciiString>& val)
{
  occ::handle<StepElement_CurveElementPurposeMember> SelMem =
    occ::down_cast<StepElement_CurveElementPurposeMember>(Value());
  if (SelMem.IsNull())
    return;
  occ::handle<TCollection_HAsciiString> name =
    new TCollection_HAsciiString("APPLICATION_DEFINED_ELEMENT_PURPOSE");
  SelMem->SetName(name->ToCString());
  SelMem->SetString(val->ToCString());
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepElement_CurveElementPurpose::
  ApplicationDefinedElementPurpose() const
{
  occ::handle<StepElement_CurveElementPurposeMember> SelMem =
    occ::down_cast<StepElement_CurveElementPurposeMember>(Value());
  if (SelMem.IsNull())
    return nullptr;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString;
  name->AssignCat(SelMem->Name());
  occ::handle<TCollection_HAsciiString> nameitem =
    new TCollection_HAsciiString("APPLICATION_DEFINED_ELEMENT_PURPOSE");
  if (name->IsDifferent(nameitem))
    return nullptr;
  occ::handle<TCollection_HAsciiString> val = new TCollection_HAsciiString;
  val->AssignCat(SelMem->String());
  return val;
}
