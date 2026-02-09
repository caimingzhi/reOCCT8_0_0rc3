#include <gp_XYZ.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGeom_BSplineSurface.hpp>
#include <IGESGeom_ToolBSplineSurface.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Msg.hpp>
#include <Standard_DomainError.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IGESGeom_ToolBSplineSurface::IGESGeom_ToolBSplineSurface() = default;

void IGESGeom_ToolBSplineSurface::ReadOwnParams(const occ::handle<IGESGeom_BSplineSurface>& ent,
                                                const occ::handle<IGESData_IGESReaderData>&,
                                                IGESData_ParamReader& PR) const
{

  Message_Msg Msg100("XSTEP_100");
  Message_Msg Msg101("XSTEP_101");
  Message_Msg Msg102("XSTEP_102");
  Message_Msg Msg103("XSTEP_103");
  Message_Msg Msg159("XSTEP_159");

  int                                      I, J;
  int                                      anIndexU, anIndexV, aDegU, aDegV;
  bool                                     aCloseU, aCloseV, aPolynom, aPeriodU, aPeriodV;
  double                                   aUmin, aUmax, aVmin = 0., aVmax = 0.;
  double                                   tempVal;
  gp_XYZ                                   tempXYZ;
  occ::handle<NCollection_HArray1<double>> allKnotsU;
  occ::handle<NCollection_HArray1<double>> allKnotsV;
  occ::handle<NCollection_HArray2<double>> allWeights;
  occ::handle<NCollection_HArray2<gp_XYZ>> allPoles;

  bool FlagindexU = PR.ReadInteger(PR.Current(), anIndexU);

  bool FlagindexV = PR.ReadInteger(PR.Current(), anIndexV);

  if (!FlagindexU || !FlagindexV)
  {
    Message_Msg Msg97("XSTEP_97");
    PR.SendFail(Msg97);
  }

  bool FlagdegU = PR.ReadInteger(PR.Current(), aDegU);

  bool FlagdegV = PR.ReadInteger(PR.Current(), aDegV);

  if (!FlagdegU || !FlagdegV)
  {
    Message_Msg Msg98("XSTEP_98");
    PR.SendFail(Msg98);
  }

  PR.ReadBoolean(PR.Current(), Msg100, aCloseU);
  PR.ReadBoolean(PR.Current(), Msg100, aCloseV);
  PR.ReadBoolean(PR.Current(), Msg101, aPolynom);
  PR.ReadBoolean(PR.Current(), Msg102, aPeriodU);
  PR.ReadBoolean(PR.Current(), Msg102, aPeriodV);

  if (FlagdegU && FlagindexU)
  {

    int tempind = anIndexU + aDegU + 2;

    PR.ReadReals(PR.CurrentList(tempind), Msg103, allKnotsU, -aDegU);
  }

  if (FlagdegV && FlagindexV)
  {

    int tempind = anIndexV + aDegV + 2;
    PR.ReadReals(PR.CurrentList(tempind), Msg103, allKnotsV, -aDegV);
  }

  if (FlagindexU && FlagindexV)
  {
    allWeights = new NCollection_HArray2<double>(0, anIndexU, 0, anIndexV);
    allPoles   = new NCollection_HArray2<gp_XYZ>(0, anIndexU, 0, anIndexV);

    bool        BadWeigth = false;
    Message_Msg Msg105("XSTEP_105");

    for (J = 0; J <= anIndexV; J++)
    {
      for (I = 0; I <= anIndexU; I++)
      {

        if (PR.ReadReal(PR.Current(), tempVal))
        {
          if (tempVal < Precision::PConfusion())
          {
            BadWeigth = true;
          }
          allWeights->SetValue(I, J, tempVal);
        }
        else
        {
          Message_Msg Msg104("XSTEP_104");
          PR.SendFail(Msg104);
        }
      }
    }
    if (BadWeigth)
    {
      for (J = 0; J <= anIndexV; J++)
      {
        for (I = 0; I <= anIndexU; I++)
        {
          allWeights->SetValue(I, J, 1.);
        }
      }
    }

    for (J = 0; J <= anIndexV; J++)
      for (I = 0; I <= anIndexU; I++)
      {

        if (PR.ReadXYZ(PR.CurrentList(1, 3), Msg105, tempXYZ))
          allPoles->SetValue(I, J, tempXYZ);
      }
  }

  if (!PR.ReadReal(PR.Current(), aUmin) || !PR.ReadReal(PR.Current(), aVmin))
  {
    Message_Msg Msg106("XSTEP_106");
    PR.SendFail(Msg106);
  }

  if (!PR.ReadReal(PR.Current(), aUmax) || !PR.ReadReal(PR.Current(), aVmax))
  {
    Message_Msg Msg107("XSTEP_107");
    PR.SendFail(Msg107);
  }

  int    icur = PR.CurrentNumber(), imax = PR.NbParams();
  double bid;
  int    pbfin = 0;

  while (imax >= icur)
  {
    Interface_ParamType pt = PR.ParamType(icur);
    if (pt == Interface_ParamReal)
    {
      if (!PR.ReadReal(PR.Current(), bid))
      {
        PR.SendFail(Msg159);
      }
      if (pbfin == 0)
        pbfin = 1;
    }
    else if (pt == Interface_ParamInteger || pt == Interface_ParamVoid)
      break;
    else
      pbfin = -1;
    icur++;
  }
  if (pbfin > 0)
    PR.SendWarning(Msg159);
  if (pbfin < 0)
  {
    Message_Msg Msg158("XSTEP_158");
    PR.SendFail(Msg158);
  }
  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(anIndexU,
            anIndexV,
            aDegU,
            aDegV,
            aCloseU,
            aCloseV,
            aPolynom,
            aPeriodU,
            aPeriodV,
            allKnotsU,
            allKnotsV,
            allWeights,
            allPoles,
            aUmin,
            aUmax,
            aVmin,
            aVmax);
}

