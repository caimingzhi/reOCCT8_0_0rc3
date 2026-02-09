#include <IGESAppli_PWBArtworkStackup.hpp>
#include <IGESAppli_ToolPWBArtworkStackup.hpp>
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
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IGESAppli_ToolPWBArtworkStackup::IGESAppli_ToolPWBArtworkStackup() = default;

void IGESAppli_ToolPWBArtworkStackup::ReadOwnParams(
  const occ::handle<IGESAppli_PWBArtworkStackup>& ent,
  const occ::handle<IGESData_IGESReaderData>&,
  IGESData_ParamReader& PR) const
{

  int                                   num;
  int                                   tempNbPropertyValues;
  occ::handle<TCollection_HAsciiString> tempArtworkStackupIdent;
  occ::handle<NCollection_HArray1<int>> tempLevelNumbers;

  PR.ReadInteger(PR.Current(), "Number of property values", tempNbPropertyValues);
  PR.ReadText(PR.Current(), "Artwork Stackup Identification", tempArtworkStackupIdent);
  if (!PR.ReadInteger(PR.Current(), "Number of level numbers", num))
    num = 0;
  if (num > 0)
    tempLevelNumbers = new NCollection_HArray1<int>(1, num);
  else
    PR.AddFail("Number of level numbers: Not Positive");
  if (!tempLevelNumbers.IsNull())
    PR.ReadInts(PR.CurrentList(num), "Level Numbers", tempLevelNumbers);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempNbPropertyValues, tempArtworkStackupIdent, tempLevelNumbers);
}

void IGESAppli_ToolPWBArtworkStackup::WriteOwnParams(
  const occ::handle<IGESAppli_PWBArtworkStackup>& ent,
  IGESData_IGESWriter&                            IW) const
{
  int i, num;
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->Identification());
  IW.Send(ent->NbLevelNumbers());
  for (num = ent->NbLevelNumbers(), i = 1; i <= num; i++)
    IW.Send(ent->LevelNumber(i));
}

void IGESAppli_ToolPWBArtworkStackup::OwnShared(const occ::handle<IGESAppli_PWBArtworkStackup>&,
                                                Interface_EntityIterator&) const
{
}

void IGESAppli_ToolPWBArtworkStackup::OwnCopy(
  const occ::handle<IGESAppli_PWBArtworkStackup>& another,
  const occ::handle<IGESAppli_PWBArtworkStackup>& ent,
  Interface_CopyTool&) const
{
  int                                   num                  = another->NbLevelNumbers();
  int                                   tempNbPropertyValues = another->NbPropertyValues();
  occ::handle<TCollection_HAsciiString> tempArtworkStackupIdent =
    new TCollection_HAsciiString(another->Identification());
  occ::handle<NCollection_HArray1<int>> tempLevelNumbers = new NCollection_HArray1<int>(1, num);
  for (int i = 1; i <= num; i++)
    tempLevelNumbers->SetValue(i, another->LevelNumber(i));
  ent->Init(tempNbPropertyValues, tempArtworkStackupIdent, tempLevelNumbers);
}

IGESData_DirChecker IGESAppli_ToolPWBArtworkStackup::DirChecker(
  const occ::handle<IGESAppli_PWBArtworkStackup>&) const
{
  IGESData_DirChecker DC(406, 25);
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

void IGESAppli_ToolPWBArtworkStackup::OwnCheck(const occ::handle<IGESAppli_PWBArtworkStackup>&,
                                               const Interface_ShareTool&,
                                               occ::handle<Interface_Check>&) const
{
}

void IGESAppli_ToolPWBArtworkStackup::OwnDump(const occ::handle<IGESAppli_PWBArtworkStackup>& ent,
                                              const IGESData_IGESDumper&,
                                              Standard_OStream& S,
                                              const int         level) const
{
  S << "IGESAppli_PWBArtworkStackup\n";
  S << "Number of property values : " << ent->NbPropertyValues() << "\n";
  S << "Artwork Stackup Identification : ";
  IGESData_DumpString(S, ent->Identification());
  S << "\n";
  S << "Level Numbers : ";
  IGESData_DumpVals(S, level, 1, ent->NbLevelNumbers(), ent->LevelNumber);
  S << std::endl;
}
