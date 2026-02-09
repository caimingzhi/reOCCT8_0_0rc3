

#include <IGESData_FreeFormatEntity.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_IGESWriter.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_UndefinedContent.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESData_FreeFormatEntity, IGESData_UndefinedEntity)

IGESData_FreeFormatEntity::IGESData_FreeFormatEntity() = default;

void IGESData_FreeFormatEntity::SetTypeNumber(const int typenum)
{
  InitTypeAndForm(typenum, 0);
}

void IGESData_FreeFormatEntity::SetFormNumber(const int formnum)
{
  InitTypeAndForm(TypeNumber(), formnum);
}

int IGESData_FreeFormatEntity::NbParams() const
{
  return UndefinedContent()->NbParams();
}

bool IGESData_FreeFormatEntity::ParamData(const int                              num,
                                          Interface_ParamType&                   ptype,
                                          occ::handle<IGESData_IGESEntity>&      ent,
                                          occ::handle<TCollection_HAsciiString>& val) const
{
  occ::handle<Standard_Transient> anEnt = ent;
  return UndefinedContent()->ParamData(num, ptype, anEnt, val)
         && !(ent = occ::down_cast<IGESData_IGESEntity>(anEnt)).IsNull();
}

Interface_ParamType IGESData_FreeFormatEntity::ParamType(const int num) const
{
  return UndefinedContent()->ParamType(num);
}

bool IGESData_FreeFormatEntity::IsParamEntity(const int num) const
{
  return UndefinedContent()->IsParamEntity(num);
}

occ::handle<IGESData_IGESEntity> IGESData_FreeFormatEntity::ParamEntity(const int num) const
{
  return occ::down_cast<IGESData_IGESEntity>(UndefinedContent()->ParamEntity(num));
}

bool IGESData_FreeFormatEntity::IsNegativePointer(const int num) const
{
  if (thenegptrs.IsNull())
    return false;
  int nb = thenegptrs->Length();
  for (int i = 1; i <= nb; i++)
    if (thenegptrs->Value(i) == num)
      return true;
  return false;
}

occ::handle<TCollection_HAsciiString> IGESData_FreeFormatEntity::ParamValue(const int num) const
{
  return UndefinedContent()->ParamValue(num);
}

occ::handle<NCollection_HSequence<int>> IGESData_FreeFormatEntity::NegativePointers() const
{
  return thenegptrs;
}

void IGESData_FreeFormatEntity::AddLiteral(const Interface_ParamType                    ptype,
                                           const occ::handle<TCollection_HAsciiString>& val)
{
  UndefinedContent()->AddLiteral(ptype, val);
}

void IGESData_FreeFormatEntity::AddLiteral(const Interface_ParamType ptype, const char* val)
{
  UndefinedContent()->AddLiteral(ptype, new TCollection_HAsciiString(val));
}

void IGESData_FreeFormatEntity::AddEntity(const Interface_ParamType               ptype,
                                          const occ::handle<IGESData_IGESEntity>& ent,
                                          const bool                              negative)
{
  UndefinedContent()->AddEntity(ptype, ent);
  if (!negative)
    return;
  if (thenegptrs.IsNull())
    thenegptrs = new NCollection_HSequence<int>();
  thenegptrs->Append(NbParams());
}

void IGESData_FreeFormatEntity::AddEntities(
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& ents)
{
  if (ents.IsNull())
  {
    AddLiteral(Interface_ParamInteger, new TCollection_HAsciiString("0"));
    return;
  }
  AddLiteral(Interface_ParamInteger, new TCollection_HAsciiString(ents->Length()));
  int iup = ents->Upper();
  for (int i = ents->Lower(); i <= iup; i++)
  {
    AddEntity(Interface_ParamIdent, ents->Value(i));
  }
}

void IGESData_FreeFormatEntity::AddNegativePointers(
  const occ::handle<NCollection_HSequence<int>>& list)
{
  if (thenegptrs.IsNull())
    thenegptrs = new NCollection_HSequence<int>();
  thenegptrs->Append(list);
}

void IGESData_FreeFormatEntity::ClearNegativePointers()
{
  thenegptrs.Nullify();
}

void IGESData_FreeFormatEntity::WriteOwnParams(IGESData_IGESWriter& IW) const
{

  int neg  = 0;
  int fneg = 0;
  if (!thenegptrs.IsNull())
    if (!thenegptrs->IsEmpty())
    {
      neg  = thenegptrs->Value(1);
      fneg = 1;
    }

  int nb = UndefinedContent()->NbParams();
  for (int i = 1; i <= nb; i++)
  {
    Interface_ParamType ptyp = UndefinedContent()->ParamType(i);
    if (ptyp == Interface_ParamVoid)
      IW.SendVoid();
    else if (UndefinedContent()->IsParamEntity(i))
    {
      DeclareAndCast(IGESData_IGESEntity, anent, UndefinedContent()->ParamEntity(i));

      if (i == neg)
      {
        IW.Send(anent, true);
        if (fneg >= thenegptrs->Length())
          neg = 0;
        else
        {
          fneg++;
          neg = thenegptrs->Value(fneg);
        }
      }
      else
        IW.Send(anent, false);
    }
    else
      IW.SendString(UndefinedContent()->ParamValue(i));
  }
}
