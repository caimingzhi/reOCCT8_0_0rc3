#include <IGESBasic_Name.hpp>
#include <IGESBasic_ToolName.hpp>
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

IGESBasic_ToolName::IGESBasic_ToolName() = default;

void IGESBasic_ToolName::ReadOwnParams(const occ::handle<IGESBasic_Name>& ent,
                                       const occ::handle<IGESData_IGESReaderData>& /* IR */,
                                       IGESData_ParamReader& PR) const
{
  int                                   tempNbPropertyValues;
  occ::handle<TCollection_HAsciiString> tempName;
  // bool st; //szv#4:S4163:12Mar99 not needed

  // clang-format off
  PR.ReadInteger(PR.Current(),"Number of property values",tempNbPropertyValues); //szv#4:S4163:12Mar99 `st=` not needed
  // clang-format on
  PR.ReadText(PR.Current(), "Name", tempName); // szv#4:S4163:12Mar99 `st=` not needed

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempNbPropertyValues, tempName);
}

void IGESBasic_ToolName::WriteOwnParams(const occ::handle<IGESBasic_Name>& ent,
                                        IGESData_IGESWriter&               IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->Value());
}

void IGESBasic_ToolName::OwnShared(const occ::handle<IGESBasic_Name>& /* ent */,
                                   Interface_EntityIterator& /* iter */) const
{
}

void IGESBasic_ToolName::OwnCopy(const occ::handle<IGESBasic_Name>& another,
                                 const occ::handle<IGESBasic_Name>& ent,
                                 Interface_CopyTool& /* TC */) const
{
  int                                   aNbPropertyValues;
  occ::handle<TCollection_HAsciiString> aName;
  aName             = new TCollection_HAsciiString(another->Value());
  aNbPropertyValues = another->NbPropertyValues();
  ent->Init(aNbPropertyValues, aName);
}

bool IGESBasic_ToolName::OwnCorrect(const occ::handle<IGESBasic_Name>& ent) const
{
  bool res = (ent->NbPropertyValues() != 1);
  if (res)
    ent->Init(1, ent->Value());
  return res; // nbpropertyvalues = 1
}

IGESData_DirChecker IGESBasic_ToolName::DirChecker(const occ::handle<IGESBasic_Name>& /*ent*/) const
{
  IGESData_DirChecker DC(406, 15); // Form no = 15 & Type = 406
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESBasic_ToolName::OwnCheck(const occ::handle<IGESBasic_Name>& ent,
                                  const Interface_ShareTool&,
                                  occ::handle<Interface_Check>& ach) const
{
  if (ent->NbPropertyValues() != 1)
    ach->AddFail("Number of Property Values != 1");
}

void IGESBasic_ToolName::OwnDump(const occ::handle<IGESBasic_Name>& ent,
                                 const IGESData_IGESDumper& /* dumper */,
                                 Standard_OStream& S,
                                 const int /* level */) const
{
  S << "IGESBasic_Name\n"
    << "Number of property values : " << ent->NbPropertyValues() << "\n"
    << "Name : ";
  IGESData_DumpString(S, ent->Value());
  S << std::endl;
}
