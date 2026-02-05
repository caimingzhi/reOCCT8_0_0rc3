#include <IGESAppli_NodalConstraint.hpp>
#include <IGESAppli_Node.hpp>
#include <IGESAppli_ToolNodalConstraint.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDefs_TabularData.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Standard_DomainError.hpp>

IGESAppli_ToolNodalConstraint::IGESAppli_ToolNodalConstraint() = default;

void IGESAppli_ToolNodalConstraint::ReadOwnParams(const occ::handle<IGESAppli_NodalConstraint>& ent,
                                                  const occ::handle<IGESData_IGESReaderData>&   IR,
                                                  IGESData_ParamReader& PR) const
{
  // bool st; //szv#4:S4163:12Mar99 not needed
  int                                                                 num, i;
  int                                                                 tempType;
  occ::handle<IGESAppli_Node>                                         tempNode;
  occ::handle<NCollection_HArray1<occ::handle<IGESDefs_TabularData>>> tempTabularDataProps;
  if (!PR.ReadInteger(PR.Current(), "Number of cases", num))
    num = 0;
  if (num > 0)
    tempTabularDataProps = new NCollection_HArray1<occ::handle<IGESDefs_TabularData>>(1, num);
  else
    PR.AddFail("Number of cases: Not Positive");
  // szv#4:S4163:12Mar99 `st=` not needed
  PR.ReadInteger(PR.Current(), "Type of Constraint", tempType);
  PR.ReadEntity(IR, PR.Current(), "Node", STANDARD_TYPE(IGESAppli_Node), tempNode);

  if (!tempTabularDataProps.IsNull())
    for (i = 1; i <= num; i++)
    {
      occ::handle<IGESDefs_TabularData> tempEntity;
      // szv#4:S4163:12Mar99 moved in if
      if (PR.ReadEntity(IR,
                        PR.Current(),
                        "Tabular Data Property",
                        STANDARD_TYPE(IGESDefs_TabularData),
                        tempEntity))
        tempTabularDataProps->SetValue(i, tempEntity);
    }
  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempType, tempNode, tempTabularDataProps);
}

void IGESAppli_ToolNodalConstraint::WriteOwnParams(
  const occ::handle<IGESAppli_NodalConstraint>& ent,
  IGESData_IGESWriter&                          IW) const
{
  int i, num;
  IW.Send(ent->NbCases());
  IW.Send(ent->Type());
  IW.Send(ent->NodeEntity());
  for (num = ent->NbCases(), i = 1; i <= num; i++)
    IW.Send(ent->TabularData(i));
}

void IGESAppli_ToolNodalConstraint::OwnShared(const occ::handle<IGESAppli_NodalConstraint>& ent,
                                              Interface_EntityIterator& iter) const
{
  int i, num;
  iter.GetOneItem(ent->NodeEntity());
  for (num = ent->NbCases(), i = 1; i <= num; i++)
    iter.GetOneItem(ent->TabularData(i));
}

void IGESAppli_ToolNodalConstraint::OwnCopy(const occ::handle<IGESAppli_NodalConstraint>& another,
                                            const occ::handle<IGESAppli_NodalConstraint>& ent,
                                            Interface_CopyTool&                           TC) const
{
  int num      = another->NbCases();
  int tempType = another->Type();
  DeclareAndCast(IGESAppli_Node, tempNode, TC.Transferred(another->NodeEntity()));
  occ::handle<NCollection_HArray1<occ::handle<IGESDefs_TabularData>>> tempTabularDataProps =
    new NCollection_HArray1<occ::handle<IGESDefs_TabularData>>(1, num);
  for (int i = 1; i <= num; i++)
  {
    DeclareAndCast(IGESDefs_TabularData, new_item, TC.Transferred(another->TabularData(i)));
    tempTabularDataProps->SetValue(i, new_item);
  }
  ent->Init(tempType, tempNode, tempTabularDataProps);
}

IGESData_DirChecker IGESAppli_ToolNodalConstraint::DirChecker(
  const occ::handle<IGESAppli_NodalConstraint>& /* ent */) const
{
  IGESData_DirChecker DC(418, 0);
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESAppli_ToolNodalConstraint::OwnCheck(const occ::handle<IGESAppli_NodalConstraint>& ent,
                                             const Interface_ShareTool&,
                                             occ::handle<Interface_Check>& ach) const
{
  if ((ent->Type() != 1) && (ent->Type() != 2))
    ach->AddFail("Type of Constraint != 1,2");
}

void IGESAppli_ToolNodalConstraint::OwnDump(const occ::handle<IGESAppli_NodalConstraint>& ent,
                                            const IGESData_IGESDumper&                    dumper,
                                            Standard_OStream&                             S,
                                            const int level) const
{
  int sublevel = (level > 4) ? 1 : 0;
  S << "IGESAppli_NodalConstraint\n";
  S << "Type of Constraint : " << ent->Type() << "\n";
  S << "Node : ";
  dumper.Dump(ent->NodeEntity(), S, sublevel);
  S << "\n";
  S << "Tabular Data Properties : ";
  IGESData_DumpEntities(S, dumper, level, 1, ent->NbCases(), ent->TabularData);
  S << std::endl;
}
