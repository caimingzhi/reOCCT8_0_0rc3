#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESSolid_BooleanTree.hpp>
#include <IGESSolid_SelectedComponent.hpp>
#include <IGESSolid_ToolSelectedComponent.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <Standard_DomainError.hpp>

IGESSolid_ToolSelectedComponent::IGESSolid_ToolSelectedComponent() = default;

void IGESSolid_ToolSelectedComponent::ReadOwnParams(
  const occ::handle<IGESSolid_SelectedComponent>& ent,
  const occ::handle<IGESData_IGESReaderData>&     IR,
  IGESData_ParamReader&                           PR) const
{
  occ::handle<IGESSolid_BooleanTree> tempEntity;
  gp_XYZ                             tempSelectPoint;

  PR.ReadEntity(IR,
                PR.Current(),
                "Boolean Tree Entity",
                STANDARD_TYPE(IGESSolid_BooleanTree),
                tempEntity);

  PR.ReadXYZ(PR.CurrentList(1, 3), "Select Point", tempSelectPoint);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempEntity, tempSelectPoint);
}

void IGESSolid_ToolSelectedComponent::WriteOwnParams(
  const occ::handle<IGESSolid_SelectedComponent>& ent,
  IGESData_IGESWriter&                            IW) const
{
  IW.Send(ent->Component());
  IW.Send(ent->SelectPoint().X());
  IW.Send(ent->SelectPoint().Y());
  IW.Send(ent->SelectPoint().Z());
}

void IGESSolid_ToolSelectedComponent::OwnShared(const occ::handle<IGESSolid_SelectedComponent>& ent,
                                                Interface_EntityIterator& iter) const
{
  iter.GetOneItem(ent->Component());
}

void IGESSolid_ToolSelectedComponent::OwnCopy(
  const occ::handle<IGESSolid_SelectedComponent>& another,
  const occ::handle<IGESSolid_SelectedComponent>& ent,
  Interface_CopyTool&                             TC) const
{
  DeclareAndCast(IGESSolid_BooleanTree, tempEntity, TC.Transferred(another->Component()));
  gp_XYZ tempSelectPoint = another->SelectPoint().XYZ();
  ent->Init(tempEntity, tempSelectPoint);
}

IGESData_DirChecker IGESSolid_ToolSelectedComponent::DirChecker(
  const occ::handle<IGESSolid_SelectedComponent>&) const
{
  IGESData_DirChecker DC(182, 0);

  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefAny);

  DC.BlankStatusIgnored();
  DC.UseFlagRequired(3);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESSolid_ToolSelectedComponent::OwnCheck(const occ::handle<IGESSolid_SelectedComponent>&,
                                               const Interface_ShareTool&,
                                               occ::handle<Interface_Check>&) const
{
}

void IGESSolid_ToolSelectedComponent::OwnDump(const occ::handle<IGESSolid_SelectedComponent>& ent,
                                              const IGESData_IGESDumper& dumper,
                                              Standard_OStream&          S,
                                              const int                  level) const
{
  S << "IGESSolid_SelectedComponent\n";

  S << "Boolean Tree Entity :\n";
  dumper.Dump(ent->Component(), S, (level <= 4) ? 0 : 1);
  S << "Selected Point       : ";
  IGESData_DumpXYZL(S, level, ent->SelectPoint(), ent->Location());
  S << std::endl;
}
