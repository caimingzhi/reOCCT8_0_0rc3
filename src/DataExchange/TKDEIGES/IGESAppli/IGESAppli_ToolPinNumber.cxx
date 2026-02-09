#include <IGESAppli_PinNumber.hpp>
#include <IGESAppli_ToolPinNumber.hpp>
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

IGESAppli_ToolPinNumber::IGESAppli_ToolPinNumber() = default;

void IGESAppli_ToolPinNumber::ReadOwnParams(const occ::handle<IGESAppli_PinNumber>& ent,
                                            const occ::handle<IGESData_IGESReaderData>&,
                                            IGESData_ParamReader& PR) const
{
  int                                   tempNbPropertyValues;
  occ::handle<TCollection_HAsciiString> tempPinNumber;

  PR.ReadInteger(PR.Current(), "Number of property values", tempNbPropertyValues);
  PR.ReadText(PR.Current(), "PinNumber", tempPinNumber);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempNbPropertyValues, tempPinNumber);
}

void IGESAppli_ToolPinNumber::WriteOwnParams(const occ::handle<IGESAppli_PinNumber>& ent,
                                             IGESData_IGESWriter&                    IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->PinNumberVal());
}

void IGESAppli_ToolPinNumber::OwnShared(const occ::handle<IGESAppli_PinNumber>&,
                                        Interface_EntityIterator&) const
{
}

void IGESAppli_ToolPinNumber::OwnCopy(const occ::handle<IGESAppli_PinNumber>& another,
                                      const occ::handle<IGESAppli_PinNumber>& ent,
                                      Interface_CopyTool&) const
{
  int                                   aNbPropertyValues;
  occ::handle<TCollection_HAsciiString> aPinNumber =
    new TCollection_HAsciiString(another->PinNumberVal());
  aNbPropertyValues = another->NbPropertyValues();
  ent->Init(aNbPropertyValues, aPinNumber);
}

bool IGESAppli_ToolPinNumber::OwnCorrect(const occ::handle<IGESAppli_PinNumber>& ent) const
{
  bool res = (ent->SubordinateStatus() != 0);
  if (res)
  {
    occ::handle<IGESData_LevelListEntity> nulevel;
    ent->InitLevel(nulevel, 0);
  }
  return res;
}

IGESData_DirChecker IGESAppli_ToolPinNumber::DirChecker(
  const occ::handle<IGESAppli_PinNumber>&) const
{
  IGESData_DirChecker DC(406, 8);
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESAppli_ToolPinNumber::OwnCheck(const occ::handle<IGESAppli_PinNumber>& ent,
                                       const Interface_ShareTool&,
                                       occ::handle<Interface_Check>& ach) const
{
  if (ent->SubordinateStatus() != 0)
    if (ent->DefLevel() != IGESData_DefOne && ent->DefLevel() != IGESData_DefSeveral)
      ach->AddFail("Level type: Incorrect");
  if (ent->NbPropertyValues() != 1)
    ach->AddFail("Number of Property Values != 1");
}

void IGESAppli_ToolPinNumber::OwnDump(const occ::handle<IGESAppli_PinNumber>& ent,
                                      const IGESData_IGESDumper&,
                                      Standard_OStream& S,
                                      const int) const
{
  S << "IGESAppli_PinNumber\n";
  S << "Number of Property Values : " << ent->NbPropertyValues() << "\n";
  S << "PinNumber : ";
  IGESData_DumpString(S, ent->PinNumberVal());
  S << std::endl;
}
