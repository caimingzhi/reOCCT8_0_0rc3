#include <Standard_Transient.hpp>
#include <StepData_SelectMember.hpp>
#include <StepElement_ElementAspect.hpp>
#include <StepElement_ElementAspectMember.hpp>
#include <TCollection_HAsciiString.hpp>

StepElement_ElementAspect::StepElement_ElementAspect() = default;

int StepElement_ElementAspect::CaseNum(const occ::handle<Standard_Transient>&) const
{
  return 0;
}

int StepElement_ElementAspect::CaseMem(const occ::handle<StepData_SelectMember>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->Matches("ELEMENT_VOLUME"))
    return 1;
  else if (ent->Matches("VOLUME_3D_FACE"))
    return 2;
  else if (ent->Matches("VOLUME_2D_FACE"))
    return 3;
  else if (ent->Matches("VOLUME_3D_EDGE"))
    return 4;
  else if (ent->Matches("VOLUME_2D_EDGE"))
    return 5;
  else if (ent->Matches("SURFACE_3D_FACE"))
    return 6;
  else if (ent->Matches("SURFACE_2D_FACE"))
    return 7;
  else if (ent->Matches("SURFACE_3D_EDGE"))
    return 8;
  else if (ent->Matches("SURFACE_2D_EDGE"))
    return 9;
  else if (ent->Matches("CURVE_EDGE"))
    return 10;
  else
    return 0;
}

occ::handle<StepData_SelectMember> StepElement_ElementAspect::NewMember() const
{
  return new StepElement_ElementAspectMember;
}

void StepElement_ElementAspect::SetElementVolume(const StepElement_ElementVolume val)
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("ELEMENT_VOLUME");
  SelMem->SetName(name->ToCString());
  SelMem->SetEnum((int)val);
}

StepElement_ElementVolume StepElement_ElementAspect::ElementVolume() const
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return StepElement_Volume;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString;
  name->AssignCat(SelMem->Name());
  occ::handle<TCollection_HAsciiString> nameitem = new TCollection_HAsciiString("ELEMENT_VOLUME");
  if (name->IsDifferent(nameitem))
    return StepElement_Volume;
  int                       numit = SelMem->Enum();
  StepElement_ElementVolume val;
  switch (numit)
  {
    case 1:
      val = StepElement_Volume;
      break;
    default:
      return StepElement_Volume;
      break;
  }
  return val;
}

void StepElement_ElementAspect::SetVolume3dFace(const int val)
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("VOLUME_3D_FACE");
  SelMem->SetName(name->ToCString());
  SelMem->SetInteger(val);
}

int StepElement_ElementAspect::Volume3dFace() const
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return 0;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString;
  name->AssignCat(SelMem->Name());
  occ::handle<TCollection_HAsciiString> nameitem = new TCollection_HAsciiString("VOLUME_3D_FACE");
  if (name->IsDifferent(nameitem))
    return 0;
  int val = SelMem->Integer();
  return val;
}

void StepElement_ElementAspect::SetVolume2dFace(const int val)
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("VOLUME_2D_FACE");
  SelMem->SetName(name->ToCString());
  SelMem->SetInteger(val);
}

int StepElement_ElementAspect::Volume2dFace() const
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return 0;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString;
  name->AssignCat(SelMem->Name());
  occ::handle<TCollection_HAsciiString> nameitem = new TCollection_HAsciiString("VOLUME_2D_FACE");
  if (name->IsDifferent(nameitem))
    return 0;
  int val = SelMem->Integer();
  return val;
}

void StepElement_ElementAspect::SetVolume3dEdge(const int val)
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("VOLUME_3D_EDGE");
  SelMem->SetName(name->ToCString());
  SelMem->SetInteger(val);
}

int StepElement_ElementAspect::Volume3dEdge() const
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return 0;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString;
  name->AssignCat(SelMem->Name());
  occ::handle<TCollection_HAsciiString> nameitem = new TCollection_HAsciiString("VOLUME_3D_EDGE");
  if (name->IsDifferent(nameitem))
    return 0;
  int val = SelMem->Integer();
  return val;
}

