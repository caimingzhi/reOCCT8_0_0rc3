#include <IGESAppli_LevelFunction.hpp>
#include <IGESAppli_ToolLevelFunction.hpp>
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

IGESAppli_ToolLevelFunction::IGESAppli_ToolLevelFunction() = default;

void IGESAppli_ToolLevelFunction::ReadOwnParams(
  const occ::handle<IGESAppli_LevelFunction>& ent,
  const occ::handle<IGESData_IGESReaderData>& /* IR */,
  IGESData_ParamReader& PR) const
{
  int                                   tempNbPropertyValues;
  int                                   tempFuncDescripCode;
  occ::handle<TCollection_HAsciiString> tempFuncDescrip;
  // bool st; //szv#4:S4163:12Mar99 not needed

  // szv#4:S4163:12Mar99 `st=` not needed
  PR.ReadInteger(PR.Current(), "No. of Property values", tempNbPropertyValues);

  if (PR.DefinedElseSkip())
    PR.ReadInteger(PR.Current(), "Function description code", tempFuncDescripCode);
  else
    tempFuncDescripCode = 0;

  if (PR.DefinedElseSkip())
    PR.ReadText(PR.Current(), "Function description", tempFuncDescrip);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempNbPropertyValues, tempFuncDescripCode, tempFuncDescrip);
}

void IGESAppli_ToolLevelFunction::WriteOwnParams(const occ::handle<IGESAppli_LevelFunction>& ent,
                                                 IGESData_IGESWriter& IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->FuncDescriptionCode());
  if (ent->FuncDescription().IsNull())
    IW.SendVoid();
  else
    IW.Send(ent->FuncDescription());
}

void IGESAppli_ToolLevelFunction::OwnShared(const occ::handle<IGESAppli_LevelFunction>& /* ent */,
                                            Interface_EntityIterator& /* iter */) const
{
}

void IGESAppli_ToolLevelFunction::OwnCopy(const occ::handle<IGESAppli_LevelFunction>& another,
                                          const occ::handle<IGESAppli_LevelFunction>& ent,
                                          Interface_CopyTool& /* TC */) const
{
  int                                   aNbPropertyValues, code;
  occ::handle<TCollection_HAsciiString> descrip;
  if (!another->FuncDescription().IsNull())
    descrip = new TCollection_HAsciiString(another->FuncDescription());
  code              = another->FuncDescriptionCode();
  aNbPropertyValues = another->NbPropertyValues();

  ent->Init(aNbPropertyValues, code, descrip);
}

bool IGESAppli_ToolLevelFunction::OwnCorrect(const occ::handle<IGESAppli_LevelFunction>& ent) const
{
  bool res = (ent->NbPropertyValues() != 2);
  if (res)
    ent->Init(2, ent->FuncDescriptionCode(), ent->FuncDescription());
  return res; // nbpropertyvalues = 2
}

IGESData_DirChecker IGESAppli_ToolLevelFunction::DirChecker(
  const occ::handle<IGESAppli_LevelFunction>& /* ent */) const
{
  IGESData_DirChecker DC(406, 3); // Form no = 3 & Type = 406
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  DC.SubordinateStatusRequired(00);
  return DC;
}

void IGESAppli_ToolLevelFunction::OwnCheck(const occ::handle<IGESAppli_LevelFunction>& ent,
                                           const Interface_ShareTool&,
                                           occ::handle<Interface_Check>& ach) const
{
  if (ent->NbPropertyValues() != 2)
    ach->AddFail("Number of Property Values != 2");
}

void IGESAppli_ToolLevelFunction::OwnDump(const occ::handle<IGESAppli_LevelFunction>& ent,
                                          const IGESData_IGESDumper& /* dumper */,
                                          Standard_OStream& S,
                                          const int /* level */) const
{
  S << "IGESAppli_LevelFunction\n";

  S << "Number of property values : " << ent->NbPropertyValues() << "\n";
  S << "Function Description code : " << ent->FuncDescriptionCode() << "\n";
  S << "Function Description : ";
  IGESData_DumpString(S, ent->FuncDescription());
  S << "\n";
}
