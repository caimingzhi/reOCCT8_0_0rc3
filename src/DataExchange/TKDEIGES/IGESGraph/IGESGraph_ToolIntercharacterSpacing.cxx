#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGraph_IntercharacterSpacing.hpp>
#include <IGESGraph_ToolIntercharacterSpacing.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>

IGESGraph_ToolIntercharacterSpacing::IGESGraph_ToolIntercharacterSpacing() = default;

void IGESGraph_ToolIntercharacterSpacing::ReadOwnParams(
  const occ::handle<IGESGraph_IntercharacterSpacing>& ent,
  const occ::handle<IGESData_IGESReaderData>&,
  IGESData_ParamReader& PR) const
{

  int    nbPropertyValues;
  double iSpace;

  PR.ReadInteger(PR.Current(), "No. of property values", nbPropertyValues);
  if (nbPropertyValues != 1)
    PR.AddFail("No. of Property values : Value is not 1");

  PR.ReadReal(PR.Current(), "Intercharacter space in % of text height", iSpace);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(nbPropertyValues, iSpace);
}

void IGESGraph_ToolIntercharacterSpacing::WriteOwnParams(
  const occ::handle<IGESGraph_IntercharacterSpacing>& ent,
  IGESData_IGESWriter&                                IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->ISpace());
}

void IGESGraph_ToolIntercharacterSpacing::OwnShared(
  const occ::handle<IGESGraph_IntercharacterSpacing>&,
  Interface_EntityIterator&) const
{
}

void IGESGraph_ToolIntercharacterSpacing::OwnCopy(
  const occ::handle<IGESGraph_IntercharacterSpacing>& another,
  const occ::handle<IGESGraph_IntercharacterSpacing>& ent,
  Interface_CopyTool&) const
{
  ent->Init(1, another->ISpace());
}

bool IGESGraph_ToolIntercharacterSpacing::OwnCorrect(
  const occ::handle<IGESGraph_IntercharacterSpacing>& ent) const
{
  bool res = (ent->NbPropertyValues() != 1);
  if (res)
    ent->Init(1, ent->ISpace());
  return res;
}

IGESData_DirChecker IGESGraph_ToolIntercharacterSpacing::DirChecker(
  const occ::handle<IGESGraph_IntercharacterSpacing>&) const
{
  IGESData_DirChecker DC(406, 18);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESGraph_ToolIntercharacterSpacing::OwnCheck(
  const occ::handle<IGESGraph_IntercharacterSpacing>& ent,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>& ach) const
{
  if ((ent->ISpace() < 0.0) || (ent->ISpace() > 100.0))
    ach->AddFail("Intercharacter Space : Value not in the range [0-100]");
  if (ent->NbPropertyValues() != 1)
    ach->AddFail("No. of Property values : Value != 1");
}

void IGESGraph_ToolIntercharacterSpacing::OwnDump(
  const occ::handle<IGESGraph_IntercharacterSpacing>& ent,
  const IGESData_IGESDumper&,
  Standard_OStream& S,
  const int) const
{
  S << "IGESGraph_IntercharacterSpacing\n"
    << "No. of property values : " << ent->NbPropertyValues() << "\n"
    << "Intercharacter space in % of text height : " << ent->ISpace() << "\n"
    << std::endl;
}
