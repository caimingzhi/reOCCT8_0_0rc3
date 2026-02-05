#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDimen_CurveDimension.hpp>
#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <IGESDimen_ToolCurveDimension.hpp>
#include <IGESDimen_WitnessLine.hpp>
#include <IGESGeom_Line.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>

IGESDimen_ToolCurveDimension::IGESDimen_ToolCurveDimension() = default;

void IGESDimen_ToolCurveDimension::ReadOwnParams(const occ::handle<IGESDimen_CurveDimension>& ent,
                                                 const occ::handle<IGESData_IGESReaderData>&  IR,
                                                 IGESData_ParamReader& PR) const
{
  // bool st; //szv#4:S4163:12Mar99 not needed

  occ::handle<IGESDimen_GeneralNote> note;
  occ::handle<IGESData_IGESEntity>   firstCurve;
  occ::handle<IGESData_IGESEntity>   secondCurve;
  occ::handle<IGESDimen_LeaderArrow> firstLeader;
  occ::handle<IGESDimen_LeaderArrow> secondLeader;
  occ::handle<IGESDimen_WitnessLine> firstWitness;
  occ::handle<IGESDimen_WitnessLine> secondWitness;

  PR.ReadEntity(IR,
                PR.Current(),
                "General Note Entity",
                STANDARD_TYPE(IGESDimen_GeneralNote),
                note); // szv#4:S4163:12Mar99 `st=` not needed

  // clang-format off
  PR.ReadEntity(IR, PR.Current(), "First Curve Entity", firstCurve); //szv#4:S4163:12Mar99 `st=` not needed
  // clang-format on

  PR.ReadEntity(IR,
                PR.Current(),
                "Second Curve Entity",
                secondCurve,
                true); // szv#4:S4163:12Mar99 `st=` not needed

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

  PR.ReadEntity(IR,
                PR.Current(),
                "First Witness Entity",
                // clang-format off
		 STANDARD_TYPE(IGESDimen_WitnessLine), firstWitness, true); //szv#4:S4163:12Mar99 `st=` not needed

  PR.ReadEntity (IR,PR.Current(),"Second Witness Entity",
		 STANDARD_TYPE(IGESDimen_WitnessLine), secondWitness, true); //szv#4:S4163:12Mar99 `st=` not needed
  // clang-format on

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(note, firstCurve, secondCurve, firstLeader, secondLeader, firstWitness, secondWitness);
}

void IGESDimen_ToolCurveDimension::WriteOwnParams(const occ::handle<IGESDimen_CurveDimension>& ent,
                                                  IGESData_IGESWriter& IW) const
{
  IW.Send(ent->Note());
  IW.Send(ent->FirstCurve());
  IW.Send(ent->SecondCurve());
  IW.Send(ent->FirstLeader());
  IW.Send(ent->SecondLeader());
  IW.Send(ent->FirstWitnessLine());
  IW.Send(ent->SecondWitnessLine());
}

void IGESDimen_ToolCurveDimension::OwnShared(const occ::handle<IGESDimen_CurveDimension>& ent,
                                             Interface_EntityIterator& iter) const
{
  iter.GetOneItem(ent->Note());
  iter.GetOneItem(ent->FirstCurve());
  iter.GetOneItem(ent->SecondCurve());
  iter.GetOneItem(ent->FirstLeader());
  iter.GetOneItem(ent->SecondLeader());
  iter.GetOneItem(ent->FirstWitnessLine());
  iter.GetOneItem(ent->SecondWitnessLine());
}

void IGESDimen_ToolCurveDimension::OwnCopy(const occ::handle<IGESDimen_CurveDimension>& another,
                                           const occ::handle<IGESDimen_CurveDimension>& ent,
                                           Interface_CopyTool&                          TC) const
{
  DeclareAndCast(IGESDimen_GeneralNote, note, TC.Transferred(another->Note()));
  DeclareAndCast(IGESData_IGESEntity, firstCurve, TC.Transferred(another->FirstCurve()));
  DeclareAndCast(IGESData_IGESEntity, secondCurve, TC.Transferred(another->SecondCurve()));
  DeclareAndCast(IGESDimen_LeaderArrow, firstLeader, TC.Transferred(another->FirstLeader()));
  DeclareAndCast(IGESDimen_LeaderArrow, secondLeader, TC.Transferred(another->SecondLeader()));
  DeclareAndCast(IGESDimen_WitnessLine, firstWitness, TC.Transferred(another->FirstWitnessLine()));
  DeclareAndCast(IGESDimen_WitnessLine,
                 secondWitness,
                 TC.Transferred(another->SecondWitnessLine()));

  ent->Init(note, firstCurve, secondCurve, firstLeader, secondLeader, firstWitness, secondWitness);
}

IGESData_DirChecker IGESDimen_ToolCurveDimension::DirChecker(
  const occ::handle<IGESDimen_CurveDimension>& /*ent*/) const
{
  IGESData_DirChecker DC(204, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);
  DC.UseFlagRequired(1);
  return DC;
}

void IGESDimen_ToolCurveDimension::OwnCheck(const occ::handle<IGESDimen_CurveDimension>& ent,
                                            const Interface_ShareTool&,
                                            occ::handle<Interface_Check>& ach) const
{
  if (ent->HasSecondCurve())
  {
    if (ent->FirstCurve()->IsKind(STANDARD_TYPE(IGESGeom_Line)))
      if (ent->SecondCurve()->IsKind(STANDARD_TYPE(IGESGeom_Line)))
        ach->AddWarning("Both curves are IGESGeom_Line Entities");
  }
}

void IGESDimen_ToolCurveDimension::OwnDump(const occ::handle<IGESDimen_CurveDimension>& ent,
                                           const IGESData_IGESDumper&                   dumper,
                                           Standard_OStream&                            S,
                                           const int                                    level) const
{
  int sublevel = (level > 4) ? 1 : 0;

  S << "IGESDimen_CurveDimension\n"
    << "General Note Entity   : ";
  dumper.Dump(ent->Note(), S, sublevel);
  S << "\n"
    << "First  Curve   Entity : ";
  dumper.Dump(ent->FirstCurve(), S, sublevel);
  S << "\n"
    << "Second Curve   Entity : ";
  dumper.Dump(ent->SecondCurve(), S, sublevel);
  S << "\n"
    << "First  Leader  Entity : ";
  dumper.Dump(ent->FirstLeader(), S, sublevel);
  S << "\n"
    << "Second Leader  Entity : ";
  dumper.Dump(ent->SecondLeader(), S, sublevel);
  S << "\n"
    << "First  Witness Entity : ";
  dumper.Dump(ent->FirstWitnessLine(), S, sublevel);
  S << "\n"
    << "Second Witness Entity : ";
  dumper.Dump(ent->SecondWitnessLine(), S, sublevel);
  S << std::endl;
}
