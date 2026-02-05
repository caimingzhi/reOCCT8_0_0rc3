#include <IFSelect_ContextModif.hpp>
#include <IFSelect_IntParam.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESData_LevelListEntity.hpp>
#include <IGESSelect_ChangeLevelList.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_ChangeLevelList, IGESSelect_ModelModifier)

IGESSelect_ChangeLevelList::IGESSelect_ChangeLevelList()
    : IGESSelect_ModelModifier(true)
{
}

bool IGESSelect_ChangeLevelList::HasOldNumber() const
{
  return (!theold.IsNull());
}

occ::handle<IFSelect_IntParam> IGESSelect_ChangeLevelList::OldNumber() const
{
  return theold;
}

void IGESSelect_ChangeLevelList::SetOldNumber(const occ::handle<IFSelect_IntParam>& param)
{
  theold = param;
}

bool IGESSelect_ChangeLevelList::HasNewNumber() const
{
  return (!thenew.IsNull());
}

occ::handle<IFSelect_IntParam> IGESSelect_ChangeLevelList::NewNumber() const
{
  return thenew;
}

void IGESSelect_ChangeLevelList::SetNewNumber(const occ::handle<IFSelect_IntParam>& param)
{
  thenew = param;
}

void IGESSelect_ChangeLevelList::Performing(IFSelect_ContextModif& ctx,
                                            const occ::handle<IGESData_IGESModel>&,
                                            Interface_CopyTool&) const
{
  int  oldl  = 0;
  bool yaold = HasOldNumber();
  if (yaold)
    oldl = theold->Value();
  bool yanew = HasOldNumber();
  int  newl  = 0;
  if (yanew)
    newl = thenew->Value();
  if (oldl < 0)
    ctx.CCheck()->AddFail("ChangeLevelList : OldNumber negative");
  if (newl < 0)
    ctx.CCheck()->AddFail("ChangeLevelList : NewNumber negative");
  if (oldl < 0 || newl < 0)
    return;

  occ::handle<IGESData_LevelListEntity> nulist;
  for (ctx.Start(); ctx.More(); ctx.Next())
  {
    DeclareAndCast(IGESData_IGESEntity, ent, ctx.ValueResult());
    if (ent.IsNull())
      continue;
    if (ent->DefLevel() != IGESData_DefSeveral)
      continue;
    if (yaold && ent->Level() != oldl)
      continue;
    if (!yanew)
    {
      occ::handle<IGESData_LevelListEntity> list = ent->LevelList();
      if (list.IsNull())
        continue;
      newl = (list->NbLevelNumbers() > 0 ? list->LevelNumber(1) : 0);
      if (newl < 0)
        newl = 0;
    }
    ent->InitLevel(nulist, newl);
    ctx.Trace();
  }
}

TCollection_AsciiString IGESSelect_ChangeLevelList::Label() const
{
  char labl[100];
  int  oldl  = 0;
  bool yaold = HasOldNumber();
  if (yaold)
    oldl = theold->Value();
  bool yanew = HasOldNumber();
  int  newl  = 0;
  if (yanew)
    newl = thenew->Value();

  if (yaold)
    Sprintf(labl, "Changes Level Lists containing %d", oldl);
  else
    Sprintf(labl, "Changes all Level Lists in D.E. %d", oldl);
  TCollection_AsciiString label(labl);
  if (yanew)
    Sprintf(labl, " to Number %d", newl);
  else
    Sprintf(labl, " to Number = first value in List");
  label.AssignCat(labl);
  return label;
}
