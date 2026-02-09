

#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_UndefinedContent.hpp>
#include <Standard_Type.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepData_UndefinedEntity.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepData_UndefinedEntity, Standard_Transient)

StepData_UndefinedEntity::StepData_UndefinedEntity()
{
  thecont = new Interface_UndefinedContent;
  thesub  = false;
}

StepData_UndefinedEntity::StepData_UndefinedEntity(const bool issub)
{
  thesub  = issub;
  thecont = new Interface_UndefinedContent;
}

occ::handle<Interface_UndefinedContent> StepData_UndefinedEntity::UndefinedContent() const
{
  return thecont;
}

bool StepData_UndefinedEntity::IsSub() const
{
  return thesub;
}

bool StepData_UndefinedEntity::IsComplex() const
{
  return (!thenext.IsNull());
}

occ::handle<StepData_UndefinedEntity> StepData_UndefinedEntity::Next() const
{
  return thenext;
}

const char* StepData_UndefinedEntity::StepType() const
{
  if (thetype.IsNull())
    return "";
  return thetype->ToCString();
}

void StepData_UndefinedEntity::ReadRecord(const occ::handle<StepData_StepReaderData>& SR,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach)
{
  thetype = new TCollection_HAsciiString(SR->RecordType(num));
  int nb  = SR->NbParams(num);

  thecont->Reservate(nb, 4);
  for (int i = 1; i <= nb; i++)
  {
    occ::handle<Standard_Transient>       anent;
    occ::handle<TCollection_HAsciiString> hval;
    const char*                           val    = SR->ParamCValue(num, i);
    Interface_ParamType                   partyp = SR->ParamType(num, i);
    int                                   nume   = 0;
    if (partyp == Interface_ParamIdent)
    {
      nume = SR->ParamNumber(num, i);
      if (nume > 0)
      {
        anent = SR->BoundEntity(nume);
        if (anent.IsNull())
        {
          nume = 0;
        }
      }
      if (nume <= 0)
      {
        ach->AddFail("A reference to another entity is unresolved");
        partyp = Interface_ParamVoid;
      }
    }
    else if (partyp == Interface_ParamSub)
    {
      nume                                      = SR->ParamNumber(num, i);
      occ::handle<StepData_UndefinedEntity> und = new StepData_UndefinedEntity(true);
      anent                                     = und;
      und->ReadRecord(SR, nume, ach);
    }
    else if (partyp == Interface_ParamText)
    {

      int lval = (int)strlen(val);
      int mval = -1;
      for (int j = 0; j < lval; j++)
      {
        if (val[j] == '\n')
        {
          mval = i;
          break;
        }
      }
      if (mval > 0)
      {
        nume = -1;
        hval = new TCollection_HAsciiString(val);
        hval->RemoveAll('\n');
      }
    }
    if (nume == 0)
      hval = new TCollection_HAsciiString(val);
    if (nume > 0)
      thecont->AddEntity(partyp, anent);
    else
      thecont->AddLiteral(partyp, hval);
  }
  int nextyp = SR->NextForComplex(num);
  if (nextyp == 0)
    return;
  thenext = new StepData_UndefinedEntity;
  thenext->ReadRecord(SR, nextyp, ach);
}

void StepData_UndefinedEntity::WriteParams(StepData_StepWriter& SW) const
{
  if (!IsSub())
    SW.StartEntity(TCollection_AsciiString(StepType()));
  int                             nb = thecont->NbParams();
  occ::handle<Standard_Transient> anent;
  for (int i = 1; i <= nb; i++)
  {
    Interface_ParamType partyp = thecont->ParamType(i);
    if (partyp == Interface_ParamSub)
    {
      DeclareAndCast(StepData_UndefinedEntity, und, thecont->ParamEntity(i));
      und->StepType();
      if (und->IsSub())
        SW.OpenTypedSub(und->StepType());
      und->WriteParams(SW);
      if (und->IsSub())
        SW.CloseSub();
    }
    else if (partyp == Interface_ParamIdent)
    {
      anent = thecont->ParamEntity(i);
      SW.Send(anent);
    }
    else
      SW.SendString(thecont->ParamValue(i)->ToCString());
  }

  if (thenext.IsNull())
    return;
  thenext->WriteParams(SW);
}

void StepData_UndefinedEntity::GetFromAnother(const occ::handle<StepData_UndefinedEntity>& another,
                                              Interface_CopyTool&                          TC)
{

  thetype = new TCollection_HAsciiString(another->StepType());
  thecont = new Interface_UndefinedContent;
  thecont->GetFromAnother(another->UndefinedContent(), TC);

  thesub = another->IsSub();
  if (another->IsComplex())
    thenext = GetCasted(StepData_UndefinedEntity, TC.Transferred(another->Next()));
  else
    thenext.Nullify();
}

void StepData_UndefinedEntity::FillShared(Interface_EntityIterator& list) const
{
  int i, nb = thecont->NbParams();
  for (i = 1; i <= nb; i++)
  {
    Interface_ParamType ptype = thecont->ParamType(i);
    if (ptype == Interface_ParamSub)
    {
      DeclareAndCast(StepData_UndefinedEntity, subent, thecont->ParamEntity(i));
      subent->FillShared(list);
    }
    else if (ptype == Interface_ParamIdent)
    {
      list.AddItem(thecont->ParamEntity(i));
    }
  }
  if (!thenext.IsNull())
    thenext->FillShared(list);
}
