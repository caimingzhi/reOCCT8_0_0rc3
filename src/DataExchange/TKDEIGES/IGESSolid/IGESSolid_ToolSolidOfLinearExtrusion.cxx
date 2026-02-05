#include <gp_XYZ.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESSolid_SolidOfLinearExtrusion.hpp>
#include <IGESSolid_ToolSolidOfLinearExtrusion.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <Standard_DomainError.hpp>

IGESSolid_ToolSolidOfLinearExtrusion::IGESSolid_ToolSolidOfLinearExtrusion() = default;

void IGESSolid_ToolSolidOfLinearExtrusion::ReadOwnParams(
  const occ::handle<IGESSolid_SolidOfLinearExtrusion>& ent,
  const occ::handle<IGESData_IGESReaderData>&          IR,
  IGESData_ParamReader&                                PR) const
{
  occ::handle<IGESData_IGESEntity> tempEntity;
  gp_XYZ                           tempDirection;
  double                           tempLength;
  double                           tempreal;
  // bool st; //szv#4:S4163:12Mar99 not needed

  // clang-format off
  PR.ReadEntity(IR, PR.Current(), "Curve Entity", tempEntity); //szv#4:S4163:12Mar99 `st=` not needed

  PR.ReadReal(PR.Current(), "Length of extrusion", tempLength); //szv#4:S4163:12Mar99 `st=` not needed
  // clang-format on

  if (PR.DefinedElseSkip())
  {
    // st = PR.ReadReal(PR.Current(), "Extrusion direction (I)", tempreal); //szv#4:S4163:12Mar99
    // moved in if
    if (PR.ReadReal(PR.Current(), "Extrusion direction (I)", tempreal))
      tempDirection.SetX(tempreal);
  }
  else
    tempDirection.SetX(0.0);

  if (PR.DefinedElseSkip())
  {
    // st = PR.ReadReal(PR.Current(), "Extrusion direction (J)", tempreal); //szv#4:S4163:12Mar99
    // moved in if
    if (PR.ReadReal(PR.Current(), "Extrusion direction (J)", tempreal))
      tempDirection.SetY(tempreal);
  }
  else
    tempDirection.SetY(0.0);

  if (PR.DefinedElseSkip())
  {
    // st = PR.ReadReal(PR.Current(), "Extrusion direction (K)", tempreal); //szv#4:S4163:12Mar99
    // moved in if
    if (PR.ReadReal(PR.Current(), "Extrusion direction (K)", tempreal))
      tempDirection.SetZ(tempreal);
  }
  else
    tempDirection.SetZ(1.0);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempEntity, tempLength, tempDirection);
  double eps = 1.E-05;
  if (!tempDirection.IsEqual(ent->ExtrusionDirection().XYZ(), eps))
    PR.AddWarning("Extrusion Direction poorly unitary, normalized");
}

void IGESSolid_ToolSolidOfLinearExtrusion::WriteOwnParams(
  const occ::handle<IGESSolid_SolidOfLinearExtrusion>& ent,
  IGESData_IGESWriter&                                 IW) const
{
  IW.Send(ent->Curve());
  IW.Send(ent->ExtrusionLength());
  IW.Send(ent->ExtrusionDirection().X());
  IW.Send(ent->ExtrusionDirection().Y());
  IW.Send(ent->ExtrusionDirection().Z());
}

void IGESSolid_ToolSolidOfLinearExtrusion::OwnShared(
  const occ::handle<IGESSolid_SolidOfLinearExtrusion>& ent,
  Interface_EntityIterator&                            iter) const
{
  iter.GetOneItem(ent->Curve());
}

void IGESSolid_ToolSolidOfLinearExtrusion::OwnCopy(
  const occ::handle<IGESSolid_SolidOfLinearExtrusion>& another,
  const occ::handle<IGESSolid_SolidOfLinearExtrusion>& ent,
  Interface_CopyTool&                                  TC) const
{
  DeclareAndCast(IGESData_IGESEntity, tempEntity, TC.Transferred(another->Curve()));
  double tempLength    = another->ExtrusionLength();
  gp_XYZ tempDirection = another->ExtrusionDirection().XYZ();
  ent->Init(tempEntity, tempLength, tempDirection);
}

IGESData_DirChecker IGESSolid_ToolSolidOfLinearExtrusion::DirChecker(
  const occ::handle<IGESSolid_SolidOfLinearExtrusion>& /* ent */) const
{
  IGESData_DirChecker DC(164, 0);

  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.Color(IGESData_DefAny);

  DC.UseFlagRequired(0);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESSolid_ToolSolidOfLinearExtrusion::OwnCheck(
  const occ::handle<IGESSolid_SolidOfLinearExtrusion>& ent,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>& ach) const
{
  if (ent->ExtrusionLength() <= 0.0)
    ach->AddFail("Length of extrusion : Not Positive");
}

void IGESSolid_ToolSolidOfLinearExtrusion::OwnDump(
  const occ::handle<IGESSolid_SolidOfLinearExtrusion>& ent,
  const IGESData_IGESDumper&                           dumper,
  Standard_OStream&                                    S,
  const int                                            level) const
{
  S << "IGESSolid_SolidOfLinearExtrusion\n"
    << "Curve entity        : ";
  dumper.Dump(ent->Curve(), S, (level <= 4) ? 0 : 1);
  S << "\n"
    << "Extrusion length    : " << ent->ExtrusionLength() << "\n"
    << "Extrusion direction : ";
  IGESData_DumpXYZL(S, level, ent->ExtrusionDirection(), ent->VectorLocation());
  S << std::endl;
}