void IGESGeom_ToolBSplineSurface::WriteOwnParams(const occ::handle<IGESGeom_BSplineSurface>& ent,
                                                 IGESData_IGESWriter& IW) const
{
  int indU = ent->UpperIndexU();
  int indV = ent->UpperIndexV();
  int degU = ent->DegreeU();
  int degV = ent->DegreeV();
  int I, J;
  IW.Send(indU);
  IW.Send(indV);
  IW.Send(degU);
  IW.Send(degV);
  IW.SendBoolean(ent->IsClosedU());
  IW.SendBoolean(ent->IsClosedV());
  IW.SendBoolean(ent->IsPolynomial());
  IW.SendBoolean(ent->IsPeriodicU());
  IW.SendBoolean(ent->IsPeriodicV());

  for (I = -degU; I <= indU + 1; I++)
    IW.Send(ent->KnotU(I));

  for (I = -degV; I <= indV + 1; I++)
    IW.Send(ent->KnotV(I));

  for (J = 0; J <= indV; J++)
    for (I = 0; I <= indU; I++)
      IW.Send(ent->Weight(I, J));

  for (J = 0; J <= indV; J++)
    for (I = 0; I <= indU; I++)
    {
      gp_XYZ tempXYZ = ent->Pole(I, J).XYZ();
      IW.Send(tempXYZ.X());
      IW.Send(tempXYZ.Y());
      IW.Send(tempXYZ.Z());
    }
  IW.Send(ent->UMin());
  IW.Send(ent->UMax());
  IW.Send(ent->VMin());
  IW.Send(ent->VMax());
}

void IGESGeom_ToolBSplineSurface::OwnShared(const occ::handle<IGESGeom_BSplineSurface>&,
                                            Interface_EntityIterator&) const
{
}

void IGESGeom_ToolBSplineSurface::OwnCopy(const occ::handle<IGESGeom_BSplineSurface>& another,
                                          const occ::handle<IGESGeom_BSplineSurface>& ent,
                                          Interface_CopyTool&) const
{
  int    I, J;
  int    anIndexU, anIndexV, aDegU, aDegV;
  bool   aCloseU, aCloseV, aPolynom;
  bool   aPeriodU, aPeriodV;
  double aUmin, aUmax, aVmin, aVmax;

  anIndexU = another->UpperIndexU();
  anIndexV = another->UpperIndexV();
  aDegU    = another->DegreeU();
  aDegV    = another->DegreeV();
  aCloseU  = another->IsClosedU();
  aCloseV  = another->IsClosedV();
  aPolynom = another->IsPolynomial();
  aPeriodU = another->IsPeriodicU();
  aPeriodV = another->IsPeriodicV();

  occ::handle<NCollection_HArray1<double>> allKnotsU =
    new NCollection_HArray1<double>(-aDegU, anIndexU + 1);
  occ::handle<NCollection_HArray1<double>> allKnotsV =
    new NCollection_HArray1<double>(-aDegV, anIndexV + 1);

  for (I = -aDegU; I <= anIndexU + 1; I++)
    allKnotsU->SetValue(I, another->KnotU(I));

  for (I = -aDegV; I <= anIndexV + 1; I++)
    allKnotsV->SetValue(I, another->KnotV(I));

  occ::handle<NCollection_HArray2<double>> allWeights =
    new NCollection_HArray2<double>(0, anIndexU, 0, anIndexV);
  occ::handle<NCollection_HArray2<gp_XYZ>> allPoles =
    new NCollection_HArray2<gp_XYZ>(0, anIndexU, 0, anIndexV);

  for (J = 0; J <= anIndexV; J++)
    for (I = 0; I <= anIndexU; I++)
      allWeights->SetValue(I, J, another->Weight(I, J));

  for (J = 0; J <= anIndexV; J++)
    for (I = 0; I <= anIndexU; I++)
      allPoles->SetValue(I, J, another->Pole(I, J).XYZ());

  aUmin = another->UMin();
  aUmax = another->UMax();
  aVmin = another->VMin();
  aVmax = another->VMax();

  ent->Init(anIndexU,
            anIndexV,
            aDegU,
            aDegV,
            aCloseU,
            aCloseV,
            aPolynom,
            aPeriodU,
            aPeriodV,
            allKnotsU,
            allKnotsV,
            allWeights,
            allPoles,
            aUmin,
            aUmax,
            aVmin,
            aVmax);
  ent->SetFormNumber(another->FormNumber());
}

