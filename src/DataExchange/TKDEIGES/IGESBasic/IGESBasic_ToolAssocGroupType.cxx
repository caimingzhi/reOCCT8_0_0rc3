#include <IGESBasic_AssocGroupType.hpp>
#include <IGESBasic_ToolAssocGroupType.hpp>
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

IGESBasic_ToolAssocGroupType::IGESBasic_ToolAssocGroupType() = default;

void IGESBasic_ToolAssocGroupType::ReadOwnParams(
  const occ::handle<IGESBasic_AssocGroupType>& ent,
  const occ::handle<IGESData_IGESReaderData>& /* IR */,
  IGESData_ParamReader& PR) const
{
  // bool st; //szv#4:S4163:12Mar99 not needed
  int                                   tempNbData;
  int                                   tempType;
  occ::handle<TCollection_HAsciiString> tempName;
  if (PR.DefinedElseSkip())
    // clang-format off
    PR.ReadInteger(PR.Current(), "Number of data fields", tempNbData); //szv#4:S4163:12Mar99 `st=` not needed
  else
    tempNbData = 2;
  PR.ReadInteger(PR.Current(), "Type of attached associativity",tempType); //szv#4:S4163:12Mar99 `st=` not needed
  PR.ReadText(PR.Current(), "Name of attached associativity", tempName); //szv#4:S4163:12Mar99 `st=` not needed
  // clang-format on
  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempNbData, tempType, tempName);
}

void IGESBasic_ToolAssocGroupType::WriteOwnParams(const occ::handle<IGESBasic_AssocGroupType>& ent,
                                                  IGESData_IGESWriter& IW) const
{
  IW.Send(ent->NbData());
  IW.Send(ent->AssocType());
  IW.Send(ent->Name());
}

void IGESBasic_ToolAssocGroupType::OwnShared(const occ::handle<IGESBasic_AssocGroupType>& /* ent */,
                                             Interface_EntityIterator& /* iter */) const
{
}

void IGESBasic_ToolAssocGroupType::OwnCopy(const occ::handle<IGESBasic_AssocGroupType>& another,
                                           const occ::handle<IGESBasic_AssocGroupType>& ent,
                                           Interface_CopyTool& /* TC */) const
{
  int                                   tempNbData = another->NbData();
  int                                   tempType   = another->AssocType();
  occ::handle<TCollection_HAsciiString> tempName   = new TCollection_HAsciiString(another->Name());
  ent->Init(tempNbData, tempType, tempName);
}

bool IGESBasic_ToolAssocGroupType::OwnCorrect(
  const occ::handle<IGESBasic_AssocGroupType>& ent) const
{
  bool res = (ent->NbData() != 2);
  if (res)
    ent->Init(2, ent->AssocType(), ent->Name());
  return res; // nbdata=2
}

IGESData_DirChecker IGESBasic_ToolAssocGroupType::DirChecker(
  const occ::handle<IGESBasic_AssocGroupType>& /* ent */) const
{
  IGESData_DirChecker DC(406, 23);
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

void IGESBasic_ToolAssocGroupType::OwnCheck(const occ::handle<IGESBasic_AssocGroupType>& ent,
                                            const Interface_ShareTool&,
                                            occ::handle<Interface_Check>& ach) const
{
  if (ent->NbData() != 2)
    ach->AddFail("Number of data fields != 2");
}

void IGESBasic_ToolAssocGroupType::OwnDump(const occ::handle<IGESBasic_AssocGroupType>& ent,
                                           const IGESData_IGESDumper& /* dumper */,
                                           Standard_OStream& S,
                                           const int /* level */) const
{
  S << "IGESBasic_AssocGroupType\n"
    << "Number of data fields : " << ent->NbData() << "\n"
    << "Type of attached associativity : " << ent->AssocType() << "\n"
    << "Name of attached associativity : ";
  IGESData_DumpString(S, ent->Name());
  S << std::endl;
}
