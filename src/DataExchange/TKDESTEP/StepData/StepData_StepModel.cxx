

#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_GeneralLib.hpp>
#include <Interface_GeneralModule.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <StepData.hpp>
#include <StepData_Protocol.hpp>
#include <StepData_StepModel.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_HAsciiString.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(StepData_StepModel, Interface_InterfaceModel)

StepData_StepModel::StepData_StepModel() = default;

occ::handle<Standard_Transient> StepData_StepModel::Entity(const int num) const
{
  return Value(num);
}

void StepData_StepModel::GetFromAnother(const occ::handle<Interface_InterfaceModel>& other)
{
  theheader.Clear();
  DeclareAndCast(StepData_StepModel, another, other);
  if (another.IsNull())
    return;
  Interface_EntityIterator iter = another->Header();

  Interface_CopyTool TC(this, StepData::HeaderProtocol());
  for (; iter.More(); iter.Next())
  {
    occ::handle<Standard_Transient> newhead;
    if (!TC.Copy(iter.Value(), newhead, false, false))
      continue;
    if (!newhead.IsNull())
      theheader.Append(newhead);
  }
}

occ::handle<Interface_InterfaceModel> StepData_StepModel::NewEmptyModel() const
{
  return new StepData_StepModel;
}

Interface_EntityIterator StepData_StepModel::Header() const
{
  Interface_EntityIterator iter;
  theheader.FillIterator(iter);
  return iter;
}

bool StepData_StepModel::HasHeaderEntity(const occ::handle<Standard_Type>& atype) const
{
  return (theheader.NbTypedEntities(atype) == 1);
}

occ::handle<Standard_Transient> StepData_StepModel::HeaderEntity(
  const occ::handle<Standard_Type>& atype) const
{
  return theheader.TypedEntity(atype);
}

void StepData_StepModel::ClearHeader()
{
  theheader.Clear();
}

void StepData_StepModel::AddHeaderEntity(const occ::handle<Standard_Transient>& ent)
{
  theheader.Append(ent);
}

void StepData_StepModel::VerifyCheck(occ::handle<Interface_Check>& ach) const
{
  Interface_GeneralLib                 lib(StepData::HeaderProtocol());
  occ::handle<StepData_StepModel>      me(this);
  occ::handle<Interface_Protocol>      aHP = StepData::HeaderProtocol();
  Interface_ShareTool                  sh(me, aHP);
  occ::handle<Interface_GeneralModule> module;
  int                                  CN;
  for (Interface_EntityIterator iter = Header(); iter.More(); iter.Next())
  {
    const occ::handle<Standard_Transient>& head = iter.Value();
    if (!lib.Select(head, module, CN))
      continue;
    module->CheckCase(CN, head, sh, ach);
  }
}

void StepData_StepModel::DumpHeader(Standard_OStream& S, const int) const
{

  occ::handle<StepData_Protocol> stepro = StepData::HeaderProtocol();
  bool                           iapro  = !stepro.IsNull();
  if (!iapro)
    S << " -- WARNING : StepModel DumpHeader, Protocol not defined\n";

  Interface_EntityIterator iter = Header();
  int                      nb   = iter.NbEntities();
  S << " --  Step Model Header : " << iter.NbEntities() << " Entities :\n";
  for (iter.Start(); iter.More(); iter.Next())
  {
    S << "  " << iter.Value()->DynamicType()->Name() << "\n";
  }
  if (!iapro || nb == 0)
    return;
  S << " --  --        STEP MODEL    HEADER  CONTENT      --  --" << "\n";
  S << " --   Dumped with Protocol : " << stepro->DynamicType()->Name() << "   --\n";

  occ::handle<StepData_StepModel> me(this);
  StepData_StepWriter             SW(me);
  SW.SendModel(stepro, true);
  SW.Print(S);
}

void StepData_StepModel::ClearLabels()
{
  theidnums.Nullify();
}

