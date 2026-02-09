#include <Bnd_Box.hpp>
#include <BRepBndLib.hpp>
#include <BRepFeat_MakeCylindricalHole.hpp>
#include <BRepPrim_Cylinder.hpp>
#include <ElCLib.hpp>
#include <Geom_Curve.hpp>
#include <gp_Ax1.hpp>
#include <LocOpe_CurveShapeIntersector.hpp>
#include <LocOpe_PntFace.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <TopExp_Explorer.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Solid.hpp>
#include <NCollection_List.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <CSLib.hpp>

static void Baryc(const TopoDS_Shape&, gp_Pnt&);

static void BoxParameters(const TopoDS_Shape&, const gp_Ax1&, double&, double&);

static bool GetOffset(const LocOpe_PntFace& PntInfo,
                      const double          Radius,
                      const gp_Ax1&         Axis,
                      double&               outOff);

static void CreateCyl(const LocOpe_PntFace& PntInfoFirst,
                      const LocOpe_PntFace& PntInfoLast,
                      const double          Radius,
                      const gp_Ax1&         Axis,
                      TopoDS_Shell&         Cyl,
                      TopoDS_Face&          CylTopF,
                      TopoDS_Face&          CylBottF);

void BRepFeat_MakeCylindricalHole::Perform(const double Radius)
{
  const TopoDS_Shape& aObject = myArguments.First();
  if (aObject.IsNull() || !myAxDef)
  {
    throw Standard_ConstructionError();
  }

  myIsBlind = false;
  myStatus  = BRepFeat_NoError;

  LocOpe_CurveShapeIntersector theASI(myAxis, aObject);
  if (!theASI.IsDone() || theASI.NbPoints() <= 0)
  {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  double PMin, PMax;
  BoxParameters(aObject, myAxis, PMin, PMax);
  double Heigth  = 2. * (PMax - PMin);
  gp_XYZ theOrig = myAxis.Location().XYZ();
  theOrig += ((3. * PMin - PMax) / 2.) * myAxis.Direction().XYZ();
  gp_Pnt            p1_ao1(theOrig);
  gp_Ax2            a1_ao1(p1_ao1, myAxis.Direction());
  BRepPrim_Cylinder theCylinder(a1_ao1, Radius, Heigth);

  BRep_Builder B;
  TopoDS_Solid theTool;
  B.MakeSolid(theTool);
  B.Add(theTool, theCylinder.Shell());

  myTopFace  = theCylinder.TopFace();
  myBotFace  = theCylinder.BottomFace();
  myValidate = false;

  bool Fuse = false;

  AddTool(theTool);
  SetOperation(Fuse);
  BOPAlgo_BOP::Perform();
}

void BRepFeat_MakeCylindricalHole::PerformThruNext(const double Radius, const bool Cont)
{

  const TopoDS_Shape& aObject = myArguments.First();
  if (aObject.IsNull() || !myAxDef)
  {
    throw Standard_ConstructionError();
  }

  myIsBlind  = false;
  myValidate = Cont;
  myStatus   = BRepFeat_NoError;

  LocOpe_CurveShapeIntersector theASI(myAxis, aObject);
  if (!theASI.IsDone())
  {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  int                IndFrom, IndTo;
  TopAbs_Orientation theOr;
  LocOpe_PntFace     PntInfoFirst, PntInfoLast;
  bool               ok = theASI.LocalizeAfter(0., theOr, IndFrom, IndTo);
  if (ok)
  {
    if (theOr == TopAbs_FORWARD)
    {
      PntInfoFirst = theASI.Point(IndFrom);
      ok           = theASI.LocalizeAfter(IndTo, theOr, IndFrom, IndTo);
      if (ok)
      {
        if (theOr != TopAbs_REVERSED)
        {
          ok = false;
        }
        else
        {
          PntInfoLast = theASI.Point(IndTo);
        }
      }
    }
    else
    {
      PntInfoLast = theASI.Point(IndTo);
      ok          = theASI.LocalizeBefore(IndFrom, theOr, IndFrom, IndTo);
      if (ok)
      {
        if (theOr != TopAbs_FORWARD)
        {
          ok = false;
        }
        else
        {
          PntInfoFirst = theASI.Point(IndFrom);
        }
      }
    }
  }
  if (!ok)
  {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  TopoDS_Shell Cyl;
  CreateCyl(PntInfoFirst, PntInfoLast, Radius, myAxis, Cyl, myTopFace, myBotFace);

  BRep_Builder B;
  TopoDS_Solid theTool;
  B.MakeSolid(theTool);
  B.Add(theTool, Cyl);

  bool Fuse = false;
  AddTool(theTool);
  SetOperation(Fuse);
  BOPAlgo_BOP::Perform();
  NCollection_List<TopoDS_Shape> parts;
  PartsOfTool(parts);

  int                                      nbparts = 0;
  NCollection_List<TopoDS_Shape>::Iterator its(parts);
  for (; its.More(); its.Next())
  {
    nbparts++;
  }
  if (nbparts == 0)
  {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  if (nbparts >= 2)
  {

    double       First = PntInfoFirst.Parameter();
    double       Last  = PntInfoLast.Parameter();
    TopoDS_Shape tokeep;
    double       parbar, parmin = Last;
    gp_Pnt       Barycentre;
    for (its.Initialize(parts); its.More(); its.Next())
    {
      Baryc(its.Value(), Barycentre);
      parbar = ElCLib::LineParameter(myAxis, Barycentre);
      if (parbar >= First && parbar <= Last && parbar <= parmin)
      {
        parmin = parbar;
        tokeep = its.Value();
      }
    }

    if (tokeep.IsNull())
    {

      double dmin = RealLast();
      for (its.Initialize(parts); its.More(); its.Next())
      {
        Baryc(its.Value(), Barycentre);
        parbar = ElCLib::LineParameter(myAxis, Barycentre);
        if (parbar < First)
        {
          if (First - parbar < dmin)
          {
            dmin   = First - parbar;
            tokeep = its.Value();
          }
          else
          {
            if (parbar - Last < dmin)
            {
              dmin   = parbar - Last;
              tokeep = its.Value();
            }
          }
        }
      }
    }
    for (its.Initialize(parts); its.More(); its.Next())
    {
      if (tokeep.IsSame(its.Value()))
      {
        KeepPart(its.Value());
        break;
      }
    }
  }
}

void BRepFeat_MakeCylindricalHole::PerformUntilEnd(const double Radius, const bool Cont)
{

  const TopoDS_Shape& aObject = myArguments.First();
  if (aObject.IsNull() || !myAxDef)
  {
    throw Standard_ConstructionError();
  }

  myIsBlind  = false;
  myValidate = Cont;
  myStatus   = BRepFeat_NoError;

  LocOpe_CurveShapeIntersector theASI(myAxis, aObject);
  if (!theASI.IsDone())
  {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  int                IndFrom, IndTo;
  TopAbs_Orientation theOr;
  bool               ok = theASI.LocalizeAfter(0., theOr, IndFrom, IndTo);
  LocOpe_PntFace     PntInfoFirst, PntInfoLast;

  if (ok)
  {
    if (theOr == TopAbs_REVERSED)
    {
      ok = theASI.LocalizeBefore(IndFrom, theOr, IndFrom, IndTo);
    }
    if (ok && theOr == TopAbs_FORWARD)
    {
      PntInfoFirst = theASI.Point(IndFrom);
      ok           = theASI.LocalizeBefore(theASI.NbPoints() + 1, theOr, IndFrom, IndTo);
      if (ok)
      {
        if (theOr != TopAbs_REVERSED)
        {
          ok = false;
        }
        else
        {
          PntInfoLast = theASI.Point(IndTo);
        }
      }
    }
  }
  if (!ok)
  {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  TopoDS_Shell Cyl;
  CreateCyl(PntInfoFirst, PntInfoLast, Radius, myAxis, Cyl, myTopFace, myBotFace);

  BRep_Builder B;
  TopoDS_Solid theTool;
  B.MakeSolid(theTool);
  B.Add(theTool, Cyl);

  bool Fuse = false;
  AddTool(theTool);
  SetOperation(Fuse);
  BOPAlgo_BOP::Perform();
  NCollection_List<TopoDS_Shape> parts;
  PartsOfTool(parts);

  int                                      nbparts = 0;
  NCollection_List<TopoDS_Shape>::Iterator its(parts);
  for (; its.More(); its.Next())
  {
    nbparts++;
  }
  if (nbparts == 0)
  {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  if (nbparts >= 2)
  {
    double parbar;
    gp_Pnt Barycentre;
    for (its.Initialize(parts); its.More(); its.Next())
    {
      Baryc(its.Value(), Barycentre);
      parbar = ElCLib::LineParameter(myAxis, Barycentre);
      if (parbar > PntInfoFirst.Parameter())
      {
        KeepPart(its.Value());
      }
    }
  }
}

void BRepFeat_MakeCylindricalHole::Perform(const double Radius,
                                           const double PFrom,
                                           const double PTo,
                                           const bool   Cont)
{

  const TopoDS_Shape& aObject = myArguments.First();
  if (aObject.IsNull() || !myAxDef)
  {
    throw Standard_ConstructionError();
  }

  myIsBlind  = false;
  myValidate = Cont;
  myStatus   = BRepFeat_NoError;

  LocOpe_CurveShapeIntersector theASI(myAxis, aObject);
  if (!theASI.IsDone())
  {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  double thePFrom, thePTo;
  if (PFrom < PTo)
  {
    thePFrom = PFrom;
    thePTo   = PTo;
  }
  else
  {
    thePFrom = PTo;
    thePTo   = PFrom;
  }

  LocOpe_PntFace     PntInfoFirst, PntInfoLast;
  int                IndFrom, IndTo;
  TopAbs_Orientation theOr;
  bool               ok = theASI.LocalizeAfter(thePFrom, theOr, IndFrom, IndTo);
  if (ok)
  {
    if (theOr == TopAbs_REVERSED)
    {
      ok = theASI.LocalizeBefore(IndFrom, theOr, IndFrom, IndTo);
    }
    if (ok && theOr == TopAbs_FORWARD)
    {
      PntInfoFirst = theASI.Point(IndFrom);
      ok           = theASI.LocalizeBefore(thePTo, theOr, IndFrom, IndTo);
      if (ok)
      {
        if (theOr == TopAbs_FORWARD)
        {
          ok = theASI.LocalizeAfter(IndTo, theOr, IndFrom, IndTo);
        }
        if (ok && theOr == TopAbs_REVERSED)
        {
          PntInfoLast = theASI.Point(IndTo);
        }
      }
    }
  }

  if (!ok)
  {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  TopoDS_Shell Cyl;
  CreateCyl(PntInfoFirst, PntInfoLast, Radius, myAxis, Cyl, myTopFace, myBotFace);

  BRep_Builder B;
  TopoDS_Solid theTool;
  B.MakeSolid(theTool);
  B.Add(theTool, Cyl);

  bool Fuse = false;
  AddTool(theTool);
  SetOperation(Fuse);
  BOPAlgo_BOP::Perform();
  NCollection_List<TopoDS_Shape> parts;
  PartsOfTool(parts);

  int                                      nbparts = 0;
  NCollection_List<TopoDS_Shape>::Iterator its(parts);
  for (; its.More(); its.Next())
  {
    nbparts++;
  }
  if (nbparts == 0)
  {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  if (nbparts >= 2)
  {

    TopoDS_Shape tokeep;
    double       parbar;
    gp_Pnt       Barycentre;
    for (its.Initialize(parts); its.More(); its.Next())
    {
      Baryc(its.Value(), Barycentre);
      parbar = ElCLib::LineParameter(myAxis, Barycentre);
      if (parbar >= PntInfoFirst.Parameter() && parbar <= PntInfoLast.Parameter())
      {
        KeepPart(its.Value());
      }
    }
  }
}

void BRepFeat_MakeCylindricalHole::PerformBlind(const double Radius,
                                                const double Length,
                                                const bool   Cont)
{

  const TopoDS_Shape& aObject = myArguments.First();
  if (aObject.IsNull() || !myAxDef || Length <= 0.)
  {
    throw Standard_ConstructionError();
  }

  myIsBlind  = true;
  myValidate = Cont;
  myStatus   = BRepFeat_NoError;

  LocOpe_CurveShapeIntersector theASI(myAxis, aObject);
  if (!theASI.IsDone())
  {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  double             First;
  int                IndFrom, IndTo;
  TopAbs_Orientation theOr;
  bool               ok = theASI.LocalizeAfter(0., theOr, IndFrom, IndTo);

  if (ok)
  {
    if (theOr == TopAbs_REVERSED)
    {
      ok = theASI.LocalizeBefore(IndFrom, theOr, IndFrom, IndTo);
    }
    ok = ok && theOr == TopAbs_FORWARD;
  }
  if (!ok)
  {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  int IFNext, ITNext;
  ok = theASI.LocalizeAfter(IndTo, theOr, IFNext, ITNext);
  if (!ok)
  {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }
  if (theASI.Point(IFNext).Parameter() <= Length)
  {
    myStatus = BRepFeat_HoleTooLong;
    return;
  }

  NCollection_List<TopoDS_Shape> theList;

  for (int i = IndFrom; i <= ITNext; i++)
  {
    theList.Append(theASI.Point(i).Face());
  }

  First = theASI.Point(IndFrom).Parameter();

  double PMin, PMax;
  BoxParameters(aObject, myAxis, PMin, PMax);
  if (PMin > Length)
  {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  double Heigth  = 3. * (Length - PMin) / 2.;
  gp_XYZ theOrig = myAxis.Location().XYZ();
  theOrig += ((3. * PMin - Length) / 2.) * myAxis.Direction().XYZ();
  gp_Pnt            p5_ao1(theOrig);
  gp_Ax2            a5_ao1(p5_ao1, myAxis.Direction());
  BRepPrim_Cylinder theCylinder(a5_ao1, Radius, Heigth);

  BRep_Builder B;
  TopoDS_Solid theTool;
  B.MakeSolid(theTool);
  B.Add(theTool, theCylinder.Shell());

  myTopFace = theCylinder.TopFace();
  myBotFace.Nullify();

  bool Fuse = false;

  AddTool(theTool);
  SetOperation(Fuse);
  BOPAlgo_BOP::Perform();
  NCollection_List<TopoDS_Shape> parts;
  PartsOfTool(parts);

  int                                      nbparts = 0;
  NCollection_List<TopoDS_Shape>::Iterator its(parts);
  for (; its.More(); its.Next())
  {
    nbparts++;
  }
  if (nbparts == 0)
  {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  if (nbparts >= 2)
  {
    TopoDS_Shape tokeep;
    double       parbar, parmin = RealLast();
    gp_Pnt       Barycentre;
    for (its.Initialize(parts); its.More(); its.Next())
    {
      Baryc(its.Value(), Barycentre);
      parbar = ElCLib::LineParameter(myAxis, Barycentre);
      if (parbar >= First && parbar <= parmin)
      {
        parmin = parbar;
        tokeep = its.Value();
      }
    }

    if (tokeep.IsNull())
    {

      double dmin = RealLast();
      for (its.Initialize(parts); its.More(); its.Next())
      {
        Baryc(its.Value(), Barycentre);
        parbar = ElCLib::LineParameter(myAxis, Barycentre);
        if (std::abs(First - parbar) < dmin)
        {
          dmin   = std::abs(First - parbar);
          tokeep = its.Value();
        }
      }
    }
    for (its.Initialize(parts); its.More(); its.Next())
    {
      if (tokeep.IsSame(its.Value()))
      {
        KeepPart(its.Value());
        break;
      }
    }
  }
}

void BRepFeat_MakeCylindricalHole::Build()
{
  if (myStatus == BRepFeat_NoError)
  {
    PerformResult();
    if (!HasErrors())
    {
      myStatus = (myValidate) ? Validate() : BRepFeat_NoError;
      if (myStatus == BRepFeat_NoError)
      {
        myShape = Shape();
      }
    }
    else
    {
      myStatus = BRepFeat_InvalidPlacement;
    }
  }
}

BRepFeat_Status BRepFeat_MakeCylindricalHole::Validate()
{
  BRepFeat_Status thestat = BRepFeat_NoError;
  TopExp_Explorer ex(Shape(), TopAbs_FACE);
  if (myIsBlind)
  {
    for (; ex.More(); ex.Next())
    {
      if (ex.Current().IsSame(myTopFace))
      {
        break;
      }
    }
    if (!ex.More())
    {
      thestat = BRepFeat_HoleTooLong;
    }
  }
  else
  {
    for (; ex.More(); ex.Next())
    {
      if (ex.Current().IsSame(myTopFace))
      {
        return BRepFeat_InvalidPlacement;
      }
    }
    for (ex.ReInit(); ex.More(); ex.Next())
    {
      if (ex.Current().IsSame(myBotFace))
      {
        return BRepFeat_InvalidPlacement;
      }
    }
  }
  return thestat;
}

void Baryc(const TopoDS_Shape& S, gp_Pnt& B)
{
  TopExp_Explorer         exp(S, TopAbs_EDGE);
  gp_XYZ                  Bar(0., 0., 0.);
  TopLoc_Location         L;
  occ::handle<Geom_Curve> C;
  double                  prm, First, Last;

  int i, nbp = 0;
  for (; exp.More(); exp.Next())
  {

    const TopoDS_Edge& E = TopoDS::Edge(exp.Current());
    if (!BRep_Tool::Degenerated(E))
    {
      C = BRep_Tool::Curve(E, L, First, Last);
      C = occ::down_cast<Geom_Curve>(C->Transformed(L.Transformation()));
      for (i = 1; i <= 11; i++)
      {
        prm = ((11 - i) * First + (i - 1) * Last) / 10.;
        Bar += C->Value(prm).XYZ();
        nbp++;
      }
    }
  }
  Bar.Divide((double)nbp);
  B.SetXYZ(Bar);
}

void BoxParameters(const TopoDS_Shape& S, const gp_Ax1& Axis, double& parmin, double& parmax)
{

  Bnd_Box B;
  BRepBndLib::Add(S, B);
  double c[6];
  B.Get(c[0], c[2], c[4], c[1], c[3], c[5]);
  gp_Pnt P;
  int    i, j, k;
  parmin = RealLast();
  parmax = RealFirst();
  double param;
  for (i = 0; i <= 1; i++)
  {
    P.SetX(c[i]);
    for (j = 2; j <= 3; j++)
    {
      P.SetY(c[j]);
      for (k = 4; k <= 5; k++)
      {
        P.SetZ(c[k]);
        param  = ElCLib::LineParameter(Axis, P);
        parmin = std::min(param, parmin);
        parmax = std::max(param, parmax);
      }
    }
  }
}

bool GetOffset(const LocOpe_PntFace& PntInfo,
               const double          Radius,
               const gp_Ax1&         Axis,
               double&               outOff)
{
  const TopoDS_Face&  FF = PntInfo.Face();
  BRepAdaptor_Surface FFA(FF);

  double Up = PntInfo.UParameter();
  double Vp = PntInfo.VParameter();
  gp_Pnt PP;
  gp_Vec D1U, D1V;
  FFA.D1(Up, Vp, PP, D1U, D1V);
  gp_Dir             NormF;
  CSLib_NormalStatus stat;
  CSLib::Normal(D1U, D1V, Precision::Angular(), stat, NormF);
  if (stat != CSLib_Defined)
    return false;
  double angle = Axis.Direction().Angle(NormF);
  if (std::abs(M_PI / 2. - angle) < Precision::Angular())
    return false;
  outOff = Radius * std::abs(tan(angle));
  return true;
}

void CreateCyl(const LocOpe_PntFace& PntInfoFirst,
               const LocOpe_PntFace& PntInfoLast,
               const double          Radius,
               const gp_Ax1&         Axis,
               TopoDS_Shell&         Cyl,
               TopoDS_Face&          CylTopF,
               TopoDS_Face&          CylBottF)
{
  double First = 0, Last = 0;
  double offF = 0., offL = 0.;
  Last          = PntInfoLast.Parameter();
  First         = PntInfoFirst.Parameter();
  double Heigth = Last - First;

  if (!GetOffset(PntInfoFirst, Radius, Axis, offF))
    offF = Radius;
  if (!GetOffset(PntInfoLast, Radius, Axis, offL))
    offL = Radius;

  gp_XYZ            theOrig = PntInfoFirst.Pnt().XYZ() - offF * Axis.Direction().XYZ();
  gp_Pnt            p2_ao1(theOrig);
  gp_Ax2            a2_ao1(p2_ao1, Axis.Direction());
  BRepPrim_Cylinder theCylinder(a2_ao1, Radius, Heigth + offF + offL);
  Cyl      = theCylinder.Shell();
  CylTopF  = theCylinder.TopFace();
  CylBottF = theCylinder.BottomFace();
}
