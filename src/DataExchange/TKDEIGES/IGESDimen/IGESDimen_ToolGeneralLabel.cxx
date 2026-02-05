#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDimen_GeneralLabel.hpp>
#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESDimen_ToolGeneralLabel.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>

IGESDimen_ToolGeneralLabel::IGESDimen_ToolGeneralLabel() = default;

void IGESDimen_ToolGeneralLabel::ReadOwnParams(const occ::handle<IGESDimen_GeneralLabel>&  ent,
                                               const occ::handle<IGESData_IGESReaderData>& IR,
                                               IGESData_ParamReader&                       PR) const
{
  // bool st; //szv#4:S4163:12Mar99 moved down

  occ::handle<IGESDimen_GeneralNote>                                   note;
  int                                                                  nbval;
  occ::handle<NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>> leaders;

  PR.ReadEntity(IR,
                PR.Current(),
                "General Note Entity",
                STANDARD_TYPE(IGESDimen_GeneralNote),
                note); // szv#4:S4163:12Mar99 `st=` not needed

  bool st = PR.ReadInteger(PR.Current(), "Number of Leaders", nbval);
  if (st && nbval > 0)
    leaders = new NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>(1, nbval);
  else
    PR.AddFail("Number of Leaders: Not Positive");

  if (!leaders.IsNull())
    for (int i = 1; i <= nbval; i++)
    {
      occ::handle<IGESDimen_LeaderArrow> anentity;
      // st = PR.ReadEntity(IR, PR.Current(), "Leaders",
      // STANDARD_TYPE(IGESDimen_LeaderArrow), anentity); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadEntity(IR,
                        PR.Current(),
                        "Leaders",
                        STANDARD_TYPE(IGESDimen_LeaderArrow),
                        anentity))
        leaders->SetValue(i, anentity);
    }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(note, leaders);
}

void IGESDimen_ToolGeneralLabel::WriteOwnParams(const occ::handle<IGESDimen_GeneralLabel>& ent,
                                                IGESData_IGESWriter&                       IW) const
{
  int upper = ent->NbLeaders();
  IW.Send(ent->Note());
  IW.Send(upper);
  for (int i = 1; i <= upper; i++)
    IW.Send(ent->Leader(i));
}

void IGESDimen_ToolGeneralLabel::OwnShared(const occ::handle<IGESDimen_GeneralLabel>& ent,
                                           Interface_EntityIterator&                  iter) const
{
  int upper = ent->NbLeaders();
  iter.GetOneItem(ent->Note());
  for (int i = 1; i <= upper; i++)
    iter.GetOneItem(ent->Leader(i));
}

void IGESDimen_ToolGeneralLabel::OwnCopy(const occ::handle<IGESDimen_GeneralLabel>& another,
                                         const occ::handle<IGESDimen_GeneralLabel>& ent,
                                         Interface_CopyTool&                        TC) const
{
  DeclareAndCast(IGESDimen_GeneralNote, note, TC.Transferred(another->Note()));
  int nbval = another->NbLeaders();

  occ::handle<NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>> leaders =
    new NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>(1, nbval);
  for (int i = 1; i <= nbval; i++)
  {
    DeclareAndCast(IGESDimen_LeaderArrow, new_ent, TC.Transferred(another->Leader(i)));
    leaders->SetValue(i, new_ent);
  }
  ent->Init(note, leaders);
}

IGESData_DirChecker IGESDimen_ToolGeneralLabel::DirChecker(
  const occ::handle<IGESDimen_GeneralLabel>& /* ent */) const
{
  IGESData_DirChecker DC(210, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);
  DC.UseFlagRequired(1);
  return DC;
}

void IGESDimen_ToolGeneralLabel::OwnCheck(const occ::handle<IGESDimen_GeneralLabel>& /* ent */,
                                          const Interface_ShareTool&,
                                          occ::handle<Interface_Check>& /* ach */) const
{
}

void IGESDimen_ToolGeneralLabel::OwnDump(const occ::handle<IGESDimen_GeneralLabel>& ent,
                                         const IGESData_IGESDumper&                 dumper,
                                         Standard_OStream&                          S,
                                         const int                                  level) const
{
  int sublevel = (level > 4) ? 1 : 0;

  S << "IGESDimen_GeneralLabel\n"
    << "General Note Entity : ";
  dumper.Dump(ent->Note(), S, sublevel);
  S << "\n"
    << "Number of Leaders : " << ent->NbLeaders() << "\n"
    << "Leaders : ";
  IGESData_DumpEntities(S, dumper, level, 1, ent->NbLeaders(), ent->Leader);
  S << std::endl;
}
