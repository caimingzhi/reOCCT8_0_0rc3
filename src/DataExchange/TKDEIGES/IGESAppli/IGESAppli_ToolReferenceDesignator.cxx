#include <IGESAppli_ReferenceDesignator.hpp>
#include <IGESAppli_ToolReferenceDesignator.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_LevelListEntity.hpp>
#include <IGESData_ParamReader.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <TCollection_HAsciiString.hpp>

IGESAppli_ToolReferenceDesignator::IGESAppli_ToolReferenceDesignator() = default;

void IGESAppli_ToolReferenceDesignator::ReadOwnParams(
  const occ::handle<IGESAppli_ReferenceDesignator>& ent,
  const occ::handle<IGESData_IGESReaderData>&,
  IGESData_ParamReader& PR) const
{
  int                                   tempNbPropertyValues;
  occ::handle<TCollection_HAsciiString> tempReferenceDesignator;

  PR.ReadInteger(PR.Current(), "Number of property values", tempNbPropertyValues);
  PR.ReadText(PR.Current(), "ReferenceDesignator", tempReferenceDesignator);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempNbPropertyValues, tempReferenceDesignator);
}

void IGESAppli_ToolReferenceDesignator::WriteOwnParams(
  const occ::handle<IGESAppli_ReferenceDesignator>& ent,
  IGESData_IGESWriter&                              IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->RefDesignatorText());
}

void IGESAppli_ToolReferenceDesignator::OwnShared(const occ::handle<IGESAppli_ReferenceDesignator>&,
                                                  Interface_EntityIterator&) const
{
}

void IGESAppli_ToolReferenceDesignator::OwnCopy(
  const occ::handle<IGESAppli_ReferenceDesignator>& another,
  const occ::handle<IGESAppli_ReferenceDesignator>& ent,
  Interface_CopyTool&) const
{
  int                                   aNbPropertyValues;
  occ::handle<TCollection_HAsciiString> aReferenceDesignator =
    new TCollection_HAsciiString(another->RefDesignatorText());
  aNbPropertyValues = another->NbPropertyValues();
  ent->Init(aNbPropertyValues, aReferenceDesignator);
}

bool IGESAppli_ToolReferenceDesignator::OwnCorrect(
  const occ::handle<IGESAppli_ReferenceDesignator>& ent) const
{
  bool res = (ent->NbPropertyValues() != 1);
  if (res)
    ent->Init(1, ent->RefDesignatorText());

  if (ent->SubordinateStatus() != 0)
  {
    occ::handle<IGESData_LevelListEntity> nulevel;
    ent->InitLevel(nulevel, 0);
    res = true;
  }
  return res;
}

IGESData_DirChecker IGESAppli_ToolReferenceDesignator::DirChecker(
  const occ::handle<IGESAppli_ReferenceDesignator>&) const
{

  IGESData_DirChecker DC(406, 7);
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESAppli_ToolReferenceDesignator::OwnCheck(
  const occ::handle<IGESAppli_ReferenceDesignator>& ent,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>& ach) const
{
  if (ent->SubordinateStatus() != 0)

    if (ent->DefLevel() != IGESData_DefOne && ent->DefLevel() != IGESData_DefSeveral)
      ach->AddFail("Level type: Not value/reference");
  if (ent->NbPropertyValues() != 1)
    ach->AddFail("Number of Property Values != 1");
}

void IGESAppli_ToolReferenceDesignator::OwnDump(
  const occ::handle<IGESAppli_ReferenceDesignator>& ent,
  const IGESData_IGESDumper&,
  Standard_OStream& S,
  const int) const
{
  S << "IGESAppli_ReferenceDesignator\n";
  S << "Number of Property Values : " << ent->NbPropertyValues() << "\n";
  S << "ReferenceDesignator : ";
  IGESData_DumpString(S, ent->RefDesignatorText());
  S << std::endl;
}
