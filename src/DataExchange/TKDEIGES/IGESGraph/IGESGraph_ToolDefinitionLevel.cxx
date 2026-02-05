#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGraph_DefinitionLevel.hpp>
#include <IGESGraph_ToolDefinitionLevel.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IGESGraph_ToolDefinitionLevel::IGESGraph_ToolDefinitionLevel() = default;

void IGESGraph_ToolDefinitionLevel::ReadOwnParams(
  const occ::handle<IGESGraph_DefinitionLevel>& ent,
  const occ::handle<IGESData_IGESReaderData>& /*IR*/,
  IGESData_ParamReader& PR) const
{
  // bool st; //szv#4:S4163:12Mar99 moved down
  int nbval;

  occ::handle<NCollection_HArray1<int>> levelNumbers;

  // Reading nbval(No. of Property Values)
  bool st = PR.ReadInteger(PR.Current(), "No. of Property Values", nbval);
  if (st && nbval > 0)
  {
    // Reading levelNumbers(HArray1OfInteger)
    //      levelNumbers = new NCollection_HArray1<int>(1, nbval);   done by :
    // clang-format off
      PR.ReadInts(PR.CurrentList(nbval), "array levelNumbers", levelNumbers, 1); //szv#4:S4163:12Mar99 `st=` not needed
    // clang-format on
  }
  else
    PR.AddFail("No. of Property Values : Not Positive");

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(levelNumbers);
}

void IGESGraph_ToolDefinitionLevel::WriteOwnParams(
  const occ::handle<IGESGraph_DefinitionLevel>& ent,
  IGESData_IGESWriter&                          IW) const
{
  int Up = ent->NbPropertyValues();
  IW.Send(Up);
  for (int i = 1; i <= Up; i++)
    IW.Send(ent->LevelNumber(i));
}

void IGESGraph_ToolDefinitionLevel::OwnShared(const occ::handle<IGESGraph_DefinitionLevel>& /*ent*/,
                                              Interface_EntityIterator& /*iter*/) const
{
}

void IGESGraph_ToolDefinitionLevel::OwnCopy(const occ::handle<IGESGraph_DefinitionLevel>& another,
                                            const occ::handle<IGESGraph_DefinitionLevel>& ent,
                                            Interface_CopyTool& /*TC*/) const
{
  int                                   nbval;
  occ::handle<NCollection_HArray1<int>> levelNumbers;

  nbval = another->NbPropertyValues();

  levelNumbers = new NCollection_HArray1<int>(1, nbval);
  for (int i = 1; i <= nbval; i++)
    levelNumbers->SetValue(i, another->LevelNumber(i));

  ent->Init(levelNumbers);
}

IGESData_DirChecker IGESGraph_ToolDefinitionLevel::DirChecker(
  const occ::handle<IGESGraph_DefinitionLevel>& /*ent*/) const
{
  IGESData_DirChecker DC(406, 1);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESGraph_ToolDefinitionLevel::OwnCheck(const occ::handle<IGESGraph_DefinitionLevel>& /*ent*/,
                                             const Interface_ShareTool&,
                                             occ::handle<Interface_Check>& /*ach*/) const
{
}

void IGESGraph_ToolDefinitionLevel::OwnDump(const occ::handle<IGESGraph_DefinitionLevel>& ent,
                                            const IGESData_IGESDumper& /*dumper*/,
                                            Standard_OStream& S,
                                            const int         level) const
{
  S << "IGESGraph_DefinitionLevel\n"
    << "Level Numbers : ";
  IGESData_DumpVals(S, level, 1, ent->NbPropertyValues(), ent->LevelNumber);
  S << std::endl;
}
