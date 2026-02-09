#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGeom_CompositeCurve.hpp>
#include <IGESGeom_ToolCompositeCurve.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <Message_Msg.hpp>

IGESGeom_ToolCompositeCurve::IGESGeom_ToolCompositeCurve() = default;

void IGESGeom_ToolCompositeCurve::ReadOwnParams(const occ::handle<IGESGeom_CompositeCurve>& ent,
                                                const occ::handle<IGESData_IGESReaderData>& IR,
                                                IGESData_ParamReader& PR) const
{

  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> tempEntities;

  int num;

  bool st = PR.ReadInteger(PR.Current(), num);

  if (st && (num > 0))
  {
    Message_Msg Msg80("XSTEP_80");

    PR.ReadEnts(IR, PR.CurrentList(num), Msg80, tempEntities);
  }

  else
  {
    Message_Msg Msg79("XSTEP_79");
    PR.SendFail(Msg79);
  }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempEntities);
}

void IGESGeom_ToolCompositeCurve::WriteOwnParams(const occ::handle<IGESGeom_CompositeCurve>& ent,
                                                 IGESData_IGESWriter& IW) const
{
  int num = ent->NbCurves();
  int i;
  IW.Send(num);
  for (num = ent->NbCurves(), i = 1; i <= num; i++)
    IW.Send(ent->Curve(i));
}

void IGESGeom_ToolCompositeCurve::OwnShared(const occ::handle<IGESGeom_CompositeCurve>& ent,
                                            Interface_EntityIterator&                   iter) const
{
  int num = ent->NbCurves();
  for (int i = 1; i <= num; i++)
    iter.GetOneItem(ent->Curve(i));
}

void IGESGeom_ToolCompositeCurve::OwnCopy(const occ::handle<IGESGeom_CompositeCurve>& another,
                                          const occ::handle<IGESGeom_CompositeCurve>& ent,
                                          Interface_CopyTool&                         TC) const
{
  int                                                                i, num = another->NbCurves();
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> tempEntities =
    new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, num);
  for (i = 1; i <= num; i++)
  {
    DeclareAndCast(IGESData_IGESEntity, new_ent, TC.Transferred(another->Curve(i)));
    tempEntities->SetValue(i, new_ent);
  }
  ent->Init(tempEntities);
}

IGESData_DirChecker IGESGeom_ToolCompositeCurve::DirChecker(
  const occ::handle<IGESGeom_CompositeCurve>&) const
{
  IGESData_DirChecker DC(102, 0);
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.LineFont(IGESData_DefAny);

  DC.Color(IGESData_DefAny);
  return DC;
}

void IGESGeom_ToolCompositeCurve::OwnCheck(const occ::handle<IGESGeom_CompositeCurve>&,
                                           const Interface_ShareTool&,
                                           occ::handle<Interface_Check>&) const
{
}

void IGESGeom_ToolCompositeCurve::OwnDump(const occ::handle<IGESGeom_CompositeCurve>& ent,
                                          const IGESData_IGESDumper&                  dumper,
                                          Standard_OStream&                           S,
                                          const int                                   level) const
{
  S << "IGESGeom_CompositeCurve\n"
    << "Curve Entities :\n";
  IGESData_DumpEntities(S, dumper, level, 1, ent->NbCurves(), ent->Curve);
  S << std::endl;
}
