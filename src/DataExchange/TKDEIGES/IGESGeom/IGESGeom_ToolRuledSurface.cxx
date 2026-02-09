#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESData_Status.hpp>
#include <IGESGeom_RuledSurface.hpp>
#include <IGESGeom_ToolRuledSurface.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Msg.hpp>

IGESGeom_ToolRuledSurface::IGESGeom_ToolRuledSurface() = default;

void IGESGeom_ToolRuledSurface::ReadOwnParams(const occ::handle<IGESGeom_RuledSurface>&   ent,
                                              const occ::handle<IGESData_IGESReaderData>& IR,
                                              IGESData_ParamReader&                       PR) const
{

  int                              aDirFlag, aDevFlag;
  occ::handle<IGESData_IGESEntity> aCurve, anotherCurve;
  IGESData_Status                  aStatus;

  if (!PR.ReadEntity(IR, PR.Current(), aStatus, aCurve))
  {
    Message_Msg Msg148("XSTEP_148");
    switch (aStatus)
    {
      case IGESData_ReferenceError:
      {
        Message_Msg Msg216("IGES_216");
        Msg148.Arg(Msg216.Value());
        PR.SendFail(Msg148);
        break;
      }
      case IGESData_EntityError:
      {
        Message_Msg Msg217("IGES_217");
        Msg148.Arg(Msg217.Value());
        PR.SendFail(Msg148);
        break;
      }
      default:
      {
      }
    }
  }
  if (!PR.ReadEntity(IR, PR.Current(), aStatus, anotherCurve))
  {
    Message_Msg Msg149("XSTEP_149");
    switch (aStatus)
    {
      case IGESData_ReferenceError:
      {
        Message_Msg Msg216("IGES_216");
        Msg149.Arg(Msg216.Value());
        PR.SendFail(Msg149);
        break;
      }
      case IGESData_EntityError:
      {
        Message_Msg Msg217("IGES_217");
        Msg149.Arg(Msg217.Value());
        PR.SendFail(Msg149);
        break;
      }
      default:
      {
      }
    }
  }
  if (!PR.ReadInteger(PR.Current(), aDirFlag))
  {
    Message_Msg Msg150("XSTEP_150");
    PR.SendFail(Msg150);
  }
  if (!PR.ReadInteger(PR.Current(), aDevFlag))
  {
    Message_Msg Msg151("XSTEP_151");
    PR.SendFail(Msg151);
  }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(aCurve, anotherCurve, aDirFlag, aDevFlag);
}

void IGESGeom_ToolRuledSurface::WriteOwnParams(const occ::handle<IGESGeom_RuledSurface>& ent,
                                               IGESData_IGESWriter&                      IW) const
{
  IW.Send(ent->FirstCurve());
  IW.Send(ent->SecondCurve());
  IW.Send(ent->DirectionFlag());
  IW.SendBoolean(ent->IsDevelopable());
}

void IGESGeom_ToolRuledSurface::OwnShared(const occ::handle<IGESGeom_RuledSurface>& ent,
                                          Interface_EntityIterator&                 iter) const
{
  iter.GetOneItem(ent->FirstCurve());
  iter.GetOneItem(ent->SecondCurve());
}

void IGESGeom_ToolRuledSurface::OwnCopy(const occ::handle<IGESGeom_RuledSurface>& another,
                                        const occ::handle<IGESGeom_RuledSurface>& ent,
                                        Interface_CopyTool&                       TC) const
{
  DeclareAndCast(IGESData_IGESEntity, aCurve, TC.Transferred(another->FirstCurve()));
  DeclareAndCast(IGESData_IGESEntity, anotherCurve, TC.Transferred(another->SecondCurve()));
  int aDirFlag = another->DirectionFlag();
  int aDevFlag = (another->IsDevelopable() ? 1 : 0);

  ent->Init(aCurve, anotherCurve, aDirFlag, aDevFlag);
}

IGESData_DirChecker IGESGeom_ToolRuledSurface::DirChecker(
  const occ::handle<IGESGeom_RuledSurface>&) const
{
  IGESData_DirChecker DC(118, 0, 1);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);

  DC.Color(IGESData_DefAny);
  DC.HierarchyStatusIgnored();

  return DC;
}

void IGESGeom_ToolRuledSurface::OwnCheck(const occ::handle<IGESGeom_RuledSurface>&,
                                         const Interface_ShareTool&,
                                         occ::handle<Interface_Check>&) const
{
}

void IGESGeom_ToolRuledSurface::OwnDump(const occ::handle<IGESGeom_RuledSurface>& ent,
                                        const IGESData_IGESDumper&                dumper,
                                        Standard_OStream&                         S,
                                        const int                                 level) const
{
  int tempSubLevel = (level <= 4) ? 0 : 1;

  S << "IGESGeom_RuledSurface\n"
    << "First  Curve   : ";
  dumper.Dump(ent->FirstCurve(), S, tempSubLevel);
  S << "\n"
    << "Second Curve   : ";
  dumper.Dump(ent->SecondCurve(), S, tempSubLevel);
  S << "\n"
    << "Direction Flag : " << ent->DirectionFlag() << "  i.e.";
  if (ent->DirectionFlag() == 0)
    S << "Join First to First, Last to Last\n";
  else
    S << "Join First to Last, Last to First\n";
  if (ent->IsDevelopable())
    S << " .. Is Developable\n";
  else
    S << " .. Is possibly not developable ..\n";
}
