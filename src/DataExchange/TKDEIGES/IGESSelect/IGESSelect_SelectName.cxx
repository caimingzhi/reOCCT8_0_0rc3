

#include <IGESData_IGESEntity.hpp>
#include <IGESSelect_SelectName.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_SelectName, IFSelect_SelectExtract)

IGESSelect_SelectName::IGESSelect_SelectName() = default;

void IGESSelect_SelectName::SetName(const occ::handle<TCollection_HAsciiString>& levnum)
{
  thename = levnum;
}

occ::handle<TCollection_HAsciiString> IGESSelect_SelectName::Name() const
{
  return thename;
}

bool IGESSelect_SelectName::Sort(const int,
                                 const occ::handle<Standard_Transient>& ent,
                                 const occ::handle<Interface_InterfaceModel>&) const
{
  DeclareAndCast(IGESData_IGESEntity, igesent, ent);
  if (igesent.IsNull())
    return false;
  if (!igesent->HasName())
    return false;
  if (thename.IsNull())
    return false;
  occ::handle<TCollection_HAsciiString> name = igesent->NameValue();

  int nb0 = thename->Length();
  int nb1 = name->Length();
  int nbf = (nb1 <= nb0 ? nb1 : nb0);
  int nbt = (nb1 >= nb0 ? nb1 : nb0);
  int i;
  for (i = 1; i <= nbf; i++)
  {
    if (name->Value(i) != thename->Value(i))
      return false;
  }
  if (nb0 > nb1)
    name = thename;
  for (i = nbf + 1; i <= nbt; i++)
  {
    if (name->Value(i) != ' ')
      return false;
  }
  return true;
}

TCollection_AsciiString IGESSelect_SelectName::ExtractLabel() const
{
  char labl[50];
  if (!thename.IsNull())
  {
    Sprintf(labl, "IGES Entity, Name : %s", thename->ToCString());
    return TCollection_AsciiString(labl);
  }
  else
    return TCollection_AsciiString("IGES Entity, Name : (undefined)");
}
