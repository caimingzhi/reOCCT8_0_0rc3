#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <IGESDimen_PointDimension.hpp>
#include <IGESDimen_ToolPointDimension.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>

IGESDimen_ToolPointDimension::IGESDimen_ToolPointDimension() = default;

void IGESDimen_ToolPointDimension::ReadOwnParams(const occ::handle<IGESDimen_PointDimension>& ent,
                                                 const occ::handle<IGESData_IGESReaderData>&  IR,
                                                 IGESData_ParamReader& PR) const
{
  occ::handle<IGESDimen_GeneralNote> tempNote;
  occ::handle<IGESDimen_LeaderArrow> leadArr;
  occ::handle<IGESData_IGESEntity>   tempGeom;
  // bool st; //szv#4:S4163:12Mar99 not needed

  PR.ReadEntity(IR,
                PR.Current(),
                "General Note",
                STANDARD_TYPE(IGESDimen_GeneralNote),
                tempNote); // szv#4:S4163:12Mar99 `st=` not needed

  PR.ReadEntity(IR,
                PR.Current(),
                "Leader",
                STANDARD_TYPE(IGESDimen_LeaderArrow),
                leadArr); // szv#4:S4163:12Mar99 `st=` not needed

  if (PR.IsParamEntity(PR.CurrentNumber()))
    // clang-format off
    PR.ReadEntity(IR, PR.Current(), "Enclosing entity", tempGeom); //szv#4:S4163:12Mar99 `st=` not needed
  // clang-format on

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempNote, leadArr, tempGeom);
}

void IGESDimen_ToolPointDimension::WriteOwnParams(const occ::handle<IGESDimen_PointDimension>& ent,
                                                  IGESData_IGESWriter& IW) const
{
  IW.Send(ent->Note());
  IW.Send(ent->LeaderArrow());
  IW.Send(ent->Geom());
}

void IGESDimen_ToolPointDimension::OwnShared(const occ::handle<IGESDimen_PointDimension>& ent,
                                             Interface_EntityIterator& iter) const
{
  iter.GetOneItem(ent->Note());
  iter.GetOneItem(ent->LeaderArrow());
  iter.GetOneItem(ent->Geom());
}

void IGESDimen_ToolPointDimension::OwnCopy(const occ::handle<IGESDimen_PointDimension>& another,
                                           const occ::handle<IGESDimen_PointDimension>& ent,
                                           Interface_CopyTool&                          TC) const
{
  DeclareAndCast(IGESDimen_GeneralNote, tempNote, TC.Transferred(another->Note()));
  DeclareAndCast(IGESDimen_LeaderArrow, tempArrow, TC.Transferred(another->LeaderArrow()));
  DeclareAndCast(IGESData_IGESEntity, tempGeom, TC.Transferred(another->Geom()));
  ent->Init(tempNote, tempArrow, tempGeom);
}

IGESData_DirChecker IGESDimen_ToolPointDimension::DirChecker(
  const occ::handle<IGESDimen_PointDimension>& /*ent*/) const
{
  IGESData_DirChecker DC(220, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);

  DC.UseFlagRequired(1);

  return DC;
}

void IGESDimen_ToolPointDimension::OwnCheck(const occ::handle<IGESDimen_PointDimension>& /*ent*/,
                                            const Interface_ShareTool&,
                                            occ::handle<Interface_Check>& /*ach*/) const
{
}

void IGESDimen_ToolPointDimension::OwnDump(const occ::handle<IGESDimen_PointDimension>& ent,
                                           const IGESData_IGESDumper&                   dumper,
                                           Standard_OStream&                            S,
                                           const int                                    level) const
{
  S << "IGESDimen_PointDimension\n";
  int sublevel = (level <= 4) ? 0 : 1;

  S << "General Note : ";
  dumper.Dump(ent->Note(), S, sublevel);
  S << "\n"
    << "Leader Arrow : ";
  dumper.Dump(ent->LeaderArrow(), S, sublevel);
  S << "\n";
  if (!ent->Geom().IsNull())
  {
    S << "Enclosing Entity : ";
    dumper.Dump(ent->Geom(), S, sublevel);
    S << "\n";
  }
}
