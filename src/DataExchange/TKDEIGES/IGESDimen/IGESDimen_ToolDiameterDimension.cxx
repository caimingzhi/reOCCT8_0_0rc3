#include <gp_Pnt2d.hpp>
#include <gp_XY.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDimen_DiameterDimension.hpp>
#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <IGESDimen_ToolDiameterDimension.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <Standard_DomainError.hpp>

IGESDimen_ToolDiameterDimension::IGESDimen_ToolDiameterDimension() = default;

void IGESDimen_ToolDiameterDimension::ReadOwnParams(
  const occ::handle<IGESDimen_DiameterDimension>& ent,
  const occ::handle<IGESData_IGESReaderData>&     IR,
  IGESData_ParamReader&                           PR) const
{

  occ::handle<IGESDimen_GeneralNote> note;
  occ::handle<IGESDimen_LeaderArrow> firstLeader;
  occ::handle<IGESDimen_LeaderArrow> secondLeader;
  gp_XY                              center;

  PR.ReadEntity(IR,
                PR.Current(),
                "General Note Entity",
                STANDARD_TYPE(IGESDimen_GeneralNote),
                note);

  PR.ReadEntity(IR,
                PR.Current(),
                "First Leader Entity",
                STANDARD_TYPE(IGESDimen_LeaderArrow),
                firstLeader);

  PR.ReadEntity(IR,
                PR.Current(),
                "Second Leader Entity",

                STANDARD_TYPE(IGESDimen_LeaderArrow),
                secondLeader,
                true);

  PR.ReadXY(PR.CurrentList(1, 2), "Arc Center Co-ords", center);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(note, firstLeader, secondLeader, center);
}

void IGESDimen_ToolDiameterDimension::WriteOwnParams(
  const occ::handle<IGESDimen_DiameterDimension>& ent,
  IGESData_IGESWriter&                            IW) const
{
  IW.Send(ent->Note());
  IW.Send(ent->FirstLeader());
  IW.Send(ent->SecondLeader());
  IW.Send(ent->Center().X());
  IW.Send(ent->Center().Y());
}

void IGESDimen_ToolDiameterDimension::OwnShared(const occ::handle<IGESDimen_DiameterDimension>& ent,
                                                Interface_EntityIterator& iter) const
{
  iter.GetOneItem(ent->Note());
  iter.GetOneItem(ent->FirstLeader());
  iter.GetOneItem(ent->SecondLeader());
}

void IGESDimen_ToolDiameterDimension::OwnCopy(
  const occ::handle<IGESDimen_DiameterDimension>& another,
  const occ::handle<IGESDimen_DiameterDimension>& ent,
  Interface_CopyTool&                             TC) const
{
  DeclareAndCast(IGESDimen_GeneralNote, note, TC.Transferred(another->Note()));
  DeclareAndCast(IGESDimen_LeaderArrow, firstLeader, TC.Transferred(another->FirstLeader()));
  DeclareAndCast(IGESDimen_LeaderArrow, secondLeader, TC.Transferred(another->SecondLeader()));
  gp_XY center = (another->Center()).XY();

  ent->Init(note, firstLeader, secondLeader, center);
}

IGESData_DirChecker IGESDimen_ToolDiameterDimension::DirChecker(
  const occ::handle<IGESDimen_DiameterDimension>&) const
{
  IGESData_DirChecker DC(206, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);
  DC.UseFlagRequired(1);
  return DC;
}

void IGESDimen_ToolDiameterDimension::OwnCheck(const occ::handle<IGESDimen_DiameterDimension>&,
                                               const Interface_ShareTool&,
                                               occ::handle<Interface_Check>&) const
{
}

void IGESDimen_ToolDiameterDimension::OwnDump(const occ::handle<IGESDimen_DiameterDimension>& ent,
                                              const IGESData_IGESDumper& dumper,
                                              Standard_OStream&          S,
                                              const int                  level) const
{
  int sublevel = (level > 4) ? 1 : 0;

  S << "IGESDimen_DiameterDimension\n"
    << "General Note Entity : ";
  dumper.Dump(ent->Note(), S, sublevel);
  S << "\n"
    << "First  Leader Entity : ";
  dumper.Dump(ent->FirstLeader(), S, sublevel);
  S << "\n"
    << "Second Leader Entity : ";
  dumper.Dump(ent->SecondLeader(), S, sublevel);
  S << "\n"
    << "Center Point : ";
  IGESData_DumpXYL(S, level, ent->Center(), ent->Location());
  S << std::endl;
}
