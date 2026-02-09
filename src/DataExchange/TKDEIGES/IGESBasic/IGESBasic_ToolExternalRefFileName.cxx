#include <IGESBasic_ExternalRefFileName.hpp>
#include <IGESBasic_ToolExternalRefFileName.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <TCollection_HAsciiString.hpp>

IGESBasic_ToolExternalRefFileName::IGESBasic_ToolExternalRefFileName() = default;

void IGESBasic_ToolExternalRefFileName::ReadOwnParams(
  const occ::handle<IGESBasic_ExternalRefFileName>& ent,
  const occ::handle<IGESData_IGESReaderData>&,
  IGESData_ParamReader& PR) const
{

  occ::handle<TCollection_HAsciiString> tempExtRefFileIdentifier;
  occ::handle<TCollection_HAsciiString> tempExtRefEntitySymbName;
  PR.ReadText(PR.Current(), "External Reference File Identifier", tempExtRefFileIdentifier);
  PR.ReadText(PR.Current(), "External Reference Symbolic Name", tempExtRefEntitySymbName);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempExtRefFileIdentifier, tempExtRefEntitySymbName);
}

void IGESBasic_ToolExternalRefFileName::WriteOwnParams(
  const occ::handle<IGESBasic_ExternalRefFileName>& ent,
  IGESData_IGESWriter&                              IW) const
{
  IW.Send(ent->FileId());
  IW.Send(ent->ReferenceName());
}

void IGESBasic_ToolExternalRefFileName::OwnShared(const occ::handle<IGESBasic_ExternalRefFileName>&,
                                                  Interface_EntityIterator&) const
{
}

void IGESBasic_ToolExternalRefFileName::OwnCopy(
  const occ::handle<IGESBasic_ExternalRefFileName>& another,
  const occ::handle<IGESBasic_ExternalRefFileName>& ent,
  Interface_CopyTool&) const
{
  occ::handle<TCollection_HAsciiString> tempFileId =
    new TCollection_HAsciiString(another->FileId());
  occ::handle<TCollection_HAsciiString> tempRefName =
    new TCollection_HAsciiString(another->ReferenceName());
  ent->Init(tempFileId, tempRefName);
}

IGESData_DirChecker IGESBasic_ToolExternalRefFileName::DirChecker(
  const occ::handle<IGESBasic_ExternalRefFileName>&) const
{
  IGESData_DirChecker DC(416, 0, 2);
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESBasic_ToolExternalRefFileName::OwnCheck(
  const occ::handle<IGESBasic_ExternalRefFileName>& ent,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>& ach) const
{
  if (ent->FormNumber() == 1)
    ach->AddFail("Invalid Form Number");
}

void IGESBasic_ToolExternalRefFileName::OwnDump(
  const occ::handle<IGESBasic_ExternalRefFileName>& ent,
  const IGESData_IGESDumper&,
  Standard_OStream& S,
  const int) const
{
  S << "IGESBasic_ExternalRefFileName\n"
    << "External Reference File Identifier : ";
  IGESData_DumpString(S, ent->FileId());
  S << "\n"
    << "External Reference Symbolic Name : ";
  IGESData_DumpString(S, ent->ReferenceName());
  S << std::endl;
}
