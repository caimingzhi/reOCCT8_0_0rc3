#include <gp_Pnt.hpp>
#include <gp_XY.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_LineFontEntity.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDimen_CenterLine.hpp>
#include <IGESDimen_ToolCenterLine.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <Standard_DomainError.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IGESDimen_ToolCenterLine::IGESDimen_ToolCenterLine() = default;

void IGESDimen_ToolCenterLine::ReadOwnParams(const occ::handle<IGESDimen_CenterLine>& ent,
                                             const occ::handle<IGESData_IGESReaderData>& /* IR */,
                                             IGESData_ParamReader& PR) const
{
  // bool st; //szv#4:S4163:12Mar99 not needed

  int                                     datatype;
  double                                  zDisplacement;
  int                                     nbval;
  occ::handle<NCollection_HArray1<gp_XY>> dataPoints;

  // clang-format off
  PR.ReadInteger(PR.Current(), "Interpretation Flag", datatype); //szv#4:S4163:12Mar99 `st=` not needed

  bool st = PR.ReadInteger(PR.Current(), "Number of data points", nbval);
  if (st && nbval > 0)  dataPoints = new NCollection_HArray1<gp_XY>(1, nbval);
  else  PR.AddFail("Number of data points: Not Positive");

  PR.ReadReal(PR.Current(), "Common Z Displacement", zDisplacement); //szv#4:S4163:12Mar99 `st=` not needed
  // clang-format on

  if (!dataPoints.IsNull())
    for (int i = 1; i <= nbval; i++)
    {
      gp_XY tempXY;
      // st = PR.ReadXY(PR.CurrentList(1, 2), "Data Points", tempXY); //szv#4:S4163:12Mar99 moved in
      // if
      if (PR.ReadXY(PR.CurrentList(1, 2), "Data Points", tempXY))
        dataPoints->SetValue(i, tempXY);
    }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(datatype, zDisplacement, dataPoints);
}

void IGESDimen_ToolCenterLine::WriteOwnParams(const occ::handle<IGESDimen_CenterLine>& ent,
                                              IGESData_IGESWriter&                     IW) const
{
  int upper = ent->NbPoints();
  IW.Send(ent->Datatype());
  IW.Send(upper);
  IW.Send(ent->ZDisplacement());
  for (int i = 1; i <= upper; i++)
  {
    IW.Send((ent->Point(i)).X());
    IW.Send((ent->Point(i)).Y());
  }
}

void IGESDimen_ToolCenterLine::OwnShared(const occ::handle<IGESDimen_CenterLine>& /* ent */,
                                         Interface_EntityIterator& /* iter */) const
{
}

void IGESDimen_ToolCenterLine::OwnCopy(const occ::handle<IGESDimen_CenterLine>& another,
                                       const occ::handle<IGESDimen_CenterLine>& ent,
                                       Interface_CopyTool& /* TC */) const
{
  int    datatype      = another->Datatype();
  int    nbval         = another->NbPoints();
  double zDisplacement = another->ZDisplacement();

  occ::handle<NCollection_HArray1<gp_XY>> dataPoints = new NCollection_HArray1<gp_XY>(1, nbval);

  for (int i = 1; i <= nbval; i++)
  {
    gp_Pnt tempPnt = (another->Point(i));
    gp_XY  tempPnt2d(tempPnt.X(), tempPnt.Y());
    dataPoints->SetValue(i, tempPnt2d);
  }
  ent->Init(datatype, zDisplacement, dataPoints);
  ent->SetCrossHair(another->IsCrossHair());
}

bool IGESDimen_ToolCenterLine::OwnCorrect(const occ::handle<IGESDimen_CenterLine>& ent) const
{
  bool res = (ent->RankLineFont() != 1);
  if (res)
  {
    occ::handle<IGESData_LineFontEntity> nulfont;
    ent->InitLineFont(nulfont, 1);
  }
  if (ent->Datatype() == 1)
    return res;
  //  Force DataType = 1 -> reconstruct
  int nb = ent->NbPoints();
  if (nb == 0)
    return res; // nothing could be done (is this possible?)
  occ::handle<NCollection_HArray1<gp_XY>> pts = new NCollection_HArray1<gp_XY>(1, nb);
  for (int i = 1; i <= nb; i++)
    pts->SetValue(i, gp_XY(ent->Point(i).X(), ent->Point(i).Y()));
  ent->Init(1, ent->ZDisplacement(), pts);
  return true;
}

IGESData_DirChecker IGESDimen_ToolCenterLine::DirChecker(
  const occ::handle<IGESDimen_CenterLine>& /* ent */) const
{
  IGESData_DirChecker DC(106, 20, 21);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefValue);
  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);
  DC.UseFlagRequired(1);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESDimen_ToolCenterLine::OwnCheck(const occ::handle<IGESDimen_CenterLine>& ent,
                                        const Interface_ShareTool&,
                                        occ::handle<Interface_Check>& ach) const
{
  if (ent->RankLineFont() != 1)
    ach->AddFail("Line Font Pattern != 1");
  if (ent->Datatype() != 1)
    ach->AddFail("Interpretation Flag != 1");
  if (ent->NbPoints() % 2 != 0)
    ach->AddFail("Number of data points is not even");
}

void IGESDimen_ToolCenterLine::OwnDump(const occ::handle<IGESDimen_CenterLine>& ent,
                                       const IGESData_IGESDumper& /* dumper */,
                                       Standard_OStream& S,
                                       const int         level) const
{
  S << "IGESDimen_CenterLine\n";
  if (ent->IsCrossHair())
    S << "Cross Hair\n";
  else
    S << "Through Circle Centers\n";
  S << "Data Type : " << ent->Datatype() << "  "
    << "Number of Data Points : " << ent->NbPoints() << "  "
    << "Common Z displacement : " << ent->ZDisplacement() << "  "
    << "Data Points :\n";
  IGESData_DumpListXYLZ(S,
                        level,
                        1,
                        ent->NbPoints(),
                        ent->Point,
                        ent->Location(),
                        ent->ZDisplacement());
  S << std::endl;
}
