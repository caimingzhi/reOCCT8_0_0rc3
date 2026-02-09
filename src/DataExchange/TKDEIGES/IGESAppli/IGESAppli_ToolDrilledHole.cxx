#include <IGESAppli_DrilledHole.hpp>
#include <IGESAppli_ToolDrilledHole.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_LevelListEntity.hpp>
#include <IGESData_ParamReader.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>

IGESAppli_ToolDrilledHole::IGESAppli_ToolDrilledHole() = default;

void IGESAppli_ToolDrilledHole::ReadOwnParams(const occ::handle<IGESAppli_DrilledHole>& ent,
                                              const occ::handle<IGESData_IGESReaderData>&,
                                              IGESData_ParamReader& PR) const
{
  int    tempNbPropertyValues;
  double tempDrillDiaSize;
  double tempFinishDiaSize;
  int    tempPlatingFlag;
  int    tempNbLowerLayer;
  int    tempNbHigherLayer;

  PR.ReadInteger(PR.Current(), "No. of Property values", tempNbPropertyValues);
  PR.ReadReal(PR.Current(), "Drill diameter size", tempDrillDiaSize);
  PR.ReadReal(PR.Current(), "Finish diameter size", tempFinishDiaSize);
  PR.ReadInteger(PR.Current(), "Plating Flag", tempPlatingFlag);
  PR.ReadInteger(PR.Current(), "Lower numbered layer", tempNbLowerLayer);
  PR.ReadInteger(PR.Current(), "Higher numbered layer", tempNbHigherLayer);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempNbPropertyValues,
            tempDrillDiaSize,
            tempFinishDiaSize,
            tempPlatingFlag,
            tempNbLowerLayer,
            tempNbHigherLayer);
}

void IGESAppli_ToolDrilledHole::WriteOwnParams(const occ::handle<IGESAppli_DrilledHole>& ent,
                                               IGESData_IGESWriter&                      IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->DrillDiaSize());
  IW.Send(ent->FinishDiaSize());
  IW.SendBoolean(ent->IsPlating());
  IW.Send(ent->NbLowerLayer());
  IW.Send(ent->NbHigherLayer());
}

void IGESAppli_ToolDrilledHole::OwnShared(const occ::handle<IGESAppli_DrilledHole>&,
                                          Interface_EntityIterator&) const
{
}

void IGESAppli_ToolDrilledHole::OwnCopy(const occ::handle<IGESAppli_DrilledHole>& another,
                                        const occ::handle<IGESAppli_DrilledHole>& ent,
                                        Interface_CopyTool&) const
{
  ent->Init(5,
            another->DrillDiaSize(),
            another->FinishDiaSize(),
            (another->IsPlating() ? 1 : 0),
            another->NbLowerLayer(),
            another->NbHigherLayer());
}

bool IGESAppli_ToolDrilledHole::OwnCorrect(const occ::handle<IGESAppli_DrilledHole>& ent) const
{
  bool res = (ent->NbPropertyValues() != 5);
  if (res)
    ent->Init(5,
              ent->DrillDiaSize(),
              ent->FinishDiaSize(),
              (ent->IsPlating() ? 1 : 0),
              ent->NbLowerLayer(),
              ent->NbHigherLayer());
  if (ent->SubordinateStatus() != 0)
  {
    occ::handle<IGESData_LevelListEntity> nulevel;
    ent->InitLevel(nulevel, 0);
    res = true;
  }
  return res;
}

IGESData_DirChecker IGESAppli_ToolDrilledHole::DirChecker(
  const occ::handle<IGESAppli_DrilledHole>&) const
{
  IGESData_DirChecker DC(406, 6);
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESAppli_ToolDrilledHole::OwnCheck(const occ::handle<IGESAppli_DrilledHole>& ent,
                                         const Interface_ShareTool&,
                                         occ::handle<Interface_Check>& ach) const
{
  if (ent->SubordinateStatus() != 0)
    if (ent->DefLevel() != IGESData_DefOne && ent->DefLevel() != IGESData_DefSeveral)
      ach->AddFail("Level type : Not value/reference");
  if (ent->NbPropertyValues() != 5)
    ach->AddFail("Number of Property Values != 5");
}

void IGESAppli_ToolDrilledHole::OwnDump(const occ::handle<IGESAppli_DrilledHole>& ent,
                                        const IGESData_IGESDumper&,
                                        Standard_OStream& S,
                                        const int) const
{
  S << "IGESAppli_DrilledHole" << std::endl;

  S << "Number of property values : " << ent->NbPropertyValues() << std::endl;
  S << "Drill  diameter size :" << ent->DrillDiaSize() << "  ";
  S << "Finish diameter size : " << ent->FinishDiaSize() << std::endl;
  S << "Plating indication flag : ";
  if (!ent->IsPlating())
    S << "NO" << "  -  ";
  else
    S << "YES  -  ";
  S << "Lower Numbered Layer  : " << ent->NbLowerLayer() << "  ";
  S << "Higher Numbered Layer : " << ent->NbHigherLayer() << std::endl;
}
