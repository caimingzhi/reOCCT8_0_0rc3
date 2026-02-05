#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESBasic_SubfigureDef.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESData_Status.hpp>
#include <IGESGeom_Point.hpp>
#include <IGESGeom_ToolPoint.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Msg.hpp>
#include <Standard_DomainError.hpp>

// MGE 28/07/98
IGESGeom_ToolPoint::IGESGeom_ToolPoint() = default;

void IGESGeom_ToolPoint::ReadOwnParams(const occ::handle<IGESGeom_Point>&          ent,
                                       const occ::handle<IGESData_IGESReaderData>& IR,
                                       IGESData_ParamReader&                       PR) const
{
  // MGE 28/07/98
  // Building of messages
  //==================================
  Message_Msg Msg73("XSTEP_73");
  //==================================

  gp_XYZ                              aPoint;
  occ::handle<IGESBasic_SubfigureDef> aSymbol;
  IGESData_Status                     aStatus;
  // bool st; //szv#4:S4163:12Mar99 not needed

  PR.ReadXYZ(PR.CurrentList(1, 3), Msg73, aPoint); // szv#4:S4163:12Mar99 `st=` not needed
  // st = PR.ReadXYZ(PR.CurrentList(1, 3), "Point", aPoint);

  if (PR.DefinedElseSkip())
  {
    if (!PR.ReadEntity(IR,
                       PR.Current(),
                       aStatus,
                       STANDARD_TYPE(IGESBasic_SubfigureDef),
                       aSymbol,
                       true))
    {
      Message_Msg Msg74("XSTEP_74");
      switch (aStatus)
      {
        case IGESData_ReferenceError:
        {
          Message_Msg Msg216("IGES_216");
          Msg74.Arg(Msg216.Value());
          PR.SendFail(Msg74);
          break;
        }
        case IGESData_EntityError:
        {
          Message_Msg Msg217("IGES_217");
          Msg74.Arg(Msg217.Value());
          PR.SendFail(Msg74);
          break;
        }
        case IGESData_TypeError:
        {
          Message_Msg Msg218("IGES_218");
          Msg74.Arg(Msg218.Value());
          PR.SendFail(Msg74);
          break;
        }
        default:
        {
        }
      }
    }
    // szv#4:S4163:12Mar99 `st=` not needed
  }
  // st = PR.ReadEntity(IR, PR.Current(), "Display Symbol",
  //		       STANDARD_TYPE(IGESBasic_SubfigureDef), aSymbol, true);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(aPoint, aSymbol);
}

void IGESGeom_ToolPoint::WriteOwnParams(const occ::handle<IGESGeom_Point>& ent,
                                        IGESData_IGESWriter&               IW) const
{
  IW.Send(ent->Value().X());
  IW.Send(ent->Value().Y());
  IW.Send(ent->Value().Z());
  IW.Send(ent->DisplaySymbol());
}

void IGESGeom_ToolPoint::OwnShared(const occ::handle<IGESGeom_Point>& ent,
                                   Interface_EntityIterator&          iter) const
{
  iter.GetOneItem(ent->DisplaySymbol());
}

void IGESGeom_ToolPoint::OwnCopy(const occ::handle<IGESGeom_Point>& another,
                                 const occ::handle<IGESGeom_Point>& ent,
                                 Interface_CopyTool&                TC) const
{
  gp_XYZ aPoint = (another->Value()).XYZ();

  DeclareAndCast(IGESBasic_SubfigureDef, aSymbol, TC.Transferred(another->DisplaySymbol()));
  ent->Init(aPoint, aSymbol);
}

IGESData_DirChecker IGESGeom_ToolPoint::DirChecker(const occ::handle<IGESGeom_Point>& ent) const
{
  IGESData_DirChecker DC(116, 0);
  DC.Structure(IGESData_DefVoid);
  if (ent->HasDisplaySymbol())
  {
    DC.LineFont(IGESData_DefAny);
    DC.LineWeight(IGESData_DefValue);
  }
  DC.Color(IGESData_DefAny);
  return DC;
}

void IGESGeom_ToolPoint::OwnCheck(const occ::handle<IGESGeom_Point>& /* ent */,
                                  const Interface_ShareTool&,
                                  occ::handle<Interface_Check>& /* ach */) const
{
}

void IGESGeom_ToolPoint::OwnDump(const occ::handle<IGESGeom_Point>& ent,
                                 const IGESData_IGESDumper&         dumper,
                                 Standard_OStream&                  S,
                                 const int                          level) const
{
  S << "IGESGeom_Point\n"
    << " Value         : ";
  IGESData_DumpXYZL(S, level, ent->Value(), ent->Location());
  S << "\n"
    << " Display Symbol : ";
  dumper.Dump(ent->DisplaySymbol(), S, (level <= 4) ? 0 : 1);
  S << std::endl;
}
