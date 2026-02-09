#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <IGESDimen_OrdinateDimension.hpp>
#include <IGESDimen_ToolOrdinateDimension.hpp>
#include <IGESDimen_WitnessLine.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>

IGESDimen_ToolOrdinateDimension::IGESDimen_ToolOrdinateDimension() = default;

void IGESDimen_ToolOrdinateDimension::ReadOwnParams(
  const occ::handle<IGESDimen_OrdinateDimension>& theEnt,
  const occ::handle<IGESData_IGESReaderData>&     IR,
  IGESData_ParamReader&                           PR) const
{
  occ::handle<IGESDimen_GeneralNote> tempNote;
  occ::handle<IGESDimen_WitnessLine> witLine;
  occ::handle<IGESDimen_LeaderArrow> leadArr;
  bool                               isLine = false;

  PR.ReadEntity(IR, PR.Current(), "General Note", STANDARD_TYPE(IGESDimen_GeneralNote), tempNote);

  if (theEnt->FormNumber() == 0)
  {
    occ::handle<IGESData_IGESEntity> ent;
    if (!PR.ReadEntity(IR, PR.Current(), "Line or Leader", ent))
    {
    }
    else if (ent->IsKind(STANDARD_TYPE(IGESDimen_WitnessLine)))
    {
      witLine = GetCasted(IGESDimen_WitnessLine, ent);
      isLine  = true;
    }
    else if (ent->IsKind(STANDARD_TYPE(IGESDimen_LeaderArrow)))
    {
      leadArr = GetCasted(IGESDimen_LeaderArrow, ent);
      isLine  = false;
    }
    else
      PR.AddFail("Line or Leader : Type is incorrect");
  }
  else
  {
    PR.ReadEntity(IR, PR.Current(), "Line", STANDARD_TYPE(IGESDimen_WitnessLine), witLine);
    PR.ReadEntity(IR, PR.Current(), "Leader", STANDARD_TYPE(IGESDimen_LeaderArrow), leadArr);
  }

  DirChecker(theEnt).CheckTypeAndForm(PR.CCheck(), theEnt);
  theEnt->Init(tempNote, isLine, witLine, leadArr);
}

void IGESDimen_ToolOrdinateDimension::WriteOwnParams(
  const occ::handle<IGESDimen_OrdinateDimension>& ent,
  IGESData_IGESWriter&                            IW) const
{
  IW.Send(ent->Note());
  if (ent->FormNumber() == 0)
  {
    if (ent->IsLine())
      IW.Send(ent->WitnessLine());
    else
      IW.Send(ent->Leader());
  }
  else
  {
    IW.Send(ent->WitnessLine());
    IW.Send(ent->Leader());
  }
}

void IGESDimen_ToolOrdinateDimension::OwnShared(const occ::handle<IGESDimen_OrdinateDimension>& ent,
                                                Interface_EntityIterator& iter) const
{
  iter.GetOneItem(ent->Note());
  iter.GetOneItem(ent->WitnessLine());
  iter.GetOneItem(ent->Leader());
}

void IGESDimen_ToolOrdinateDimension::OwnCopy(
  const occ::handle<IGESDimen_OrdinateDimension>& another,
  const occ::handle<IGESDimen_OrdinateDimension>& ent,
  Interface_CopyTool&                             TC) const
{
  DeclareAndCast(IGESDimen_GeneralNote, tempNote, TC.Transferred(another->Note()));
  DeclareAndCast(IGESDimen_WitnessLine, witLine, TC.Transferred(another->WitnessLine()));
  DeclareAndCast(IGESDimen_LeaderArrow, leadArr, TC.Transferred(another->Leader()));
  ent->Init(tempNote, another->IsLine(), witLine, leadArr);
}

IGESData_DirChecker IGESDimen_ToolOrdinateDimension::DirChecker(
  const occ::handle<IGESDimen_OrdinateDimension>&) const
{
  IGESData_DirChecker DC(218, 0, 1);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);

  DC.UseFlagRequired(1);

  return DC;
}

void IGESDimen_ToolOrdinateDimension::OwnCheck(const occ::handle<IGESDimen_OrdinateDimension>& ent,
                                               const Interface_ShareTool&,
                                               occ::handle<Interface_Check>& ach) const
{
  bool nowitnes = ent->WitnessLine().IsNull();
  bool noleader = ent->Leader().IsNull();
  if (nowitnes && noleader)
    ach->AddFail("Neither WitnessLine nor LeaderArrow is defined");
  else if (ent->FormNumber() == 0)
  {
    if (!nowitnes && !noleader)
      ach->AddFail("Form 0 cannot afford both WitnessLine and LeaderArrow");
  }
  else
  {
    if (nowitnes || noleader)
      ach->AddFail("Form 1 requires both WtnessLine and LeaderArrow");
  }
}

void IGESDimen_ToolOrdinateDimension::OwnDump(const occ::handle<IGESDimen_OrdinateDimension>& ent,
                                              const IGESData_IGESDumper& dumper,
                                              Standard_OStream&          S,
                                              const int                  level) const
{
  S << "IGESDimen_OrdinateDimension\n";
  int sublevel = (level <= 4) ? 0 : 1;

  S << "General Note : ";
  dumper.Dump(ent->Note(), S, sublevel);
  S << "\n";
  occ::handle<IGESDimen_WitnessLine> witLine = ent->WitnessLine();
  occ::handle<IGESDimen_LeaderArrow> leadArr = ent->Leader();
  if (!witLine.IsNull())
  {
    S << "Witness line : ";
    dumper.Dump(witLine, S, sublevel);
    S << "\n";
  }
  if (!leadArr.IsNull())
  {
    S << "Leader arrow :";
    dumper.Dump(leadArr, S, sublevel);
    S << "\n";
  }
}
