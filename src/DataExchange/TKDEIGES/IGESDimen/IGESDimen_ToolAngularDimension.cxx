#include <gp_Pnt2d.hpp>
#include <gp_XY.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDimen_AngularDimension.hpp>
#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <IGESDimen_ToolAngularDimension.hpp>
#include <IGESDimen_WitnessLine.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <Standard_DomainError.hpp>

IGESDimen_ToolAngularDimension::IGESDimen_ToolAngularDimension() = default;

void IGESDimen_ToolAngularDimension::ReadOwnParams(
  const occ::handle<IGESDimen_AngularDimension>& ent,
  const occ::handle<IGESData_IGESReaderData>&    IR,
  IGESData_ParamReader&                          PR) const
{
  // bool st; //szv#4:S4163:12Mar99 not needed

  occ::handle<IGESDimen_GeneralNote> note;
  occ::handle<IGESDimen_WitnessLine> firstWitness;
  occ::handle<IGESDimen_WitnessLine> secondWitness;
  gp_XY                              vertex;
  double                             radius;
  occ::handle<IGESDimen_LeaderArrow> firstLeader;
  occ::handle<IGESDimen_LeaderArrow> secondLeader;

  PR.ReadEntity(IR,
                PR.Current(),
                "General Note Entity",
                STANDARD_TYPE(IGESDimen_GeneralNote),
                note); // szv#4:S4163:12Mar99 `st=` not needed

  PR.ReadEntity(IR,
                PR.Current(),
                "First Witness Entity",
                // clang-format off
		 STANDARD_TYPE(IGESDimen_WitnessLine), firstWitness, true); //szv#4:S4163:12Mar99 `st=` not needed

  PR.ReadEntity (IR,PR.Current(),"Second Witness Entity",
		 STANDARD_TYPE(IGESDimen_WitnessLine), secondWitness, true); //szv#4:S4163:12Mar99 `st=` not needed

  PR.ReadXY(PR.CurrentList(1, 2), "Vertex Point Co-ords", vertex); //szv#4:S4163:12Mar99 `st=` not needed

  PR.ReadReal(PR.Current(), "Radius of Leader arcs", radius); //szv#4:S4163:12Mar99 `st=` not needed
  // clang-format on

  PR.ReadEntity(IR,
                PR.Current(),
                "First Leader Entity",
                STANDARD_TYPE(IGESDimen_LeaderArrow),
                firstLeader); // szv#4:S4163:12Mar99 `st=` not needed

  PR.ReadEntity(IR,
                PR.Current(),
                "Second Leader Entity",
                STANDARD_TYPE(IGESDimen_LeaderArrow),
                secondLeader); // szv#4:S4163:12Mar99 `st=` not needed

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(note, firstWitness, secondWitness, vertex, radius, firstLeader, secondLeader);
}

void IGESDimen_ToolAngularDimension::WriteOwnParams(
  const occ::handle<IGESDimen_AngularDimension>& ent,
  IGESData_IGESWriter&                           IW) const
{
  IW.Send(ent->Note());
  IW.Send(ent->FirstWitnessLine());
  IW.Send(ent->SecondWitnessLine());
  IW.Send(ent->Vertex().X());
  IW.Send(ent->Vertex().Y());
  IW.Send(ent->Radius());
  IW.Send(ent->FirstLeader());
  IW.Send(ent->SecondLeader());
}

void IGESDimen_ToolAngularDimension::OwnShared(const occ::handle<IGESDimen_AngularDimension>& ent,
                                               Interface_EntityIterator& iter) const
{
  iter.GetOneItem(ent->Note());
  iter.GetOneItem(ent->FirstWitnessLine());
  iter.GetOneItem(ent->SecondWitnessLine());
  iter.GetOneItem(ent->FirstLeader());
  iter.GetOneItem(ent->SecondLeader());
}

void IGESDimen_ToolAngularDimension::OwnCopy(const occ::handle<IGESDimen_AngularDimension>& another,
                                             const occ::handle<IGESDimen_AngularDimension>& ent,
                                             Interface_CopyTool& TC) const
{
  DeclareAndCast(IGESDimen_GeneralNote, note, TC.Transferred(another->Note()));
  DeclareAndCast(IGESDimen_WitnessLine, firstWitness, TC.Transferred(another->FirstWitnessLine()));
  DeclareAndCast(IGESDimen_WitnessLine,
                 secondWitness,
                 TC.Transferred(another->SecondWitnessLine()));
  gp_XY  vertex = (another->Vertex()).XY();
  double radius = another->Radius();
  DeclareAndCast(IGESDimen_LeaderArrow, firstLeader, TC.Transferred(another->FirstLeader()));
  DeclareAndCast(IGESDimen_LeaderArrow, secondLeader, TC.Transferred(another->SecondLeader()));

  ent->Init(note, firstWitness, secondWitness, vertex, radius, firstLeader, secondLeader);
}

IGESData_DirChecker IGESDimen_ToolAngularDimension::DirChecker(
  const occ::handle<IGESDimen_AngularDimension>& /* ent */) const
{
  IGESData_DirChecker DC(202, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);
  DC.UseFlagRequired(1);
  return DC;
}

void IGESDimen_ToolAngularDimension::OwnCheck(
  const occ::handle<IGESDimen_AngularDimension>& /* ent */,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>& /* ach */) const
{
}

void IGESDimen_ToolAngularDimension::OwnDump(const occ::handle<IGESDimen_AngularDimension>& ent,
                                             const IGESData_IGESDumper&                     dumper,
                                             Standard_OStream&                              S,
                                             const int level) const
{
  int sublevel = (level > 4) ? 1 : 0;

  S << "IGESDimen_AngularDimension\n"
    << "General Note Entity   : ";
  dumper.Dump(ent->Note(), S, sublevel);
  S << "\n"
    << "First  Witness Entity : ";
  dumper.Dump(ent->FirstWitnessLine(), S, sublevel);
  S << "\n"
    << "Second Witness Entity : ";
  dumper.Dump(ent->SecondWitnessLine(), S, sublevel);
  S << "\n"
    << "Vertex Point Co-ords  : ";
  IGESData_DumpXYL(S, level, ent->Vertex(), ent->Location());
  S << "\n";
  S << "Radius of Leader arcs : " << ent->Radius() << "\n"
    << "First  Leader Entity  : ";
  dumper.Dump(ent->FirstLeader(), S, sublevel);
  S << "\n"
    << "Second Leader Entity  : ";
  dumper.Dump(ent->SecondLeader(), S, sublevel);
  S << std::endl;
}
