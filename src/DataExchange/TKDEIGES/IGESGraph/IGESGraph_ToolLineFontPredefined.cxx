#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGraph_LineFontPredefined.hpp>
#include <IGESGraph_ToolLineFontPredefined.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>

IGESGraph_ToolLineFontPredefined::IGESGraph_ToolLineFontPredefined() = default;

void IGESGraph_ToolLineFontPredefined::ReadOwnParams(
  const occ::handle<IGESGraph_LineFontPredefined>& ent,
  const occ::handle<IGESData_IGESReaderData>&,
  IGESData_ParamReader& PR) const
{

  int nbPropertyValues;
  int lineFontPatternCode;

  PR.ReadInteger(PR.Current(), "No. of property values", nbPropertyValues);
  if (nbPropertyValues != 1)
    PR.AddFail("No. of Property values : Value is not 1");

  PR.ReadInteger(PR.Current(), "Line Font Pattern Code", lineFontPatternCode);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(nbPropertyValues, lineFontPatternCode);
}

void IGESGraph_ToolLineFontPredefined::WriteOwnParams(
  const occ::handle<IGESGraph_LineFontPredefined>& ent,
  IGESData_IGESWriter&                             IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->LineFontPatternCode());
}

void IGESGraph_ToolLineFontPredefined::OwnShared(const occ::handle<IGESGraph_LineFontPredefined>&,
                                                 Interface_EntityIterator&) const
{
}

void IGESGraph_ToolLineFontPredefined::OwnCopy(
  const occ::handle<IGESGraph_LineFontPredefined>& another,
  const occ::handle<IGESGraph_LineFontPredefined>& ent,
  Interface_CopyTool&) const
{
  ent->Init(1, another->LineFontPatternCode());
}

bool IGESGraph_ToolLineFontPredefined::OwnCorrect(
  const occ::handle<IGESGraph_LineFontPredefined>& ent) const
{
  bool res = (ent->NbPropertyValues() != 1);
  if (res)
    ent->Init(1, ent->LineFontPatternCode());
  return res;
}

IGESData_DirChecker IGESGraph_ToolLineFontPredefined::DirChecker(
  const occ::handle<IGESGraph_LineFontPredefined>&) const
{
  IGESData_DirChecker DC(406, 19);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESGraph_ToolLineFontPredefined::OwnCheck(
  const occ::handle<IGESGraph_LineFontPredefined>& ent,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>& ach) const
{
  if (ent->NbPropertyValues() != 1)
    ach->AddFail("No. of Property values : Value != 1");
}

void IGESGraph_ToolLineFontPredefined::OwnDump(const occ::handle<IGESGraph_LineFontPredefined>& ent,
                                               const IGESData_IGESDumper&,
                                               Standard_OStream& S,
                                               const int) const
{
  S << "IGESGraph_LineFontPredefined\n"
    << "No. of property values : " << ent->NbPropertyValues() << "\n"
    << "Line font pattern code : " << ent->LineFontPatternCode() << "\n"
    << std::endl;
}
