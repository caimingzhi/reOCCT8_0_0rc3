#include <IGESAppli_PWBDrilledHole.hpp>
#include <IGESAppli_ToolPWBDrilledHole.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>

IGESAppli_ToolPWBDrilledHole::IGESAppli_ToolPWBDrilledHole() = default;

void IGESAppli_ToolPWBDrilledHole::ReadOwnParams(const occ::handle<IGESAppli_PWBDrilledHole>& ent,
                                                 const occ::handle<IGESData_IGESReaderData>&,
                                                 IGESData_ParamReader& PR) const
{

  int    tempNbPropertyValues;
  double tempDrillDiameter;
  double tempFinishDiameter;
  int    tempFunctionCode;

  if (PR.DefinedElseSkip())
    PR.ReadInteger(PR.Current(), "Number of property values", tempNbPropertyValues);
  else
    tempNbPropertyValues = 3;

  PR.ReadReal(PR.Current(), "Drill Diameter Size", tempDrillDiameter);
  PR.ReadReal(PR.Current(), "Finish Diameter Size", tempFinishDiameter);
  PR.ReadInteger(PR.Current(), "Drilled Hole Function Code", tempFunctionCode);
  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempNbPropertyValues, tempDrillDiameter, tempFinishDiameter, tempFunctionCode);
}

void IGESAppli_ToolPWBDrilledHole::WriteOwnParams(const occ::handle<IGESAppli_PWBDrilledHole>& ent,
                                                  IGESData_IGESWriter& IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->DrillDiameterSize());
  IW.Send(ent->FinishDiameterSize());
  IW.Send(ent->FunctionCode());
}

void IGESAppli_ToolPWBDrilledHole::OwnShared(const occ::handle<IGESAppli_PWBDrilledHole>&,
                                             Interface_EntityIterator&) const
{
}

void IGESAppli_ToolPWBDrilledHole::OwnCopy(const occ::handle<IGESAppli_PWBDrilledHole>& another,
                                           const occ::handle<IGESAppli_PWBDrilledHole>& ent,
                                           Interface_CopyTool&) const
{
  ent->Init(3,
            another->DrillDiameterSize(),
            another->FinishDiameterSize(),
            another->FunctionCode());
}

bool IGESAppli_ToolPWBDrilledHole::OwnCorrect(
  const occ::handle<IGESAppli_PWBDrilledHole>& ent) const
{
  bool res = (ent->NbPropertyValues() != 3);
  if (res)
    ent->Init(3, ent->DrillDiameterSize(), ent->FinishDiameterSize(), ent->FunctionCode());

  return res;
}

IGESData_DirChecker IGESAppli_ToolPWBDrilledHole::DirChecker(
  const occ::handle<IGESAppli_PWBDrilledHole>&) const
{
  IGESData_DirChecker DC(406, 26);
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESAppli_ToolPWBDrilledHole::OwnCheck(const occ::handle<IGESAppli_PWBDrilledHole>& ent,
                                            const Interface_ShareTool&,
                                            occ::handle<Interface_Check>& ach) const
{
  if (ent->NbPropertyValues() != 3)
    ach->AddFail("Number of property values != 3");
  if ((ent->FunctionCode() < 1) || ((ent->FunctionCode() > 5) && (ent->FunctionCode() < 5001))
      || (ent->FunctionCode() > 9999))
    ach->AddFail("Drilled Hole Function Code != 1-5,5001-9999");
}

void IGESAppli_ToolPWBDrilledHole::OwnDump(const occ::handle<IGESAppli_PWBDrilledHole>& ent,
                                           const IGESData_IGESDumper&,
                                           Standard_OStream& S,
                                           const int) const
{
  S << "IGESAppli_PWBDrilledHole\n"
    << "Number of property values : " << ent->NbPropertyValues() << "\n"
    << "Drill Diameter Size  : " << ent->DrillDiameterSize() << "\n"
    << "Finish Diameter Size : " << ent->FinishDiameterSize() << "\n"
    << "Drilled Hole Function Code : " << ent->FunctionCode() << std::endl;
}
