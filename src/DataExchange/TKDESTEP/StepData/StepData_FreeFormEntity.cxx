

#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>
#include <StepData_FreeFormEntity.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepData_FreeFormEntity, Standard_Transient)

void StepData_FreeFormEntity::SetStepType(const char* typenam)
{

  thetype.Clear();
  thetype.AssignCat(typenam);
}

const char* StepData_FreeFormEntity::StepType() const
{
  return thetype.ToCString();
}

void StepData_FreeFormEntity::SetNext(const occ::handle<StepData_FreeFormEntity>& next,
                                      const bool                                  last)
{
  if (next.IsNull())
    thenext.Nullify();
  else if (thenext.IsNull())
    thenext = next;
  else if (last)
    thenext->SetNext(next);
  else
  {
    next->SetNext(thenext, last);
    thenext = next;
  }
}

occ::handle<StepData_FreeFormEntity> StepData_FreeFormEntity::Next() const
{
  return thenext;
}

bool StepData_FreeFormEntity::IsComplex() const
{

  return (!thenext.IsNull());
}

occ::handle<StepData_FreeFormEntity> StepData_FreeFormEntity::Typed(const char* typenam) const
{
  occ::handle<StepData_FreeFormEntity> res;
  if (thetype.IsEqual(typenam))
    return this;
  if (thenext.IsNull())
    return res;
  return thenext->Typed(typenam);
}

occ::handle<NCollection_HSequence<TCollection_AsciiString>> StepData_FreeFormEntity::TypeList()
  const
{
  occ::handle<NCollection_HSequence<TCollection_AsciiString>> li =
    new NCollection_HSequence<TCollection_AsciiString>();
  li->Append(thetype);
  occ::handle<StepData_FreeFormEntity> next = thenext;
  while (!next.IsNull())
  {
    li->Append(TCollection_AsciiString(next->StepType()));
    next = next->Next();
  }
  return li;
}

bool StepData_FreeFormEntity::Reorder(occ::handle<StepData_FreeFormEntity>& ent)
{

  if (ent.IsNull())
    return false;
  if (!ent->IsComplex())
    return false;
  bool                                 afr = false;
  occ::handle<StepData_FreeFormEntity> e1  = ent;
  occ::handle<StepData_FreeFormEntity> e2  = ent->Next();

  while (!e2.IsNull())
  {
    if (strcmp(e1->StepType(), e2->StepType()) > 0)
    {
      afr = true;
      break;
    }
    e1 = e2;
    e2 = e1->Next();
  }
  if (!afr)
    return afr;

  e1 = ent;
  e2.Nullify();
  NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>> dic;
  while (!e1.IsNull())
  {
    dic.Bind(e1->StepType(), e1);
    e1 = e1->Next();
  }

  for (NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>>::Iterator iter(
         dic);
       iter.More();
       iter.Next())
  {
    e1 = GetCasted(StepData_FreeFormEntity, iter.Value());
    if (!e1.IsNull())
      e1->SetNext(e2);
  }

  e1.Nullify();
  for (NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>>::Iterator iter(
         dic);
       iter.More();
       iter.Next())
  {
    e2 = GetCasted(StepData_FreeFormEntity, iter.Value());
    if (!e1.IsNull())
      e1->SetNext(e2);
    e1 = e2;
  }

  ent = e1;
  return afr;
}

void StepData_FreeFormEntity::SetNbFields(const int nb)
{

  if (nb <= 0)
    thefields.Nullify();
  else
    thefields = new NCollection_HArray1<StepData_Field>(1, nb);
}

int StepData_FreeFormEntity::NbFields() const
{
  return (thefields.IsNull() ? 0 : thefields->Length());
}

const StepData_Field& StepData_FreeFormEntity::Field(const int num) const
{
  return thefields->Value(num);
}

StepData_Field& StepData_FreeFormEntity::CField(const int num)
{
  return thefields->ChangeValue(num);
}
