#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESData_TransfEntity.hpp>
#include <IGESDraw_ToolView.hpp>
#include <IGESDraw_View.hpp>
#include <IGESGeom_Plane.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>

IGESDraw_ToolView::IGESDraw_ToolView() = default;

void IGESDraw_ToolView::ReadOwnParams(const occ::handle<IGESDraw_View>&           ent,
                                      const occ::handle<IGESData_IGESReaderData>& IR,
                                      IGESData_ParamReader&                       PR) const
{

  int                         tempViewNumber;
  double                      tempScaleFactor;
  occ::handle<IGESGeom_Plane> tempLeftPlane, tempTopPlane, tempRightPlane;
  occ::handle<IGESGeom_Plane> tempBottomPlane, tempBackPlane, tempFrontPlane;

  PR.ReadInteger(PR.Current(), "View Number", tempViewNumber);

  if (PR.DefinedElseSkip())
    PR.ReadReal(PR.Current(), "Scale Factor", tempScaleFactor);
  else
    tempScaleFactor = 1.0;

  PR.ReadEntity(IR,
                PR.Current(),
                "Left Side Of View Volume",
                STANDARD_TYPE(IGESGeom_Plane),
                tempLeftPlane,
                true);

  PR.ReadEntity(IR,
                PR.Current(),
                "Top Side Of View Volume",
                STANDARD_TYPE(IGESGeom_Plane),
                tempTopPlane,
                true);

  PR.ReadEntity(IR,
                PR.Current(),
                "Right Side Of View Volume",
                STANDARD_TYPE(IGESGeom_Plane),
                tempRightPlane,
                true);

  PR.ReadEntity(IR,
                PR.Current(),
                "Bottom Side Of View Volume",
                STANDARD_TYPE(IGESGeom_Plane),
                tempBottomPlane,
                true);

  PR.ReadEntity(IR,
                PR.Current(),
                "Back Side Of View Volume",
                STANDARD_TYPE(IGESGeom_Plane),
                tempBackPlane,
                true);

  PR.ReadEntity(IR,
                PR.Current(),
                "Front Side Of View Volume",
                STANDARD_TYPE(IGESGeom_Plane),
                tempFrontPlane,
                true);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempViewNumber,
            tempScaleFactor,
            tempLeftPlane,
            tempTopPlane,
            tempRightPlane,
            tempBottomPlane,
            tempBackPlane,
            tempFrontPlane);
}

void IGESDraw_ToolView::WriteOwnParams(const occ::handle<IGESDraw_View>& ent,
                                       IGESData_IGESWriter&              IW) const
{
  IW.Send(ent->ViewNumber());
  IW.Send(ent->ScaleFactor());
  IW.Send(ent->LeftPlane());
  IW.Send(ent->TopPlane());
  IW.Send(ent->RightPlane());
  IW.Send(ent->BottomPlane());
  IW.Send(ent->BackPlane());
  IW.Send(ent->FrontPlane());
}

void IGESDraw_ToolView::OwnShared(const occ::handle<IGESDraw_View>& ent,
                                  Interface_EntityIterator&         iter) const
{
  iter.GetOneItem(ent->LeftPlane());
  iter.GetOneItem(ent->TopPlane());
  iter.GetOneItem(ent->RightPlane());
  iter.GetOneItem(ent->BottomPlane());
  iter.GetOneItem(ent->BackPlane());
  iter.GetOneItem(ent->FrontPlane());
}

void IGESDraw_ToolView::OwnCopy(const occ::handle<IGESDraw_View>& another,
                                const occ::handle<IGESDraw_View>& ent,
                                Interface_CopyTool&               TC) const
{
  int    tempViewNumber  = another->ViewNumber();
  double tempScaleFactor = another->ScaleFactor();
  DeclareAndCast(IGESGeom_Plane, tempLeftPlane, TC.Transferred(another->LeftPlane()));
  DeclareAndCast(IGESGeom_Plane, tempTopPlane, TC.Transferred(another->TopPlane()));
  DeclareAndCast(IGESGeom_Plane, tempRightPlane, TC.Transferred(another->RightPlane()));
  DeclareAndCast(IGESGeom_Plane, tempBottomPlane, TC.Transferred(another->BottomPlane()));
  DeclareAndCast(IGESGeom_Plane, tempBackPlane, TC.Transferred(another->BackPlane()));
  DeclareAndCast(IGESGeom_Plane, tempFrontPlane, TC.Transferred(another->FrontPlane()));

  ent->Init(tempViewNumber,
            tempScaleFactor,
            tempLeftPlane,
            tempTopPlane,
            tempRightPlane,
            tempBottomPlane,
            tempBackPlane,
            tempFrontPlane);
}

IGESData_DirChecker IGESDraw_ToolView::DirChecker(const occ::handle<IGESDraw_View>&) const
{
  IGESData_DirChecker DC(410, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.UseFlagRequired(1);
  DC.HierarchyStatusIgnored();

  return DC;
}

void IGESDraw_ToolView::OwnCheck(const occ::handle<IGESDraw_View>& ent,
                                 const Interface_ShareTool&,
                                 occ::handle<Interface_Check>& ach) const
{
  if (ent->HasTransf())
  {
    if (ent->Transf()->FormNumber() != 0)
      ach->AddFail("Associated Matrix has not Form Number 0");
  }
}

void IGESDraw_ToolView::OwnDump(const occ::handle<IGESDraw_View>& ent,
                                const IGESData_IGESDumper&        dumper,
                                Standard_OStream&                 S,
                                const int                         level) const
{
  int tempSubLevel = (level <= 4) ? 0 : 1;

  S << "IGESDraw_View\n"
    << "View Number  : " << ent->ViewNumber() << "\n"
    << "Scale Factor : " << ent->ScaleFactor() << "\n"
    << "Left Plane Of View Volume   : ";
  dumper.Dump(ent->LeftPlane(), S, tempSubLevel);
  S << "\n";
  S << "Top Plane Of View Volume    : ";
  dumper.Dump(ent->TopPlane(), S, tempSubLevel);
  S << "\n";
  S << "Right Plane Of View Volume  : ";
  dumper.Dump(ent->RightPlane(), S, tempSubLevel);
  S << "\n";
  S << "Bottom Plane Of View Volume : ";
  dumper.Dump(ent->BottomPlane(), S, tempSubLevel);
  S << "\n";
  S << "Back Plane Of View Volume   : ";
  dumper.Dump(ent->BackPlane(), S, tempSubLevel);
  S << "\n";
  S << "Front Plane Of View Volume  : ";
  dumper.Dump(ent->FrontPlane(), S, tempSubLevel);
  S << std::endl;
}
