

#include <IFSelect_IntParam.hpp>
#include <IGESGraph_DefinitionLevel.hpp>
#include <IGESSelect_SelectLevelNumber.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_SelectLevelNumber, IFSelect_SelectExtract)

IGESSelect_SelectLevelNumber::IGESSelect_SelectLevelNumber() = default;

void IGESSelect_SelectLevelNumber::SetLevelNumber(const occ::handle<IFSelect_IntParam>& levnum)
{
  thelevnum = levnum;
}

occ::handle<IFSelect_IntParam> IGESSelect_SelectLevelNumber::LevelNumber() const
{
  return thelevnum;
}

bool IGESSelect_SelectLevelNumber::Sort(const int,
                                        const occ::handle<Standard_Transient>& ent,
                                        const occ::handle<Interface_InterfaceModel>&) const
{
  DeclareAndCast(IGESData_IGESEntity, igesent, ent);
  if (igesent.IsNull())
    return false;
  int numlev = 0;
  if (!thelevnum.IsNull())
    numlev = thelevnum->Value();
  DeclareAndCast(IGESGraph_DefinitionLevel, levelist, igesent->LevelList());
  int level = igesent->Level();
  if (levelist.IsNull())
    return (level == numlev);

  if (numlev == 0)
    return false;
  int nb = levelist->NbPropertyValues();
  for (int i = 1; i <= nb; i++)
  {
    level = levelist->LevelNumber(i);
    if (level == numlev)
      return true;
  }
  return false;
}

TCollection_AsciiString IGESSelect_SelectLevelNumber::ExtractLabel() const
{
  char labl[50];
  int  numlev = 0;
  if (!thelevnum.IsNull())
    numlev = thelevnum->Value();
  if (numlev == 0)
    return TCollection_AsciiString("IGES Entity attached to no Level");

  Sprintf(labl, "IGES Entity, Level Number admitting %d", numlev);
  return TCollection_AsciiString(labl);
}
