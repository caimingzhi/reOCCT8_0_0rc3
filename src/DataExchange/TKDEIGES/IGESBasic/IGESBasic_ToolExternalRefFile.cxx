#include <IGESBasic_ExternalRefFile.hpp>
#include <IGESBasic_ToolExternalRefFile.hpp>
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

IGESBasic_ToolExternalRefFile::IGESBasic_ToolExternalRefFile() = default;

void IGESBasic_ToolExternalRefFile::ReadOwnParams(
  const occ::handle<IGESBasic_ExternalRefFile>& ent,
  const occ::handle<IGESData_IGESReaderData>& /* IR */,
  IGESData_ParamReader& PR) const
{
  // bool st; //szv#4:S4163:12Mar99 not needed
  occ::handle<TCollection_HAsciiString> tempExtRefFileIdentifier;
  PR.ReadText(PR.Current(),
              "External Reference File Identifier",
              tempExtRefFileIdentifier); // szv#4:S4163:12Mar99 `st=` not needed

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempExtRefFileIdentifier);
}

void IGESBasic_ToolExternalRefFile::WriteOwnParams(
  const occ::handle<IGESBasic_ExternalRefFile>& ent,
  IGESData_IGESWriter&                          IW) const
{
  IW.Send(ent->FileId());
}

void IGESBasic_ToolExternalRefFile::OwnShared(
  const occ::handle<IGESBasic_ExternalRefFile>& /* ent */,
  Interface_EntityIterator& /* iter */) const
{
}

void IGESBasic_ToolExternalRefFile::OwnCopy(const occ::handle<IGESBasic_ExternalRefFile>& another,
                                            const occ::handle<IGESBasic_ExternalRefFile>& ent,
                                            Interface_CopyTool& /* TC */) const
{
  occ::handle<TCollection_HAsciiString> tempFileId =
    new TCollection_HAsciiString(another->FileId());
  ent->Init(tempFileId);
}

IGESData_DirChecker IGESBasic_ToolExternalRefFile::DirChecker(
  const occ::handle<IGESBasic_ExternalRefFile>& /* ent */) const
{
  IGESData_DirChecker DC(416, 1);
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESBasic_ToolExternalRefFile::OwnCheck(
  const occ::handle<IGESBasic_ExternalRefFile>& /* ent */,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>& /* ach */) const
{
}

void IGESBasic_ToolExternalRefFile::OwnDump(const occ::handle<IGESBasic_ExternalRefFile>& ent,
                                            const IGESData_IGESDumper& /* dumper */,
                                            Standard_OStream& S,
                                            const int /* level */) const
{
  S << "IGESBasic_ExternalRefFile\n"
    << "External Reference File Identifier : ";
  IGESData_DumpString(S, ent->FileId());
  S << std::endl;
}