void StepElement_ElementAspect::SetVolume2dEdge(const int val)
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("VOLUME_2D_EDGE");
  SelMem->SetName(name->ToCString());
  SelMem->SetInteger(val);
}

int StepElement_ElementAspect::Volume2dEdge() const
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return 0;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString;
  name->AssignCat(SelMem->Name());
  occ::handle<TCollection_HAsciiString> nameitem = new TCollection_HAsciiString("VOLUME_2D_EDGE");
  if (name->IsDifferent(nameitem))
    return 0;
  int val = SelMem->Integer();
  return val;
}

void StepElement_ElementAspect::SetSurface3dFace(const int val)
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("SURFACE_3D_FACE");
  SelMem->SetName(name->ToCString());
  SelMem->SetInteger(val);
}

int StepElement_ElementAspect::Surface3dFace() const
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return 0;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString;
  name->AssignCat(SelMem->Name());
  occ::handle<TCollection_HAsciiString> nameitem = new TCollection_HAsciiString("SURFACE_3D_FACE");
  if (name->IsDifferent(nameitem))
    return 0;
  int val = SelMem->Integer();
  return val;
}

void StepElement_ElementAspect::SetSurface2dFace(const int val)
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("SURFACE_2D_FACE");
  SelMem->SetName(name->ToCString());
  SelMem->SetInteger(val);
}

int StepElement_ElementAspect::Surface2dFace() const
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return 0;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString;
  name->AssignCat(SelMem->Name());
  occ::handle<TCollection_HAsciiString> nameitem = new TCollection_HAsciiString("SURFACE_2D_FACE");
  if (name->IsDifferent(nameitem))
    return 0;
  int val = SelMem->Integer();
  return val;
}

void StepElement_ElementAspect::SetSurface3dEdge(const int val)
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("SURFACE_3D_EDGE");
  SelMem->SetName(name->ToCString());
  SelMem->SetInteger(val);
}

int StepElement_ElementAspect::Surface3dEdge() const
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return 0;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString;
  name->AssignCat(SelMem->Name());
  occ::handle<TCollection_HAsciiString> nameitem = new TCollection_HAsciiString("SURFACE_3D_EDGE");
  if (name->IsDifferent(nameitem))
    return 0;
  int val = SelMem->Integer();
  return val;
}

void StepElement_ElementAspect::SetSurface2dEdge(const int val)
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("SURFACE_2D_EDGE");
  SelMem->SetName(name->ToCString());
  SelMem->SetInteger(val);
}

int StepElement_ElementAspect::Surface2dEdge() const
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return 0;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString;
  name->AssignCat(SelMem->Name());
  occ::handle<TCollection_HAsciiString> nameitem = new TCollection_HAsciiString("SURFACE_2D_EDGE");
  if (name->IsDifferent(nameitem))
    return 0;
  int val = SelMem->Integer();
  return val;
}

void StepElement_ElementAspect::SetCurveEdge(const StepElement_CurveEdge val)
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("CURVE_EDGE");
  SelMem->SetName(name->ToCString());
  SelMem->SetEnum((int)val);
}

StepElement_CurveEdge StepElement_ElementAspect::CurveEdge() const
{
  occ::handle<StepElement_ElementAspectMember> SelMem =
    occ::down_cast<StepElement_ElementAspectMember>(Value());
  if (SelMem.IsNull())
    return StepElement_ElementEdge;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString;
  name->AssignCat(SelMem->Name());
  occ::handle<TCollection_HAsciiString> nameitem = new TCollection_HAsciiString("CURVE_EDGE");
  if (name->IsDifferent(nameitem))
    return StepElement_ElementEdge;
  int                   numit = SelMem->Enum();
  StepElement_CurveEdge val;
  switch (numit)
  {
    case 1:
      val = StepElement_ElementEdge;
      break;
    default:
      return StepElement_ElementEdge;
      break;
  }
  return val;
}