void StepData_StepModel::SetIdentLabel(const occ::handle<Standard_Transient>& ent, const int ident)
{
  int num = Number(ent);
  if (!num)
    return;
  int nbEnt = NbEntities();

  if (theidnums.IsNull())
  {
    theidnums = new NCollection_HArray1<int>(1, nbEnt);
    theidnums->Init(0);
  }

  else if (nbEnt > theidnums->Length())
  {
    int                                   prevLength = theidnums->Length();
    occ::handle<NCollection_HArray1<int>> idnums1    = new NCollection_HArray1<int>(1, nbEnt);
    idnums1->Init(0);

    int k = 1;
    for (; k <= prevLength; k++)
      idnums1->SetValue(k, theidnums->Value(k));
    theidnums = idnums1;
  }
  theidnums->SetValue(num, ident);
}

int StepData_StepModel::IdentLabel(const occ::handle<Standard_Transient>& ent) const
{
  if (theidnums.IsNull())
    return 0;
  int num = Number(ent);
  return (!num ? 0 : theidnums->Value(num));
}

void StepData_StepModel::PrintLabel(const occ::handle<Standard_Transient>& ent,
                                    Standard_OStream&                      S) const
{
  int num = (theidnums.IsNull() ? 0 : Number(ent));
  int nid = (!num ? 0 : theidnums->Value(num));
  if (nid > 0)
    S << "#" << nid;
  else if (num > 0)
    S << "(#" << num << ")";
  else
    S << "(#0..)";
}

occ::handle<TCollection_HAsciiString> StepData_StepModel::StringLabel(
  const occ::handle<Standard_Transient>& ent) const
{
  occ::handle<TCollection_HAsciiString> label;
  char                                  text[20];
  int                                   num = (theidnums.IsNull() ? 0 : Number(ent));
  int                                   nid = (!num ? 0 : theidnums->Value(num));

  if (nid > 0)
    Sprintf(text, "#%d", nid);
  else if (num > 0)
    Sprintf(text, "(#%d)", num);
  else
    Sprintf(text, "(#0..)");

  label = new TCollection_HAsciiString(text);
  return label;
}

void StepData_StepModel::SetLocalLengthUnit(const double theUnit)
{
  myLocalLengthUnit       = theUnit;
  myReadUnitIsInitialized = true;
}

double StepData_StepModel::LocalLengthUnit() const
{
  return myLocalLengthUnit;
}

void StepData_StepModel::SetWriteLengthUnit(const double theUnit)
{
  myWriteUnit              = theUnit;
  myWriteUnitIsInitialized = true;
}

double StepData_StepModel::WriteLengthUnit() const
{

  if (!myWriteUnitIsInitialized)
  {
    myWriteUnitIsInitialized = true;
    switch (InternalParameters.WriteUnit)
    {
      case UnitsMethods_LengthUnit_Inch:
        myWriteUnit = 25.4;
        break;
      case UnitsMethods_LengthUnit_Millimeter:
        myWriteUnit = 1.;
        break;
      case UnitsMethods_LengthUnit_Foot:
        myWriteUnit = 304.8;
        break;
      case UnitsMethods_LengthUnit_Mile:
        myWriteUnit = 1609344.0;
        break;
      case UnitsMethods_LengthUnit_Meter:
        myWriteUnit = 1000.0;
        break;
      case UnitsMethods_LengthUnit_Kilometer:
        myWriteUnit = 1000000.0;
        break;
      case UnitsMethods_LengthUnit_Mil:
        myWriteUnit = 0.0254;
        break;
      case UnitsMethods_LengthUnit_Micron:
        myWriteUnit = 0.001;
        break;
      case UnitsMethods_LengthUnit_Centimeter:
        myWriteUnit = 10.0;
        break;
      case UnitsMethods_LengthUnit_Microinch:
        myWriteUnit = 0.0000254;
        break;
      default:
      {
        myWriteUnitIsInitialized = false;
        GlobalCheck()->AddWarning("Incorrect write.step.unit parameter, use default value");
      }
    }
  }
  return myWriteUnit;
}
