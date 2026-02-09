#include <IGESBasic_ExternalReferenceFile.hpp>
#include <IGESBasic_ToolExternalReferenceFile.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <Standard_DomainError.hpp>

IGESBasic_ToolExternalReferenceFile::IGESBasic_ToolExternalReferenceFile() = default;

void IGESBasic_ToolExternalReferenceFile::ReadOwnParams(
  const occ::handle<IGESBasic_ExternalReferenceFile>& ent,
  const occ::handle<IGESData_IGESReaderData>&,
  IGESData_ParamReader& PR) const
{

  int                                                                     num;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> tempNames;
  bool st = PR.ReadInteger(PR.Current(), "Number of list entries", num);
  if (st && num > 0)
    tempNames = new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(1, num);
  else
    PR.AddFail("Number of list entries: Not Positive");
  if (!tempNames.IsNull())

    PR.ReadTexts(PR.CurrentList(num), "External Reference Entity", tempNames);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempNames);
}

void IGESBasic_ToolExternalReferenceFile::WriteOwnParams(
  const occ::handle<IGESBasic_ExternalReferenceFile>& ent,
  IGESData_IGESWriter&                                IW) const
{
  int i, num;
  IW.Send(ent->NbListEntries());
  for (num = ent->NbListEntries(), i = 1; i <= num; i++)
    IW.Send(ent->Name(i));
}

void IGESBasic_ToolExternalReferenceFile::OwnShared(
  const occ::handle<IGESBasic_ExternalReferenceFile>&,
  Interface_EntityIterator&) const
{
}

void IGESBasic_ToolExternalReferenceFile::OwnCopy(
  const occ::handle<IGESBasic_ExternalReferenceFile>& another,
  const occ::handle<IGESBasic_ExternalReferenceFile>& ent,
  Interface_CopyTool&) const
{
  int num = another->NbListEntries();
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> tempNames =
    new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(1, num);
  for (int i = 1; i <= num; i++)
    tempNames->SetValue(i, new TCollection_HAsciiString(another->Name(i)));
  ent->Init(tempNames);
}

IGESData_DirChecker IGESBasic_ToolExternalReferenceFile::DirChecker(
  const occ::handle<IGESBasic_ExternalReferenceFile>&) const
{
  IGESData_DirChecker DC(406, 12);
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

void IGESBasic_ToolExternalReferenceFile::OwnCheck(
  const occ::handle<IGESBasic_ExternalReferenceFile>&,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>&) const
{
}

void IGESBasic_ToolExternalReferenceFile::OwnDump(
  const occ::handle<IGESBasic_ExternalReferenceFile>& ent,
  const IGESData_IGESDumper&,
  Standard_OStream& S,
  const int         level) const
{
  S << "IGESBasic_ExternalReferenceFile\n"
    << "External Reference Names : ";
  IGESData_DumpStrings(S, level, 1, ent->NbListEntries(), ent->Name);
  S << std::endl;
}
