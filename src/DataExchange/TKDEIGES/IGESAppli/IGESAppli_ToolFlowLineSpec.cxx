#include <IGESAppli_FlowLineSpec.hpp>
#include <IGESAppli_ToolFlowLineSpec.hpp>
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

IGESAppli_ToolFlowLineSpec::IGESAppli_ToolFlowLineSpec() = default;

void IGESAppli_ToolFlowLineSpec::ReadOwnParams(const occ::handle<IGESAppli_FlowLineSpec>& ent,
                                               const occ::handle<IGESData_IGESReaderData>&,
                                               IGESData_ParamReader& PR) const
{

  int                                                                     num;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> tempNameAndModifiers;
  if (!PR.ReadInteger(PR.Current(), "Number of property values", num))
    num = 0;
  if (num > 0)
    tempNameAndModifiers = new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(1, num);
  else
    PR.AddFail("Number of property values: Not Positive");

  if (!tempNameAndModifiers.IsNull())
    PR.ReadTexts(PR.CurrentList(num), "Name and Modifiers", tempNameAndModifiers);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempNameAndModifiers);
}

void IGESAppli_ToolFlowLineSpec::WriteOwnParams(const occ::handle<IGESAppli_FlowLineSpec>& ent,
                                                IGESData_IGESWriter&                       IW) const
{
  int i, num;
  IW.Send(ent->NbPropertyValues());
  for (num = ent->NbPropertyValues(), i = 1; i <= num; i++)
    IW.Send(ent->Modifier(i));
}

void IGESAppli_ToolFlowLineSpec::OwnShared(const occ::handle<IGESAppli_FlowLineSpec>&,
                                           Interface_EntityIterator&) const
{
}

void IGESAppli_ToolFlowLineSpec::OwnCopy(const occ::handle<IGESAppli_FlowLineSpec>& another,
                                         const occ::handle<IGESAppli_FlowLineSpec>& ent,
                                         Interface_CopyTool&) const
{
  int num = another->NbPropertyValues();
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> tempNameAndModifiers =
    new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(1, num);
  for (int i = 1; i <= num; i++)
    tempNameAndModifiers->SetValue(i, new TCollection_HAsciiString(another->Modifier(i)));
  ent->Init(tempNameAndModifiers);
}

IGESData_DirChecker IGESAppli_ToolFlowLineSpec::DirChecker(
  const occ::handle<IGESAppli_FlowLineSpec>&) const
{
  IGESData_DirChecker DC(406, 14);
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

void IGESAppli_ToolFlowLineSpec::OwnCheck(const occ::handle<IGESAppli_FlowLineSpec>&,
                                          const Interface_ShareTool&,
                                          occ::handle<Interface_Check>&) const
{
}

void IGESAppli_ToolFlowLineSpec::OwnDump(const occ::handle<IGESAppli_FlowLineSpec>& ent,
                                         const IGESData_IGESDumper&,
                                         Standard_OStream& S,
                                         const int         level) const
{
  S << "IGESAppli_FlowLineSpec\n";
  S << "Name and Modifiers : ";
  IGESData_DumpStrings(S, level, 1, ent->NbPropertyValues(), ent->Modifier);
  S << "\n";
}
