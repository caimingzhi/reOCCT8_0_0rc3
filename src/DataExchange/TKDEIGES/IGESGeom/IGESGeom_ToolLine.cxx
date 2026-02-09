#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGeom_Line.hpp>
#include <IGESGeom_ToolLine.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Msg.hpp>
#include <Standard_DomainError.hpp>

IGESGeom_ToolLine::IGESGeom_ToolLine() = default;

void IGESGeom_ToolLine::ReadOwnParams(const occ::handle<IGESGeom_Line>& ent,
                                      const occ::handle<IGESData_IGESReaderData>&,
                                      IGESData_ParamReader& PR) const
{

  Message_Msg Msg89("XSTEP_89");
  Message_Msg Msg90("XSTEP_90");

  gp_XYZ aStart, anEnd;

  PR.ReadXYZ(PR.CurrentList(1, 3), Msg89, aStart);
  PR.ReadXYZ(PR.CurrentList(1, 3), Msg90, anEnd);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(aStart, anEnd);
}

void IGESGeom_ToolLine::WriteOwnParams(const occ::handle<IGESGeom_Line>& ent,
                                       IGESData_IGESWriter&              IW) const
{
  IW.Send(ent->StartPoint().X());
  IW.Send(ent->StartPoint().Y());
  IW.Send(ent->StartPoint().Z());
  IW.Send(ent->EndPoint().X());
  IW.Send(ent->EndPoint().Y());
  IW.Send(ent->EndPoint().Z());
}

void IGESGeom_ToolLine::OwnShared(const occ::handle<IGESGeom_Line>&,
                                  Interface_EntityIterator&) const
{
}

void IGESGeom_ToolLine::OwnCopy(const occ::handle<IGESGeom_Line>& another,
                                const occ::handle<IGESGeom_Line>& ent,
                                Interface_CopyTool&) const
{
  ent->Init(another->StartPoint().XYZ(), another->EndPoint().XYZ());
}

IGESData_DirChecker IGESGeom_ToolLine::DirChecker(const occ::handle<IGESGeom_Line>&) const
{
  IGESData_DirChecker DC(110, 0, 2);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);

  DC.Color(IGESData_DefAny);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESGeom_ToolLine::OwnCheck(const occ::handle<IGESGeom_Line>&,
                                 const Interface_ShareTool&,
                                 occ::handle<Interface_Check>&) const
{
}

void IGESGeom_ToolLine::OwnDump(const occ::handle<IGESGeom_Line>& ent,
                                const IGESData_IGESDumper&,
                                Standard_OStream& S,
                                const int         level) const
{
  int infin = ent->Infinite();
  switch (infin)
  {
    case 1:
      S << "Semi-Infinite Line\n";
      break;
    case 2:
      S << "Infinite Line\n";
      break;
    default:
      S << "Bounded Line\n";
      break;
  }

  S << "Line from IGESGeom\n"
    << "Starting Point : ";
  IGESData_DumpXYZL(S, level, ent->StartPoint(), ent->Location());
  S << "\n"
       "End Point : ";
  IGESData_DumpXYZL(S, level, ent->EndPoint(), ent->Location());
  S << std::endl;
}
