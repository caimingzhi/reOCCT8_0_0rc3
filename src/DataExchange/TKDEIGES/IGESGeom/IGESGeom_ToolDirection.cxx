#include <gp_Vec.hpp>
#include <gp_XY.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGeom_Direction.hpp>
#include <IGESGeom_ToolDirection.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <Standard_DomainError.hpp>

IGESGeom_ToolDirection::IGESGeom_ToolDirection() = default;

void IGESGeom_ToolDirection::ReadOwnParams(const occ::handle<IGESGeom_Direction>& ent,
                                           const occ::handle<IGESData_IGESReaderData>& /* IR */,
                                           IGESData_ParamReader& PR) const
{
  gp_XYZ aDirection;
  gp_XY  tmpXY;
  // bool st; //szv#4:S4163:12Mar99 not needed
  double tmpReal;

  // st = PR.ReadXY(PR.CurrentList(1, 2), "Direction", tmpXY); //szv#4:S4163:12Mar99 moved in if
  if (PR.ReadXY(PR.CurrentList(1, 2), "Direction", tmpXY))
  {
    aDirection.SetX(tmpXY.X());
    aDirection.SetY(tmpXY.Y());
  }

  if (PR.DefinedElseSkip())
  {
    // st = PR.ReadReal(PR.Current(), "Direction", tmpReal); //szv#4:S4163:12Mar99 moved in if
    if (PR.ReadReal(PR.Current(), "Direction", tmpReal))
      aDirection.SetZ(tmpReal);
  }
  else
  {
    aDirection.SetZ(0.0); // Default value.
  }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(aDirection);
}

void IGESGeom_ToolDirection::WriteOwnParams(const occ::handle<IGESGeom_Direction>& ent,
                                            IGESData_IGESWriter&                   IW) const
{
  IW.Send(ent->Value().X());
  IW.Send(ent->Value().Y());
  IW.Send(ent->Value().Z());
}

void IGESGeom_ToolDirection::OwnShared(const occ::handle<IGESGeom_Direction>& /* ent */,
                                       Interface_EntityIterator& /* iter */) const
{
}

void IGESGeom_ToolDirection::OwnCopy(const occ::handle<IGESGeom_Direction>& another,
                                     const occ::handle<IGESGeom_Direction>& ent,
                                     Interface_CopyTool& /* TC */) const
{
  ent->Init(another->Value().XYZ());
}

IGESData_DirChecker IGESGeom_ToolDirection::DirChecker(
  const occ::handle<IGESGeom_Direction>& /* ent */) const
{
  IGESData_DirChecker DC(123, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  //  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);

  DC.BlankStatusIgnored();
  DC.SubordinateStatusRequired(1);
  DC.UseFlagRequired(2);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESGeom_ToolDirection::OwnCheck(const occ::handle<IGESGeom_Direction>& ent,
                                      const Interface_ShareTool&,
                                      occ::handle<Interface_Check>& ach) const
{
  if (ent->Value().XYZ().SquareModulus() <= 0.0)
    ach->AddFail("Direction : The values indicate no direction");
}

void IGESGeom_ToolDirection::OwnDump(const occ::handle<IGESGeom_Direction>& ent,
                                     const IGESData_IGESDumper& /* dumper */,
                                     Standard_OStream& S,
                                     const int         level) const
{
  S << "IGESGeom_Direction\n\n"
    << "Value : ";
  IGESData_DumpXYZL(S, level, ent->Value(), ent->VectorLocation());
  S << std::endl;
}
