#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <IGESDimen_LinearDimension.hpp>
#include <IGESDimen_ToolLinearDimension.hpp>
#include <IGESDimen_WitnessLine.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>

IGESDimen_ToolLinearDimension::IGESDimen_ToolLinearDimension() = default;

void IGESDimen_ToolLinearDimension::ReadOwnParams(const occ::handle<IGESDimen_LinearDimension>& ent,
                                                  const occ::handle<IGESData_IGESReaderData>&   IR,
                                                  IGESData_ParamReader& PR) const
{

  occ::handle<IGESDimen_GeneralNote> note;
  occ::handle<IGESDimen_LeaderArrow> firstLeader;
  occ::handle<IGESDimen_LeaderArrow> secondLeader;
  occ::handle<IGESDimen_WitnessLine> firstWitness;
  occ::handle<IGESDimen_WitnessLine> secondWitness;

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
                secondLeader);

  PR.ReadEntity(IR,
                PR.Current(),
                "First Witness Entity",

                STANDARD_TYPE(IGESDimen_WitnessLine),
                firstWitness,
                true);

  PR.ReadEntity(IR,
                PR.Current(),
                "Second Witness Entity",
                STANDARD_TYPE(IGESDimen_WitnessLine),
                secondWitness,
                true);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(note, firstLeader, secondLeader, firstWitness, secondWitness);
}

void IGESDimen_ToolLinearDimension::WriteOwnParams(
  const occ::handle<IGESDimen_LinearDimension>& ent,
  IGESData_IGESWriter&                          IW) const
{
  IW.Send(ent->Note());
  IW.Send(ent->FirstLeader());
  IW.Send(ent->SecondLeader());
  IW.Send(ent->FirstWitness());
  IW.Send(ent->SecondWitness());
}

void IGESDimen_ToolLinearDimension::OwnShared(const occ::handle<IGESDimen_LinearDimension>& ent,
                                              Interface_EntityIterator& iter) const
{
  iter.GetOneItem(ent->Note());
  iter.GetOneItem(ent->FirstLeader());
  iter.GetOneItem(ent->SecondLeader());
  iter.GetOneItem(ent->FirstWitness());
  iter.GetOneItem(ent->SecondWitness());
}

void IGESDimen_ToolLinearDimension::OwnCopy(const occ::handle<IGESDimen_LinearDimension>& another,
                                            const occ::handle<IGESDimen_LinearDimension>& ent,
                                            Interface_CopyTool&                           TC) const
{
  DeclareAndCast(IGESDimen_GeneralNote, note, TC.Transferred(another->Note()));
  DeclareAndCast(IGESDimen_LeaderArrow, firstLeader, TC.Transferred(another->FirstLeader()));
  DeclareAndCast(IGESDimen_LeaderArrow, secondLeader, TC.Transferred(another->SecondLeader()));
  DeclareAndCast(IGESDimen_WitnessLine, firstWitness, TC.Transferred(another->FirstWitness()));
  DeclareAndCast(IGESDimen_WitnessLine, secondWitness, TC.Transferred(another->SecondWitness()));

  ent->Init(note, firstLeader, secondLeader, firstWitness, secondWitness);
  ent->SetFormNumber(another->FormNumber());
}

IGESData_DirChecker IGESDimen_ToolLinearDimension::DirChecker(
  const occ::handle<IGESDimen_LinearDimension>&) const
{
  IGESData_DirChecker DC(216, 0, 2);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);
  DC.UseFlagRequired(1);
  return DC;
}

void IGESDimen_ToolLinearDimension::OwnCheck(const occ::handle<IGESDimen_LinearDimension>&,
                                             const Interface_ShareTool&,
                                             occ::handle<Interface_Check>&) const
{
}

void IGESDimen_ToolLinearDimension::OwnDump(const occ::handle<IGESDimen_LinearDimension>& ent,
                                            const IGESData_IGESDumper&                    dumper,
                                            Standard_OStream&                             S,
                                            const int level) const
{
  int sublevel = (level > 4) ? 1 : 0;

  S << "IGESDimen_LinearDimension\n";
  if (ent->FormNumber() == 0)
    S << "     (Undetermined Form)\n";
  else if (ent->FormNumber() == 1)
    S << "     (Diameter Form)\n";
  else if (ent->FormNumber() == 2)
    S << "     (Radius Form)\n";
  S << "General Note Entity : ";
  dumper.Dump(ent->Note(), S, sublevel);
  S << "\n"
    << "First  Leader  Entity : ";
  dumper.Dump(ent->FirstLeader(), S, sublevel);
  S << "\n"
    << "Second Leader  Entity : ";
  dumper.Dump(ent->SecondLeader(), S, sublevel);
  S << "\n"
    << "First  Witness Entity : ";
  dumper.Dump(ent->FirstWitness(), S, sublevel);
  S << "\n"
    << "Second Witness Entity : ";
  dumper.Dump(ent->SecondWitness(), S, sublevel);
  S << std::endl;
}
