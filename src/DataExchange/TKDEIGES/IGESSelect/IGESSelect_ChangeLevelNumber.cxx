#include <IFSelect_ContextModif.hpp>
#include <IFSelect_IntParam.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESData_LevelListEntity.hpp>
#include <IGESSelect_ChangeLevelNumber.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_ChangeLevelNumber, IGESSelect_ModelModifier)

IGESSelect_ChangeLevelNumber::IGESSelect_ChangeLevelNumber()
    : IGESSelect_ModelModifier(false)
{
}

bool IGESSelect_ChangeLevelNumber::HasOldNumber() const
{
  return (!theold.IsNull());
}

occ::handle<IFSelect_IntParam> IGESSelect_ChangeLevelNumber::OldNumber() const
{
  return theold;
}

void IGESSelect_ChangeLevelNumber::SetOldNumber(const occ::handle<IFSelect_IntParam>& param)
{
  theold = param;
}

occ::handle<IFSelect_IntParam> IGESSelect_ChangeLevelNumber::NewNumber() const
{
  return thenew;
}

void IGESSelect_ChangeLevelNumber::SetNewNumber(const occ::handle<IFSelect_IntParam>& param)
{
  thenew = param;
}

void IGESSelect_ChangeLevelNumber::Performing(IFSelect_ContextModif& ctx,
                                              const occ::handle<IGESData_IGESModel>&,
                                              Interface_CopyTool&) const
{
  int  oldl  = 0;
  bool yaold = HasOldNumber();
  if (yaold)
    oldl = theold->Value();
  int newl = 0;
  if (!thenew.IsNull())
    newl = thenew->Value();
  if (oldl < 0)
    ctx.CCheck()->AddFail("ChangeLevelNumber : OldNumber negative");
  if (newl < 0)
    ctx.CCheck()->AddFail("ChangeLevelNumber : NewNumber negative");
  if (oldl < 0 || newl < 0)
    return;

  occ::handle<IGESData_LevelListEntity> nulist;
  for (ctx.Start(); ctx.More(); ctx.Next())
  {
    DeclareAndCast(IGESData_IGESEntity, ent, ctx.ValueResult());
    if (ent.IsNull())
      continue;
    if (ent->DefLevel() == IGESData_DefSeveral)
      continue;
    if (yaold && ent->Level() != oldl)
      continue;
    ent->InitLevel(nulist, newl);
    ctx.Trace();
  }
}

TCollection_AsciiString IGESSelect_ChangeLevelNumber::Label() const
{
  char labl[100];
  int  oldl  = 0;
  bool yaold = HasOldNumber();
  if (yaold)
    oldl = theold->Value();
  int newl = 0;
  if (!thenew.IsNull())
    newl = thenew->Value();

  if (yaold)
    Sprintf(labl, "Changes Level Number %d to %d", oldl, newl);
  else
    Sprintf(labl, "Changes all Level Numbers positive and zero to %d", newl);
  return TCollection_AsciiString(labl);
}
