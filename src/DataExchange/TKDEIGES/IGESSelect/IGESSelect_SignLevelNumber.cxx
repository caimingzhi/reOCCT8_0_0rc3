

#include <IGESGraph_DefinitionLevel.hpp>
#include <IGESSelect_SignLevelNumber.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_SignLevelNumber, IFSelect_Signature)

static TCollection_AsciiString laval;

IGESSelect_SignLevelNumber::IGESSelect_SignLevelNumber(const bool countmode)
    : IFSelect_Signature("Level Number"),
      thecountmode(countmode)
{
}

const char* IGESSelect_SignLevelNumber::Value(const occ::handle<Standard_Transient>& ent,
                                              const occ::handle<Interface_InterfaceModel>&) const
{
  char carlev[20];
  DeclareAndCast(IGESData_IGESEntity, igesent, ent);

  if (igesent.IsNull())
  {
    const char* astr;
    astr = (const char*)(thecountmode ? " NO LEVEL" : "/0/");
    return astr;
  }

  DeclareAndCast(IGESGraph_DefinitionLevel, levelist, igesent->LevelList());
  int level = igesent->Level();

  if (levelist.IsNull())
  {

    if (level < 0)
    {
      const char* astr;
      astr = (const char*)(thecountmode ? " NO LEVEL" : "/0/");
      return astr;
    }

    laval.Clear();
    if (thecountmode)
      Sprintf(carlev, "%7d", level);
    else
      Sprintf(carlev, "/%d/", level);
    laval.AssignCat(carlev);
  }
  else if (thecountmode)
    return "LEVEL LIST";
  else
  {
    int i, nblev = levelist->NbLevelNumbers();
    laval.Clear();
    laval.AssignCat("LIST:/");
    for (i = 1; i <= nblev; i++)
    {
      Sprintf(carlev, "%d/", levelist->LevelNumber(i));
      laval.AssignCat(carlev);
    }
  }
  return laval.ToCString();
}
