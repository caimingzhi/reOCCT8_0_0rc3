#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGraph_NominalSize.hpp>
#include <IGESGraph_ToolNominalSize.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <TCollection_HAsciiString.hpp>

IGESGraph_ToolNominalSize::IGESGraph_ToolNominalSize() = default;

void IGESGraph_ToolNominalSize::ReadOwnParams(const occ::handle<IGESGraph_NominalSize>& ent,
                                              const occ::handle<IGESData_IGESReaderData>&,
                                              IGESData_ParamReader& PR) const
{

  int                                   nbPropertyValues;
  double                                nominalSizeValue;
  occ::handle<TCollection_HAsciiString> nominalSizeName;
  occ::handle<TCollection_HAsciiString> standardName;

  PR.ReadInteger(PR.Current(), "No. of property values", nbPropertyValues);
  if ((nbPropertyValues != 2) && (nbPropertyValues != 3))
    PR.AddFail("No. of Property values : Value is not 2/3");

  PR.ReadReal(PR.Current(), "Nominal size value", nominalSizeValue);

  PR.ReadText(PR.Current(), "Nominal size name", nominalSizeName);

  if (PR.NbParams() >= PR.CurrentNumber())
  {
    int num = PR.CurrentNumber();
    if (PR.ParamType(num) == Interface_ParamText)

      PR.ReadText(PR.Current(), "Name of relevant engg. standard", standardName);
  }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(nbPropertyValues, nominalSizeValue, nominalSizeName, standardName);
}

void IGESGraph_ToolNominalSize::WriteOwnParams(const occ::handle<IGESGraph_NominalSize>& ent,
                                               IGESData_IGESWriter&                      IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->NominalSizeValue());
  IW.Send(ent->NominalSizeName());

  if (ent->HasStandardName())
    IW.Send(ent->StandardName());
}

void IGESGraph_ToolNominalSize::OwnShared(const occ::handle<IGESGraph_NominalSize>&,
                                          Interface_EntityIterator&) const
{
}

void IGESGraph_ToolNominalSize::OwnCopy(const occ::handle<IGESGraph_NominalSize>& another,
                                        const occ::handle<IGESGraph_NominalSize>& ent,
                                        Interface_CopyTool&) const
{
  int                                   nbPropertyValues;
  double                                nominalSizeValue;
  occ::handle<TCollection_HAsciiString> nominalSizeName;
  occ::handle<TCollection_HAsciiString> standardName;

  nbPropertyValues = another->NbPropertyValues();
  nominalSizeValue = another->NominalSizeValue();
  nominalSizeName  = new TCollection_HAsciiString(another->NominalSizeName());
  if (another->HasStandardName())
    standardName = new TCollection_HAsciiString(another->StandardName());

  ent->Init(nbPropertyValues, nominalSizeValue, nominalSizeName, standardName);
}

bool IGESGraph_ToolNominalSize::OwnCorrect(const occ::handle<IGESGraph_NominalSize>& ent) const
{
  int nbp = 2;
  if (ent->HasStandardName())
    nbp = 3;
  bool res = (ent->NbPropertyValues() != nbp);
  if (res)
    ent->Init(nbp, ent->NominalSizeValue(), ent->NominalSizeName(), ent->StandardName());
  return res;
}

IGESData_DirChecker IGESGraph_ToolNominalSize::DirChecker(
  const occ::handle<IGESGraph_NominalSize>&) const
{
  IGESData_DirChecker DC(406, 13);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESGraph_ToolNominalSize::OwnCheck(const occ::handle<IGESGraph_NominalSize>& ent,
                                         const Interface_ShareTool&,
                                         occ::handle<Interface_Check>& ach) const
{
  int nbp = 2;
  if (ent->HasStandardName())
    nbp = 3;
  if (ent->NbPropertyValues() != nbp)
    ach->AddFail("No. of Property values : Value != 2/3 according Standard Name Status");
}

void IGESGraph_ToolNominalSize::OwnDump(const occ::handle<IGESGraph_NominalSize>& ent,
                                        const IGESData_IGESDumper&,
                                        Standard_OStream& S,
                                        const int) const
{
  S << "IGESGraph_NominalSize\n"
    << "No. of property values : " << ent->NbPropertyValues() << "\n"
    << "Nominal size value : " << ent->NominalSizeValue() << "\n"
    << "Nominal size name  : ";
  IGESData_DumpString(S, ent->NominalSizeName());
  S << "\n"
    << "Name of relevant engineering standard : ";
  IGESData_DumpString(S, ent->StandardName());
  S << std::endl;
}
