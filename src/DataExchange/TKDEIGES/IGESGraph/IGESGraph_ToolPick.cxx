#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGraph_Pick.hpp>
#include <IGESGraph_ToolPick.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>

IGESGraph_ToolPick::IGESGraph_ToolPick() = default;

void IGESGraph_ToolPick::ReadOwnParams(const occ::handle<IGESGraph_Pick>& ent,
                                       const occ::handle<IGESData_IGESReaderData>& /*IR*/,
                                       IGESData_ParamReader& PR) const
{
  int nbPropertyValues;
  int pickStatus;

  // Reading nbPropertyValues(Integer)
  PR.ReadInteger(PR.Current(), "No. of property values", nbPropertyValues);
  if (nbPropertyValues != 1)
    PR.AddFail("No. of Property values : Value is not 1");

  if (PR.DefinedElseSkip())
    // Reading pickStatus(Integer)
    PR.ReadInteger(PR.Current(), "Pick Flag", pickStatus);
  else
    pickStatus = 0; // Default Value

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(nbPropertyValues, pickStatus);
}

void IGESGraph_ToolPick::WriteOwnParams(const occ::handle<IGESGraph_Pick>& ent,
                                        IGESData_IGESWriter&               IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->PickFlag());
}

void IGESGraph_ToolPick::OwnShared(const occ::handle<IGESGraph_Pick>& /*ent*/,
                                   Interface_EntityIterator& /*iter*/) const
{
}

void IGESGraph_ToolPick::OwnCopy(const occ::handle<IGESGraph_Pick>& another,
                                 const occ::handle<IGESGraph_Pick>& ent,
                                 Interface_CopyTool& /*TC*/) const
{
  ent->Init(1, another->PickFlag());
}

bool IGESGraph_ToolPick::OwnCorrect(const occ::handle<IGESGraph_Pick>& ent) const
{
  bool res = (ent->NbPropertyValues() != 1);
  if (res)
    ent->Init(1, ent->PickFlag()); // nbpropertyvalues=1
  return res;
}

IGESData_DirChecker IGESGraph_ToolPick::DirChecker(const occ::handle<IGESGraph_Pick>& /*ent*/) const
{
  IGESData_DirChecker DC(406, 21);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESGraph_ToolPick::OwnCheck(const occ::handle<IGESGraph_Pick>& ent,
                                  const Interface_ShareTool&,
                                  occ::handle<Interface_Check>& ach) const
{
  if (ent->NbPropertyValues() != 1)
    ach->AddFail("No. of Property values : Value != 1");
  if ((ent->PickFlag() != 0) && (ent->PickFlag() != 1))
    ach->AddFail("Pick Flag : Value != 0/1");
}

void IGESGraph_ToolPick::OwnDump(const occ::handle<IGESGraph_Pick>& ent,
                                 const IGESData_IGESDumper& /*dumper*/,
                                 Standard_OStream& S,
                                 const int /*level*/) const
{
  S << "IGESGraph_Pick\n"
    << "No. of property values : " << ent->NbPropertyValues() << "\n"
    << "Pick flag : " << ent->PickFlag() << (ent->PickFlag() == 0 ? " NO" : " YES") << std::endl;
}
