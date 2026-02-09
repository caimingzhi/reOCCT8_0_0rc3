#include <gp_XYZ.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGeom_BSplineCurve.hpp>
#include <IGESGeom_ToolBSplineCurve.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Msg.hpp>
#include <Standard_DomainError.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IGESGeom_ToolBSplineCurve::IGESGeom_ToolBSplineCurve() = default;

void IGESGeom_ToolBSplineCurve::ReadOwnParams(const occ::handle<IGESGeom_BSplineCurve>& ent,
                                              const occ::handle<IGESData_IGESReaderData>&,
                                              IGESData_ParamReader& PR) const
{

  Message_Msg Msg99("XSTEP_99");
  Message_Msg Msg100("XSTEP_100");
  Message_Msg Msg101("XSTEP_101");
  Message_Msg Msg102("XSTEP_102");
  Message_Msg Msg103("XSTEP_103");

  int                                      anIndex, aDegree;
  bool                                     aPlanar, aClosed, aPolynomial, aPeriodic;
  double                                   aUmin, aUmax, normX, normY, normZ;
  gp_XYZ                                   aNorm(0., 0., 0.);
  occ::handle<NCollection_HArray1<double>> allKnots;
  occ::handle<NCollection_HArray1<double>> allWeights;
  occ::handle<NCollection_HArray1<gp_XYZ>> allPoles;

  if (PR.ReadInteger(PR.Current(), anIndex))
  {
    if (anIndex < 0)
    {
      Message_Msg Msg97("XSTEP_97");
      PR.SendFail(Msg97);
      anIndex = 0;
    }
    else
    {
      allPoles = new NCollection_HArray1<gp_XYZ>(0, anIndex);
    }
  }
  else
  {
    Message_Msg Msg97("XSTEP_97");
    PR.SendFail(Msg97);
  }

  if (!PR.ReadInteger(PR.Current(), aDegree))
  {
    aDegree = 0;
    Message_Msg Msg98("XSTEP_98");
    PR.SendFail(Msg98);
  }

  PR.ReadBoolean(PR.Current(), Msg99, aPlanar);
  PR.ReadBoolean(PR.Current(), Msg100, aClosed);
  PR.ReadBoolean(PR.Current(), Msg101, aPolynomial);
  PR.ReadBoolean(PR.Current(), Msg102, aPeriodic);

  int nbKnots = anIndex + aDegree + 2;

  PR.ReadReals(PR.CurrentList(nbKnots), Msg103, allKnots, -aDegree);

  if (!allPoles.IsNull())
  {
    Message_Msg Msg104("XSTEP_104");
    Message_Msg Msg105("XSTEP_105");
    PR.ReadReals(PR.CurrentList(anIndex + 1), Msg104, allWeights, 0);

    for (int I = 0; I <= anIndex; I++)
    {
      gp_XYZ tempPole;

      if (PR.ReadXYZ(PR.CurrentList(1, 3), Msg105, tempPole))
        allPoles->SetValue(I, tempPole);
    }
  }

  if (!PR.ReadReal(PR.Current(), aUmin))
  {
    Message_Msg Msg106("XSTEP_106");
    PR.SendFail(Msg106);
  }
  if (!PR.ReadReal(PR.Current(), aUmax))
  {
    Message_Msg Msg107("XSTEP_107");
    PR.SendFail(Msg107);
  }

  bool st = false;
  if (PR.DefinedElseSkip())
  {
    st = PR.ReadReal(PR.Current(), normX);
    if (!st)
    {
      Message_Msg Msg108("XSTEP_108");
      PR.SendFail(Msg108);
    }
  }

  else
    normX = 0.;
  if (PR.DefinedElseSkip())
  {
    st = PR.ReadReal(PR.Current(), normY);
    if (!st)
    {
      Message_Msg Msg108("XSTEP_108");
      PR.SendFail(Msg108);
    }
  }

  else
    normY = 0.;
  if (PR.DefinedElseSkip())
  {
    st = PR.ReadReal(PR.Current(), normZ);
    if (!st)
    {
      Message_Msg Msg108("XSTEP_108");
      PR.SendFail(Msg108);
    }
  }

  else
    normZ = 0.;
  if (st)
    aNorm.SetCoord(normX, normY, normZ);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(anIndex,
            aDegree,
            aPlanar,
            aClosed,
            aPolynomial,
            aPeriodic,
            allKnots,
            allWeights,
            allPoles,
            aUmin,
            aUmax,
            aNorm);
}

void IGESGeom_ToolBSplineCurve::WriteOwnParams(const occ::handle<IGESGeom_BSplineCurve>& ent,
                                               IGESData_IGESWriter&                      IW) const
{
  int low, up;
  int I;
  int index  = ent->UpperIndex();
  int degree = ent->Degree();
  IW.Send(index);
  IW.Send(degree);
  IW.SendBoolean(ent->IsPlanar());
  IW.SendBoolean(ent->IsClosed());
  IW.SendBoolean(ent->IsPolynomial());
  IW.SendBoolean(ent->IsPeriodic());

  low = -degree;
  up  = index + 1;
  for (I = low; I <= up; I++)
    IW.Send(ent->Knot(I));

  low = 0;
  up  = index;
  for (I = low; I <= up; I++)
    IW.Send(ent->Weight(I));

  for (I = low; I <= up; I++)
  {
    IW.Send((ent->Pole(I)).X());
    IW.Send((ent->Pole(I)).Y());
    IW.Send((ent->Pole(I)).Z());
  }
  IW.Send(ent->UMin());
  IW.Send(ent->UMax());
  IW.Send(ent->Normal().X());
  IW.Send(ent->Normal().Y());
  IW.Send(ent->Normal().Z());
}

