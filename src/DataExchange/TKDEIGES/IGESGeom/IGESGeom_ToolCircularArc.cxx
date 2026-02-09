#include <gp_Pnt2d.hpp>
#include <gp_XY.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGeom_CircularArc.hpp>
#include <IGESGeom_ToolCircularArc.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_MSG.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Msg.hpp>
#include <Standard_DomainError.hpp>

#include <cstdio>

IGESGeom_ToolCircularArc::IGESGeom_ToolCircularArc() = default;

void IGESGeom_ToolCircularArc::ReadOwnParams(const occ::handle<IGESGeom_CircularArc>& ent,
                                             const occ::handle<IGESData_IGESReaderData>&,
                                             IGESData_ParamReader& PR) const
{

  Message_Msg Msg76("XSTEP_76");
  Message_Msg Msg77("XSTEP_77");
  Message_Msg Msg78("XSTEP_78");

  double aZT;
  gp_XY  aCenter, aStart, anEnd;

  if (!PR.ReadReal(PR.Current(), aZT))
  {
    Message_Msg Msg75("XSTEP_75");
    PR.SendFail(Msg75);
  }
  PR.ReadXY(PR.CurrentList(1, 2), Msg76, aCenter);
  PR.ReadXY(PR.CurrentList(1, 2), Msg77, aStart);
  PR.ReadXY(PR.CurrentList(1, 2), Msg78, anEnd);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(aZT, aCenter, aStart, anEnd);
}

void IGESGeom_ToolCircularArc::WriteOwnParams(const occ::handle<IGESGeom_CircularArc>& ent,
                                              IGESData_IGESWriter&                     IW) const
{
  IW.Send(ent->ZPlane());
  IW.Send(ent->Center().X());
  IW.Send(ent->Center().Y());
  IW.Send(ent->StartPoint().X());
  IW.Send(ent->StartPoint().Y());
  IW.Send(ent->EndPoint().X());
  IW.Send(ent->EndPoint().Y());
}

void IGESGeom_ToolCircularArc::OwnShared(const occ::handle<IGESGeom_CircularArc>&,
                                         Interface_EntityIterator&) const
{
}

void IGESGeom_ToolCircularArc::OwnCopy(const occ::handle<IGESGeom_CircularArc>& another,
                                       const occ::handle<IGESGeom_CircularArc>& ent,
                                       Interface_CopyTool&) const
{
  ent->Init(another->ZPlane(),
            another->Center().XY(),
            another->StartPoint().XY(),
            another->EndPoint().XY());
}

IGESData_DirChecker IGESGeom_ToolCircularArc::DirChecker(
  const occ::handle<IGESGeom_CircularArc>&) const
{
  IGESData_DirChecker DC(100, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);

  DC.Color(IGESData_DefAny);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESGeom_ToolCircularArc::OwnCheck(const occ::handle<IGESGeom_CircularArc>&,
                                        const Interface_ShareTool&,
                                        occ::handle<Interface_Check>&) const
{
}

void IGESGeom_ToolCircularArc::OwnDump(const occ::handle<IGESGeom_CircularArc>& ent,
                                       const IGESData_IGESDumper&,
                                       Standard_OStream& S,
                                       const int         level) const
{
  S << "CircularArc from IGESGeom]\n"
    << "Z-Plane Displacement : " << ent->ZPlane() << "\n"
    << "Center      : ";
  IGESData_DumpXYLZ(S, level, ent->Center(), ent->Location(), ent->ZPlane());
  S << "\n"
    << "Start Point : ";
  IGESData_DumpXYLZ(S, level, ent->StartPoint(), ent->Location(), ent->ZPlane());
  S << "\n"
    << "End Point   : ";
  IGESData_DumpXYLZ(S, level, ent->EndPoint(), ent->Location(), ent->ZPlane());
  S << "\n";
  if (level <= 5)
    return;
  S << "  Normal Axis : ";
  IGESData_DumpXYZL(S, level, ent->Axis(), ent->VectorLocation());
  S << std::endl;
}
