#include <gp_Pnt2d.hpp>
#include <gp_XY.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <IGESDimen_ToolLeaderArrow.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <Standard_DomainError.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IGESDimen_ToolLeaderArrow::IGESDimen_ToolLeaderArrow() = default;

void IGESDimen_ToolLeaderArrow::ReadOwnParams(const occ::handle<IGESDimen_LeaderArrow>& ent,
                                              const occ::handle<IGESData_IGESReaderData>&,
                                              IGESData_ParamReader& PR) const
{

  double                                  arrowHeadHeight;
  double                                  arrowHeadWidth;
  double                                  zDepth;
  gp_XY                                   arrowHead;
  occ::handle<NCollection_HArray1<gp_XY>> segmentTails;
  int                                     nbval;

  bool st = PR.ReadInteger(PR.Current(), "Count of Segments", nbval);
  if (st && nbval > 0)
    segmentTails = new NCollection_HArray1<gp_XY>(1, nbval);
  else
    PR.AddFail("Count of Segments: Not Positive");

  PR.ReadReal(PR.Current(), "Arrow Head Height", arrowHeadHeight);
  PR.ReadReal(PR.Current(), "Arrow Head Width", arrowHeadWidth);
  PR.ReadReal(PR.Current(), "Z Depth", zDepth);
  PR.ReadXY(PR.CurrentList(1, 2), "Arrow Head Position", arrowHead);

  if (!segmentTails.IsNull())
  {
    for (int i = 1; i <= nbval; i++)
    {
      gp_XY tempXY;

      if (PR.ReadXY(PR.CurrentList(1, 2), "Segment Co-ords.", tempXY))
        segmentTails->SetValue(i, tempXY);
    }
    DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
    ent->Init(arrowHeadHeight, arrowHeadWidth, zDepth, arrowHead, segmentTails);
  }
}

void IGESDimen_ToolLeaderArrow::WriteOwnParams(const occ::handle<IGESDimen_LeaderArrow>& ent,
                                               IGESData_IGESWriter&                      IW) const
{
  int upper = ent->NbSegments();
  IW.Send(upper);
  IW.Send(ent->ArrowHeadHeight());
  IW.Send(ent->ArrowHeadWidth());
  IW.Send(ent->ZDepth());
  IW.Send(ent->ArrowHead().X());
  IW.Send(ent->ArrowHead().Y());
  for (int i = 1; i <= upper; i++)
  {
    IW.Send((ent->SegmentTail(i)).X());
    IW.Send((ent->SegmentTail(i)).Y());
  }
}

void IGESDimen_ToolLeaderArrow::OwnShared(const occ::handle<IGESDimen_LeaderArrow>&,
                                          Interface_EntityIterator&) const
{
}

void IGESDimen_ToolLeaderArrow::OwnCopy(const occ::handle<IGESDimen_LeaderArrow>& another,
                                        const occ::handle<IGESDimen_LeaderArrow>& ent,
                                        Interface_CopyTool&) const
{
  int    nbval           = another->NbSegments();
  double arrowHeadHeight = another->ArrowHeadHeight();
  double arrowHeadWidth  = another->ArrowHeadWidth();
  double zDepth          = another->ZDepth();
  gp_XY  arrowHead       = another->ArrowHead().XY();

  occ::handle<NCollection_HArray1<gp_XY>> segmentTails = new NCollection_HArray1<gp_XY>(1, nbval);

  for (int i = 1; i <= nbval; i++)
  {
    segmentTails->SetValue(i, (another->SegmentTail(i)).XY());
  }

  ent->Init(arrowHeadHeight, arrowHeadWidth, zDepth, arrowHead, segmentTails);
  ent->SetFormNumber(another->FormNumber());
}

IGESData_DirChecker IGESDimen_ToolLeaderArrow::DirChecker(
  const occ::handle<IGESDimen_LeaderArrow>&) const
{
  IGESData_DirChecker DC(214, 1, 12);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);
  DC.UseFlagRequired(1);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESDimen_ToolLeaderArrow::OwnCheck(const occ::handle<IGESDimen_LeaderArrow>&,
                                         const Interface_ShareTool&,
                                         occ::handle<Interface_Check>&) const
{
}

void IGESDimen_ToolLeaderArrow::OwnDump(const occ::handle<IGESDimen_LeaderArrow>& ent,
                                        const IGESData_IGESDumper&,
                                        Standard_OStream& S,
                                        const int         level) const
{
  S << "IGESDimen_LeaderArrow\n"
    << "Number of Segments : " << ent->NbSegments() << "\n"
    << "Arrowhead Height   : " << ent->ArrowHeadHeight() << "\n"
    << "Arrowhead Width    : " << ent->ArrowHeadWidth() << "\n"
    << "Z depth            : " << ent->ZDepth() << "\n"
    << "Arrowhead co-ords  : ";
  IGESData_DumpXYLZ(S, level, ent->ArrowHead(), ent->Location(), ent->ZDepth());
  S << "\nSegment Tails : ";
  IGESData_DumpListXYLZ(S,
                        level,
                        1,
                        ent->NbSegments(),
                        ent->SegmentTail,
                        ent->Location(),
                        ent->ZDepth());
  S << std::endl;
}
