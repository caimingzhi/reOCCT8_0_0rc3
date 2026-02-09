#include <IGESBasic_ExternalRefName.hpp>
#include <IGESBasic_ToolExternalRefName.hpp>
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

IGESBasic_ToolExternalRefName::IGESBasic_ToolExternalRefName() = default;

void IGESBasic_ToolExternalRefName::ReadOwnParams(const occ::handle<IGESBasic_ExternalRefName>& ent,
                                                  const occ::handle<IGESData_IGESReaderData>&,
                                                  IGESData_ParamReader& PR) const
{

  occ::handle<TCollection_HAsciiString> tempExtRefEntitySymbName;
  PR.ReadText(PR.Current(), "External Reference Symbolic Name", tempExtRefEntitySymbName);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempExtRefEntitySymbName);
}

void IGESBasic_ToolExternalRefName::WriteOwnParams(
  const occ::handle<IGESBasic_ExternalRefName>& ent,
  IGESData_IGESWriter&                          IW) const
{
  IW.Send(ent->ReferenceName());
}

void IGESBasic_ToolExternalRefName::OwnShared(const occ::handle<IGESBasic_ExternalRefName>&,
                                              Interface_EntityIterator&) const
{
}

void IGESBasic_ToolExternalRefName::OwnCopy(const occ::handle<IGESBasic_ExternalRefName>& another,
                                            const occ::handle<IGESBasic_ExternalRefName>& ent,
                                            Interface_CopyTool&) const
{
  occ::handle<TCollection_HAsciiString> tempRefName =
    new TCollection_HAsciiString(another->ReferenceName());
  ent->Init(tempRefName);
}

IGESData_DirChecker IGESBasic_ToolExternalRefName::DirChecker(
  const occ::handle<IGESBasic_ExternalRefName>&) const
{
  IGESData_DirChecker DC(416, 3);
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusRequired(0);
  DC.HierarchyStatusRequired(0);
  return DC;
}

void IGESBasic_ToolExternalRefName::OwnCheck(const occ::handle<IGESBasic_ExternalRefName>&,
                                             const Interface_ShareTool&,
                                             occ::handle<Interface_Check>&) const
{
}

void IGESBasic_ToolExternalRefName::OwnDump(const occ::handle<IGESBasic_ExternalRefName>& ent,
                                            const IGESData_IGESDumper&,
                                            Standard_OStream& S,
                                            const int) const
{
  S << "IGESBasic_ExternalRefName\n"
    << "External Reference Symbolic Name : ";
  IGESData_DumpString(S, ent->ReferenceName());
  S << std::endl;
}