IGESData_DirChecker IGESGeom_ToolBSplineSurface::DirChecker(
  const occ::handle<IGESGeom_BSplineSurface>&) const
{
  IGESData_DirChecker DC(128, 0, 9);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);

  DC.Color(IGESData_DefAny);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESGeom_ToolBSplineSurface::OwnCheck(const occ::handle<IGESGeom_BSplineSurface>& ent,
                                           const Interface_ShareTool&,
                                           occ::handle<Interface_Check>& ach) const
{

  bool Flag = true;
  int  indU = ent->UpperIndexU();
  int  indV = ent->UpperIndexV();
  int  I, J;

  if (ent->NbKnotsU() != (indU + ent->DegreeU() + 2))
  {
    Message_Msg Msg160("XSTEP_160");
    Msg160.Arg(indU + ent->DegreeU() + 2);
    ach->SendFail(Msg160);
  }
  if (ent->NbKnotsV() != (indV + ent->DegreeV() + 2))
  {
    Message_Msg Msg161("XSTEP_161");
    Msg161.Arg(indV + ent->DegreeV() + 2);
    ach->SendFail(Msg161);
  }

  for (J = 0; ((J < indV) && (Flag)); J++)
    for (I = 0; ((I < indU) && (Flag)); I++)
      Flag &= (ent->Weight(I, J) > 0);

  if (!Flag)
  {
    Message_Msg Msg104("XSTEP_104");
    ach->SendFail(Msg104);
  }

  Flag           = true;
  double tempVal = ent->Weight(0, 0);

  for (J = 0; ((J < indV) && (Flag)); J++)
    for (I = 0; ((I < indU) && (Flag)); I++)
      Flag &= (ent->Weight(I, J) == tempVal);
}

void IGESGeom_ToolBSplineSurface::OwnDump(const occ::handle<IGESGeom_BSplineSurface>& ent,
                                          const IGESData_IGESDumper&,
                                          Standard_OStream& S,
                                          const int         level) const
{
  S << "BSplineSurface from IGESGeom\n\n";

  int indU = ent->UpperIndexU();
  int indV = ent->UpperIndexV();
  int degU = ent->DegreeU();
  int degV = ent->DegreeV();

  S << "In U : Upper Knot Index : " << indU << "   Degree : " << degU << "  "
    << (ent->IsClosedU() ? "Closed" : "Open") << "  "
    << (ent->IsPeriodicU() ? "Periodic" : "Non Periodic") << "\n"
    << "In V : Upper Knot Index : " << indV << "   Degree : " << degV << "  "
    << (ent->IsClosedV() ? "Closed" : "Open") << "  "
    << (ent->IsPeriodicV() ? "Periodic" : "Non Periodic") << "  "
    << (ent->IsPolynomial(true) ? "Polynomial" : "Rational") << "\n";

  S << "Starting Parameter for U direction : " << ent->UMin() << "\n"
    << "Ending   Parameter for U direction : " << ent->UMax() << "\n"
    << "Starting Parameter for V direction : " << ent->VMin() << "\n"
    << "Ending   Parameter for V direction : " << ent->VMax() << "\n";

  S << " Knots in  U : ";
  IGESData_DumpVals(S, level, -degU, indU + 1, ent->KnotU);
  S << "\n"
    << " Knots in  V : ";
  IGESData_DumpVals(S, level, -degV, indV + 1, ent->KnotV);
  S << "\n"
    << "Weights : (Row -> IndexU, Col -> IndexV)";
  IGESData_DumpRectVals(S, level, 0, indU, 0, indV, ent->Weight);
  S << "\n"
    << "Control Points (Poles) : ";

  if (level < 5)
  {
    S << " [ content : ask level > 4 ]" << std::endl;
    return;
  }
  gp_GTrsf loca = ent->Location();
  for (int JP = 0; JP <= indV; JP++)
    for (int IP = 0; IP <= indU; IP++)
    {
      if (IP == 0)
        S << "\n";
      S << "  -  [" << IP << "," << JP << "]: ";
      IGESData_DumpXYZL(S, level, ent->Pole(IP, JP), loca);
    }
  S << std::endl;
}