void IGESGeom_ToolBSplineCurve::OwnShared(const occ::handle<IGESGeom_BSplineCurve>&,
                                          Interface_EntityIterator&) const
{
}

void IGESGeom_ToolBSplineCurve::OwnCopy(const occ::handle<IGESGeom_BSplineCurve>& another,
                                        const occ::handle<IGESGeom_BSplineCurve>& ent,
                                        Interface_CopyTool&) const
{
  int                                      I;
  int                                      low, up;
  int                                      anIndex, aDegree;
  bool                                     aPlanar, aClosed, aPolynomial, aPeriodic;
  occ::handle<NCollection_HArray1<double>> allKnots, allWeights;
  occ::handle<NCollection_HArray1<gp_XYZ>> allPoles;
  double                                   aUmin, aUmax;
  gp_XYZ                                   aNorm;

  anIndex     = another->UpperIndex();
  aDegree     = another->Degree();
  aPlanar     = another->IsPlanar();
  aClosed     = another->IsClosed();
  aPolynomial = another->IsPolynomial();
  aPeriodic   = another->IsPeriodic();

  allKnots = new NCollection_HArray1<double>(-aDegree, anIndex + 1);

  low = -aDegree;
  up  = anIndex + 1;
  for (I = low; I <= up; I++)
    allKnots->SetValue(I, another->Knot(I));

  allWeights = new NCollection_HArray1<double>(0, anIndex);

  low = 0;
  up  = anIndex;
  for (I = low; I <= up; I++)
    allWeights->SetValue(I, another->Weight(I));

  allPoles = new NCollection_HArray1<gp_XYZ>(0, anIndex);

  for (I = low; I <= up; I++)
    allPoles->SetValue(I, (another->Pole(I)).XYZ());

  aUmin = another->UMin();
  aUmax = another->UMax();
  aNorm = another->Normal();

  ent->Init(anIndex,
            aDegree,
            aPlanar,
            aClosed,
            aPolynomial,
            aPeriodic,
            allKnots,
            allWeights,
            allPoles,
            aUmin,
            aUmax,
            aNorm);
}

IGESData_DirChecker IGESGeom_ToolBSplineCurve::DirChecker(
  const occ::handle<IGESGeom_BSplineCurve>&) const
{
  IGESData_DirChecker DC(126, 0, 5);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);

  DC.Color(IGESData_DefAny);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESGeom_ToolBSplineCurve::OwnCheck(const occ::handle<IGESGeom_BSplineCurve>& ent,
                                         const Interface_ShareTool&,
                                         occ::handle<Interface_Check>& ach) const
{

  double eps = 1.E-04;

  int  lower = 0;
  int  upper = ent->UpperIndex();
  bool Flag  = true;

  int I;
  for (I = 0; ((I < upper) && (Flag)); I++)
    Flag &= (ent->Weight(I) > 0);

  if (!Flag)
  {
    Message_Msg Msg104("XSTEP_104");
    ach->SendFail(Msg104);
  }

  Flag           = true;
  double tempVal = ent->Weight(lower);

  for (I = lower; ((I < upper) && (Flag)); I++)
    Flag &= (ent->Weight(I) == tempVal);

  if (ent->IsPlanar())
  {
    gp_XYZ aNorm  = ent->Normal();
    double epsn   = eps * 10.;
    double normod = aNorm.SquareModulus();
    if (normod < epsn)
    {
      Message_Msg Msg109("XSTEP_109");
      ach->AddWarning(Msg109);
    }
  }
}

void IGESGeom_ToolBSplineCurve::OwnDump(const occ::handle<IGESGeom_BSplineCurve>& ent,
                                        const IGESData_IGESDumper&,
                                        Standard_OStream& S,
                                        const int         level) const
{
  int upind = ent->UpperIndex();
  S << "BSplineCurve from IGESGeom\n"
    << "Sum UpperIndex : " << upind << "   Degree : " << ent->Degree() << "  "
    << (ent->IsPlanar() ? "Planar" : "NonPlanar") << "\n"
    << (ent->IsClosed() ? "Closed" : "Open") << "  "
    << (ent->IsPeriodic() ? "Periodic" : "NonPeriodic") << "  "
    << (ent->IsPolynomial(true) ? "Polynomial" : "Rational") << "\nKnots : ";
  IGESData_DumpVals(S, level, -ent->Degree(), upind + 1, ent->Knot);
  S << "\nWeights : ";
  IGESData_DumpVals(S, level, 0, upind, ent->Weight);
  S << "\nControl Points (Poles) : ";
  IGESData_DumpListXYZL(S, level, 0, upind, ent->Pole, ent->Location());
  S << "\nStarting Parameter Value : " << ent->UMin()
    << "  Ending Parameter Value : " << ent->UMax() << "\n"
    << "Unit Normal : ";
  IGESData_DumpXYZL(S, level, ent->Normal(), ent->Location());
  S << std::endl;
}
