#include <GeomPlate_BuildPlateSurface.hpp>

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Curve.hpp>
#include <Adaptor3d_CurveOnSurface.hpp>
#include <Approx_CurveOnSurface.hpp>
#include <Extrema_POnSurf.hpp>
#include <GCPnts_AbscissaPoint.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom2dInt_GInter.hpp>
#include <Geom_BSplineSurface.hpp>
#include <Geom_Plane.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_Surface.hpp>
#include <GeomAdaptor.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomLProp_SLProps.hpp>
#include <GeomPlate_BuildAveragePlane.hpp>
#include <GeomPlate_CurveConstraint.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <GeomPlate_MakeApprox.hpp>
#include <GeomPlate_PointConstraint.hpp>
#include <GeomPlate_Aij.hpp>
#include <GeomPlate_Surface.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <IntRes2d_IntersectionPoint.hpp>
#include <Law_Interpol.hpp>
#include <LocalAnalysis_SurfaceContinuity.hpp>
#include <Plate_D2.hpp>
#include <Plate_FreeGtoCConstraint.hpp>
#include <Plate_GtoCConstraint.hpp>
#include <Plate_PinpointConstraint.hpp>
#include <Plate_Plate.hpp>
#include <Precision.hpp>
#include <ProjLib_HCompProjectedCurve.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_Integer.hpp>
#include <Message_ProgressScope.hpp>

#include <cstdio>

#ifdef OCCT_DEBUG
  #include <OSD_Chronometer.hpp>
static int Affich = 0;
#endif

GeomPlate_BuildPlateSurface::GeomPlate_BuildPlateSurface(
  const occ::handle<NCollection_HArray1<int>>&                          NPoints,
  const occ::handle<NCollection_HArray1<occ::handle<Adaptor3d_Curve>>>& TabCurve,
  const occ::handle<NCollection_HArray1<int>>&                          Tang,
  const int                                                             Degree,
  const int                                                             NbIter,
  const double                                                          Tol2d,
  const double                                                          Tol3d,
  const double                                                          TolAng,
  const double,
  const bool Anisotropie)
    : myAnisotropie(Anisotropie),
      myDegree(Degree),
      myNbIter(NbIter),

      myTol2d(Tol2d),
      myTol3d(Tol3d),
      myTolAng(TolAng),
      myNbBounds(0)
{
  int NTCurve  = TabCurve->Length();
  myNbPtsOnCur = 0;
  myLinCont    = new NCollection_HSequence<occ::handle<GeomPlate_CurveConstraint>>;
  myPntCont    = new NCollection_HSequence<occ::handle<GeomPlate_PointConstraint>>;
  if (myNbIter < 1)
    throw Standard_ConstructionError("GeomPlate :  Number of iteration must be >= 1");

  if (NTCurve == 0)
    throw Standard_ConstructionError("GeomPlate : the bounds Array is null");
  if (Tang->Length() == 0)
    throw Standard_ConstructionError("GeomPlate : the constraints Array is null");
  int nbp = 0;
  int i;
  for (i = 1; i <= NTCurve; i++)
  {
    nbp += NPoints->Value(i);
  }
  if (nbp == 0)
    throw Standard_ConstructionError(
      "GeomPlate : the resolution is impossible if the number of constraints points is 0");
  if (myDegree < 2)
    throw Standard_ConstructionError("GeomPlate ; the degree resolution must be upper of 2");

  for (i = 1; i <= NTCurve; i++)
  {
    occ::handle<GeomPlate_CurveConstraint> Cont =
      new GeomPlate_CurveConstraint(TabCurve->Value(i), Tang->Value(i), NPoints->Value(i));
    myLinCont->Append(Cont);
  }
  mySurfInitIsGive = false;

  myIsLinear = true;
  myFree     = false;
}

GeomPlate_BuildPlateSurface::GeomPlate_BuildPlateSurface(const occ::handle<Geom_Surface>& Surf,
                                                         const int                        Degree,
                                                         const int    NbPtsOnCur,
                                                         const int    NbIter,
                                                         const double Tol2d,
                                                         const double Tol3d,
                                                         const double TolAng,
                                                         const double,
                                                         const bool Anisotropie)
    : mySurfInit(Surf),
      myAnisotropie(Anisotropie),
      myDegree(Degree),
      myNbPtsOnCur(NbPtsOnCur),
      myNbIter(NbIter),

      myTol2d(Tol2d),
      myTol3d(Tol3d),
      myTolAng(TolAng),
      myNbBounds(0)
{
  if (myNbIter < 1)
    throw Standard_ConstructionError("GeomPlate :  Number of iteration must be >= 1");
  if (myDegree < 2)
    throw Standard_ConstructionError("GeomPlate : the degree must be above 2");
  myLinCont        = new NCollection_HSequence<occ::handle<GeomPlate_CurveConstraint>>;
  myPntCont        = new NCollection_HSequence<occ::handle<GeomPlate_PointConstraint>>;
  mySurfInitIsGive = true;

  myIsLinear = true;
  myFree     = false;
}

GeomPlate_BuildPlateSurface::GeomPlate_BuildPlateSurface(const int    Degree,
                                                         const int    NbPtsOnCur,
                                                         const int    NbIter,
                                                         const double Tol2d,
                                                         const double Tol3d,
                                                         const double TolAng,
                                                         const double,
                                                         const bool Anisotropie)
    : myAnisotropie(Anisotropie),
      myDegree(Degree),
      myNbPtsOnCur(NbPtsOnCur),
      myNbIter(NbIter),

      myTol2d(Tol2d),
      myTol3d(Tol3d),
      myTolAng(TolAng),
      myNbBounds(0)
{
  if (myNbIter < 1)
    throw Standard_ConstructionError("GeomPlate :  Number of iteration must be >= 1");
  if (myDegree < 2)
    throw Standard_ConstructionError("GeomPlate : the degree resolution must be upper of 2");
  myLinCont        = new NCollection_HSequence<occ::handle<GeomPlate_CurveConstraint>>;
  myPntCont        = new NCollection_HSequence<occ::handle<GeomPlate_PointConstraint>>;
  mySurfInitIsGive = false;

  myIsLinear = true;
  myFree     = false;
}

static void TrierTab(occ::handle<NCollection_HArray1<int>>& Tab)
{

  int                     Nb = Tab->Length();
  NCollection_Array1<int> TabTri(1, Nb);
  for (int i = 1; i <= Nb; i++)
    TabTri.SetValue(Tab->Value(i), i);
  Tab->ChangeArray1() = TabTri;
}

occ::handle<Geom2d_Curve> GeomPlate_BuildPlateSurface::ProjectCurve(
  const occ::handle<Adaptor3d_Curve>& Curv)
{

  occ::handle<Geom2d_Curve>        Curve2d;
  occ::handle<GeomAdaptor_Surface> hsur = new GeomAdaptor_Surface(mySurfInit);
  gp_Pnt2d                         P2d;

  occ::handle<ProjLib_HCompProjectedCurve> HProjector =
    new ProjLib_HCompProjectedCurve(hsur, Curv, myTol3d / 10, myTol3d / 10);

  double UdebCheck, UfinCheck, ProjUdeb, ProjUfin;
  UdebCheck = Curv->FirstParameter();
  UfinCheck = Curv->LastParameter();
  HProjector->Bounds(1, ProjUdeb, ProjUfin);

  if (HProjector->NbCurves() != 1 || std::abs(UdebCheck - ProjUdeb) > Precision::PConfusion()
      || std::abs(UfinCheck - ProjUfin) > Precision::PConfusion())
  {
    if (HProjector->IsSinglePnt(1, P2d))
    {

      NCollection_Array1<gp_Pnt2d> poles(1, 2);
      poles.Init(P2d);
      Curve2d = new (Geom2d_BezierCurve)(poles);
    }
    else
    {
      Curve2d.Nullify();
#ifdef OCCT_DEBUG
      std::cout << "BuildPlateSurace :: No continuous projection" << std::endl;
#endif
    }
  }
  else
  {
    GeomAbs_Shape Continuity = GeomAbs_C1;
    int           MaxDegree  = 10, MaxSeg;
    double        Udeb, Ufin;
    HProjector->Bounds(1, Udeb, Ufin);

    MaxSeg = 20 + HProjector->NbIntervals(GeomAbs_C3);
    Approx_CurveOnSurface appr(HProjector, hsur, Udeb, Ufin, myTol3d);
    appr.Perform(MaxSeg, MaxDegree, Continuity, false, true);

    Curve2d = appr.Curve2d();
  }
  return Curve2d;
}

occ::handle<Adaptor2d_Curve2d> GeomPlate_BuildPlateSurface::ProjectedCurve(
  occ::handle<Adaptor3d_Curve>& Curv)
{

  occ::handle<GeomAdaptor_Surface> hsur = new GeomAdaptor_Surface(mySurfInit);

  occ::handle<ProjLib_HCompProjectedCurve> HProjector =
    new ProjLib_HCompProjectedCurve(hsur, Curv, myTolU / 10, myTolV / 10);
  if (HProjector->NbCurves() != 1)
  {
    HProjector.Nullify();
#ifdef OCCT_DEBUG
    std::cout << "BuildPlateSurace :: No continuous projection" << std::endl;
#endif
  }
  else
  {
    double First1, Last1, First2, Last2;
    First1 = Curv->FirstParameter();
    Last1  = Curv->LastParameter();
    HProjector->Bounds(1, First2, Last2);

    if (std::abs(First1 - First2) <= std::max(myTolU, myTolV)
        && std::abs(Last1 - Last2) <= std::max(myTolU, myTolV))
    {
      HProjector = occ::down_cast<ProjLib_HCompProjectedCurve>(
        HProjector->Trim(First2, Last2, Precision::PConfusion()));
    }
    else
    {
      HProjector.Nullify();
#ifdef OCCT_DEBUG
      std::cout << "BuildPlateSurace :: No complete projection" << std::endl;
#endif
    }
  }
  return HProjector;
}

gp_Pnt2d GeomPlate_BuildPlateSurface::ProjectPoint(const gp_Pnt& p3d)
{
  Extrema_POnSurf P;
  myProj.Perform(p3d);
  int nearest = 1;
  if (myProj.NbExt() > 1)
  {
    double dist2mini = myProj.SquareDistance(1);
    for (int i = 2; i <= myProj.NbExt(); i++)
    {
      if (myProj.SquareDistance(i) < dist2mini)
      {
        dist2mini = myProj.SquareDistance(i);
        nearest   = i;
      }
    }
  }
  P = myProj.Point(nearest);
  double u, v;
  P.Parameter(u, v);
  gp_Pnt2d p2d;
  p2d.SetCoord(u, v);

  return p2d;
}

void GeomPlate_BuildPlateSurface::Init()
{
  myLinCont->Clear();
  myPntCont->Clear();
  myPntCont = new NCollection_HSequence<occ::handle<GeomPlate_PointConstraint>>;
  myLinCont = new NCollection_HSequence<occ::handle<GeomPlate_CurveConstraint>>;
}

void GeomPlate_BuildPlateSurface::LoadInitSurface(const occ::handle<Geom_Surface>& Surf)
{
  mySurfInit       = Surf;
  mySurfInitIsGive = true;
}

void GeomPlate_BuildPlateSurface::Add(const occ::handle<GeomPlate_CurveConstraint>& Cont)
{
  myLinCont->Append(Cont);
}

void GeomPlate_BuildPlateSurface::SetNbBounds(const int NbBounds)
{
  myNbBounds = NbBounds;
}

void GeomPlate_BuildPlateSurface::Add(const occ::handle<GeomPlate_PointConstraint>& Cont)
{
  myPntCont->Append(Cont);
}

void GeomPlate_BuildPlateSurface::Perform(const Message_ProgressRange& theProgress)
{
#ifdef OCCT_DEBUG

  OSD_Chronometer Chrono;
  Chrono.Reset();
  Chrono.Start();
#endif

  if (myNbBounds == 0)
    myNbBounds = myLinCont->Length();

  myPlate.Init();

  int  NTLinCont = myLinCont->Length(), NTPntCont = myPntCont->Length(), NbBoucle = 0;
  bool Fini = true;
  if ((NTLinCont + NTPntCont) == 0)
  {
#ifdef OCCT_DEBUG
    std::cout << "WARNING : GeomPlate : The number of constraints is null." << std::endl;
#endif

    return;
  }

  Message_ProgressScope aPS(theProgress, "Calculating the surface filled", 100, true);
  if (!mySurfInitIsGive)
  {
    ComputeSurfInit(aPS.Next(10));
    if (aPS.UserBreak())
      return;
  }

  else
  {
    if (NTLinCont >= 2)
    {
      myInitOrder = new NCollection_HArray1<int>(1, NTLinCont);
      for (int l = 1; l <= NTLinCont; l++)
        myInitOrder->SetValue(l, l);
      if (!CourbeJointive(myTol3d))
      {
#ifdef OCCT_DEBUG
        std::cout << "WARNING : Courbes non jointives a " << myTol3d << " pres" << std::endl;
#endif
      }
      TrierTab(myInitOrder);
    }
    else if (NTLinCont > 0)
    {
      mySense     = new NCollection_HArray1<int>(1, NTLinCont, 0);
      myInitOrder = new NCollection_HArray1<int>(1, NTLinCont, 1);
    }
  }

  if (mySurfInit.IsNull())
  {
    return;
  }

  double u1, v1, u2, v2;
  mySurfInit->Bounds(u1, v1, u2, v2);
  GeomAdaptor_Surface aSurfInit(mySurfInit);
  myTolU = aSurfInit.UResolution(myTol3d);
  myTolV = aSurfInit.VResolution(myTol3d);
  myProj.Initialize(aSurfInit, u1, v1, u2, v2, myTolU, myTolV);

  bool Ok = true;
  for (int i = 1; i <= NTLinCont; i++)
    if (myLinCont->Value(i)->Curve2dOnSurf().IsNull())
    {
      occ::handle<Geom2d_Curve> Curve2d = ProjectCurve(myLinCont->Value(i)->Curve3d());
      if (Curve2d.IsNull())
      {
        Ok = false;
        break;
      }
      myLinCont->ChangeValue(i)->SetCurve2dOnSurf(Curve2d);
    }
  if (!Ok)
  {
    GeomPlate_MakeApprox App(myGeomPlateSurface, myTol3d, 1, 3, 15 * myTol3d, -1, GeomAbs_C0, 1.3);
    mySurfInit = App.Surface();

    mySurfInit->Bounds(u1, v1, u2, v2);
    GeomAdaptor_Surface Surf(mySurfInit);
    myTolU = Surf.UResolution(myTol3d);
    myTolV = Surf.VResolution(myTol3d);
    myProj.Initialize(Surf, u1, v1, u2, v2, myTolU, myTolV);

    Ok = true;
    for (int i = 1; i <= NTLinCont; i++)
    {
      occ::handle<Geom2d_Curve> Curve2d = ProjectCurve(myLinCont->Value(i)->Curve3d());
      if (Curve2d.IsNull())
      {
        Ok = false;
        break;
      }
      myLinCont->ChangeValue(i)->SetCurve2dOnSurf(Curve2d);
    }
    if (!Ok)
    {
      mySurfInit = myPlanarSurfInit;

      mySurfInit->Bounds(u1, v1, u2, v2);
      GeomAdaptor_Surface SurfNew(mySurfInit);
      myTolU = SurfNew.UResolution(myTol3d);
      myTolV = SurfNew.VResolution(myTol3d);
      myProj.Initialize(SurfNew, u1, v1, u2, v2, myTolU, myTolV);

      for (int i = 1; i <= NTLinCont; i++)
        myLinCont->ChangeValue(i)->SetCurve2dOnSurf(ProjectCurve(myLinCont->Value(i)->Curve3d()));
    }
    else
    {
      for (int i = 1; i <= NTPntCont; i++)
      {
        gp_Pnt P;
        myPntCont->Value(i)->D0(P);
        myPntCont->ChangeValue(i)->SetPnt2dOnSurf(ProjectPoint(P));
      }
    }
  }

  for (int i = 1; i <= NTPntCont; i++)
  {
    if (!myPntCont->Value(i)->HasPnt2dOnSurf())
    {
      gp_Pnt P;
      myPntCont->Value(i)->D0(P);
      myPntCont->ChangeValue(i)->SetPnt2dOnSurf(ProjectPoint(P));
    }
  }

  if ((NTLinCont != 0) && (myNbPtsOnCur != 0))
    CalculNbPtsInit();

  occ::handle<NCollection_HArray1<NCollection_Sequence<double>>> PntInter;
  occ::handle<NCollection_HArray1<NCollection_Sequence<double>>> PntG1G1;
  if (NTLinCont != 0)
  {
    PntInter = new NCollection_HArray1<NCollection_Sequence<double>>(1, NTLinCont);
    PntG1G1  = new NCollection_HArray1<NCollection_Sequence<double>>(1, NTLinCont);
    Intersect(PntInter, PntG1G1);
  }

  myFree = !myIsLinear;

  do
  {
#ifdef OCCT_DEBUG
    if (Affich && NbBoucle)
    {
      std::cout << "Resultats boucle" << NbBoucle << std::endl;
      std::cout << "DistMax=" << myG0Error << std::endl;
      if (myG1Error != 0)
        std::cout << "AngleMax=" << myG1Error << std::endl;
      if (myG2Error != 0)
        std::cout << "CourbMax=" << myG2Error << std::endl;
    }
#endif
    NbBoucle++;
    if (NTLinCont != 0)
    {

      int NPointMax = 0;
      for (int i = 1; i <= NTLinCont; i++)
        if ((myLinCont->Value(i)->NbPoints()) > NPointMax)
          NPointMax = (int)(myLinCont->Value(i)->NbPoints());

      Discretise(PntInter, PntG1G1);

      LoadCurve(NbBoucle);
      if (myPntCont->Length() != 0)
        LoadPoint(NbBoucle);

      myPlate.SolveTI(myDegree, ComputeAnisotropie(), aPS.Next(90));

      if (aPS.UserBreak())
      {
        return;
      }

      if (!myPlate.IsDone())
      {
#ifdef OCCT_DEBUG
        std::cout << "WARNING : GeomPlate : calculation of Plate failed" << std::endl;
#endif
        return;
      }

      myGeomPlateSurface = new GeomPlate_Surface(mySurfInit, myPlate);
      double Umin, Umax, Vmin, Vmax;
      myPlate.UVBox(Umin, Umax, Vmin, Vmax);
      myGeomPlateSurface->SetBounds(Umin, Umax, Vmin, Vmax);

      Fini = VerifSurface(NbBoucle);
      if ((NbBoucle >= myNbIter) && (!Fini))
      {
#ifdef OCCT_DEBUG
        std::cout << "Warning: objective was not reached" << std::endl;
#endif
        Fini = true;
      }

      if ((NTPntCont != 0) && (Fini))
      {
        double di, an, cu;
        VerifPoints(di, an, cu);
      }
    }
    else
    {
      LoadPoint(NbBoucle);

      myPlate.SolveTI(myDegree, ComputeAnisotropie(), aPS.Next(90));

      if (aPS.UserBreak())
      {
        return;
      }

      if (!myPlate.IsDone())
      {
#ifdef OCCT_DEBUG
        std::cout << "WARNING : GeomPlate : calculation of Plate failed" << std::endl;
#endif
        return;
      }

      myGeomPlateSurface = new GeomPlate_Surface(mySurfInit, myPlate);
      double Umin, Umax, Vmin, Vmax;
      myPlate.UVBox(Umin, Umax, Vmin, Vmax);
      myGeomPlateSurface->SetBounds(Umin, Umax, Vmin, Vmax);
      Fini = true;
      double di, an, cu;
      VerifPoints(di, an, cu);
    }
  } while (!Fini);
#ifdef OCCT_DEBUG
  if (NTLinCont != 0)
  {
    std::cout << "======== Global results ===========" << std::endl;
    std::cout << "DistMax=" << myG0Error << std::endl;
    if (myG1Error != 0)
      std::cout << "AngleMax=" << myG1Error << std::endl;
    if (myG2Error != 0)
      std::cout << "CourbMax=" << myG2Error << std::endl;
  }
  Chrono.Stop();
  double Tps;
  Chrono.Show(Tps);
  std::cout << "*** END OF GEOMPLATE ***" << std::endl;
  std::cout << "Time of calculation : " << Tps << std::endl;
  std::cout << "Number of loops : " << NbBoucle << std::endl;
#endif
}

void GeomPlate_BuildPlateSurface::EcartContraintesMil(
  const int                                 c,
  occ::handle<NCollection_HArray1<double>>& d,
  occ::handle<NCollection_HArray1<double>>& an,
  occ::handle<NCollection_HArray1<double>>& courb)
{
  int    NbPt = myParCont->Value(c).Length();
  double U;
  if (NbPt < 3)
    NbPt = 4;
  else
    NbPt = myParCont->Value(c).Length();
  gp_Vec                                 v1i, v1f, v2i, v2f, v3i, v3f;
  gp_Pnt                                 Pi, Pf;
  gp_Pnt2d                               P2d;
  int                                    i;
  occ::handle<GeomPlate_CurveConstraint> LinCont = myLinCont->Value(c);
  switch (LinCont->Order())
  {
    case 0:
      for (i = 1; i < NbPt; i++)
      {
        U = (myParCont->Value(c).Value(i) + myParCont->Value(c).Value(i + 1)) / 2;
        LinCont->D0(U, Pi);
        if (!LinCont->ProjectedCurve().IsNull())
          P2d = LinCont->ProjectedCurve()->Value(U);
        else
        {
          if (!LinCont->Curve2dOnSurf().IsNull())
            P2d = LinCont->Curve2dOnSurf()->Value(U);
          else
            P2d = ProjectPoint(Pi);
        }
        myGeomPlateSurface->D0(P2d.Coord(1), P2d.Coord(2), Pf);
        an->Init(0);
        courb->Init(0);
        d->ChangeValue(i) = Pf.Distance(Pi);
      }
      break;
    case 1:
      for (i = 1; i < NbPt; i++)
      {
        U = (myParCont->Value(c).Value(i) + myParCont->Value(c).Value(i + 1)) / 2;
        LinCont->D1(U, Pi, v1i, v2i);
        if (!LinCont->ProjectedCurve().IsNull())
          P2d = LinCont->ProjectedCurve()->Value(U);
        else
        {
          if (!LinCont->Curve2dOnSurf().IsNull())
            P2d = LinCont->Curve2dOnSurf()->Value(U);
          else
            P2d = ProjectPoint(Pi);
        }
        myGeomPlateSurface->D1(P2d.Coord(1), P2d.Coord(2), Pf, v1f, v2f);
        d->ChangeValue(i) = Pf.Distance(Pi);
        v3i               = v1i ^ v2i;
        v3f               = v1f ^ v2f;
        double angle      = v3f.Angle(v3i);
        if (angle > (M_PI / 2))
          an->ChangeValue(i) = M_PI - angle;
        else
          an->ChangeValue(i) = angle;
        courb->Init(0);
      }
      break;
    case 2:
      occ::handle<Geom_Surface>       Splate(myGeomPlateSurface);
      LocalAnalysis_SurfaceContinuity CG2;
      for (i = 1; i < NbPt; i++)
      {
        U = (myParCont->Value(c).Value(i) + myParCont->Value(c).Value(i + 1)) / 2;
        LinCont->D0(U, Pi);
        if (!LinCont->ProjectedCurve().IsNull())
          P2d = LinCont->ProjectedCurve()->Value(U);
        else
        {
          if (!LinCont->Curve2dOnSurf().IsNull())
            P2d = LinCont->Curve2dOnSurf()->Value(U);
          else
            P2d = ProjectPoint(Pi);
        }
        GeomLProp_SLProps Prop(Splate, P2d.Coord(1), P2d.Coord(2), 2, 0.001);
        CG2.ComputeAnalysis(Prop, myLinCont->Value(c)->LPropSurf(U), GeomAbs_G2);
        d->ChangeValue(i)     = CG2.C0Value();
        an->ChangeValue(i)    = CG2.G1Angle();
        courb->ChangeValue(i) = CG2.G2CurvatureGap();
      }
      break;
  }
}

void GeomPlate_BuildPlateSurface::Disc2dContour(const int, NCollection_Sequence<gp_XY>& Seq2d)
{
#ifdef OCCT_DEBUG
  if (Seq2d.Length() != 4)
    std::cout << "Number of points should be equal to 4 for Disc2dContour" << std::endl;
#endif

  Seq2d.Clear();

  int      NTCurve   = myLinCont->Length();
  int      NTPntCont = myPntCont->Length();
  gp_Pnt2d P2d;
  gp_XY    UV;
  gp_Pnt   PP;
  double   u1, v1, u2, v2;
  int      i;

  mySurfInit->Bounds(u1, v1, u2, v2);
  GeomAdaptor_Surface Surf(mySurfInit);
  myProj.Initialize(Surf, u1, v1, u2, v2, myTolU, myTolV);

  for (i = 1; i <= NTPntCont; i++)
    if (myPntCont->Value(i)->Order() != -1)
    {
      P2d = myPntCont->Value(i)->Pnt2dOnSurf();
      UV.SetX(P2d.Coord(1));
      UV.SetY(P2d.Coord(2));
      Seq2d.Append(UV);
    }
  for (i = 1; i <= NTCurve; i++)
  {
    occ::handle<GeomPlate_CurveConstraint> LinCont = myLinCont->Value(i);
    if (LinCont->Order() != -1)
    {
      int NbPt = myParCont->Value(i).Length();

      if (!LinCont->ProjectedCurve().IsNull())
        P2d = LinCont->ProjectedCurve()->Value(myParCont->Value(i).Value(1));

      else
      {
        if (!LinCont->Curve2dOnSurf().IsNull())
          P2d = LinCont->Curve2dOnSurf()->Value(myParCont->Value(i).Value(1));

        else
        {
          LinCont->D0(myParCont->Value(i).Value(1), PP);
          P2d = ProjectPoint(PP);
        }
      }

      UV.SetX(P2d.Coord(1));
      UV.SetY(P2d.Coord(2));
      Seq2d.Append(UV);
      for (int j = 2; j < NbPt; j++)
      {
        double Uj = myParCont->Value(i).Value(j), Ujp1 = myParCont->Value(i).Value(j + 1);
        if (!LinCont->ProjectedCurve().IsNull())
          P2d = LinCont->ProjectedCurve()->Value((Ujp1 + 3 * Uj) / 4);

        else
        {
          if (!LinCont->Curve2dOnSurf().IsNull())
            P2d = LinCont->Curve2dOnSurf()->Value((Ujp1 + 3 * Uj) / 4);

          else
          {
            LinCont->D0((Ujp1 + 3 * Uj) / 4, PP);
            P2d = ProjectPoint(PP);
          }
        }
        UV.SetX(P2d.Coord(1));
        UV.SetY(P2d.Coord(2));
        Seq2d.Append(UV);

        if (!LinCont->ProjectedCurve().IsNull())
          P2d = LinCont->ProjectedCurve()->Value((Ujp1 + Uj) / 2);

        else
        {
          if (!LinCont->Curve2dOnSurf().IsNull())
            P2d = LinCont->Curve2dOnSurf()->Value((Ujp1 + Uj) / 2);

          else
          {
            LinCont->D0((Ujp1 + Uj) / 2, PP);
            P2d = ProjectPoint(PP);
          }
        }

        UV.SetX(P2d.Coord(1));
        UV.SetY(P2d.Coord(2));
        Seq2d.Append(UV);

        if (!LinCont->ProjectedCurve().IsNull())
          P2d = LinCont->ProjectedCurve()->Value((3 * Ujp1 + Uj) / 4);

        else
        {
          if (!LinCont->Curve2dOnSurf().IsNull())
            P2d = LinCont->Curve2dOnSurf()->Value((3 * Ujp1 + Uj) / 4);

          else
          {
            LinCont->D0((3 * Ujp1 + Uj) / 4, PP);
            P2d = ProjectPoint(PP);
          }
        }

        UV.SetX(P2d.Coord(1));
        UV.SetY(P2d.Coord(2));
        Seq2d.Append(UV);

        if (!LinCont->ProjectedCurve().IsNull())
          P2d = LinCont->ProjectedCurve()->Value(Ujp1);

        else
        {
          if (!LinCont->Curve2dOnSurf().IsNull())
            P2d = LinCont->Curve2dOnSurf()->Value(Ujp1);

          else
          {
            LinCont->D0(Ujp1, PP);
            P2d = ProjectPoint(PP);
          }
        }

        UV.SetX(P2d.Coord(1));
        UV.SetY(P2d.Coord(2));
        Seq2d.Append(UV);
      }
    }
  }
}

void GeomPlate_BuildPlateSurface::Disc3dContour(const int,
                                                const int                     iordre,
                                                NCollection_Sequence<gp_XYZ>& Seq3d)
{
#ifdef OCCT_DEBUG
  if (Seq3d.Length() != 4)
    std::cout << "nbp should be equal to 4 for Disc3dContour" << std::endl;
  if (iordre != 0 && iordre != 1)
    std::cout << "incorrect order for Disc3dContour" << std::endl;
#endif

  Seq3d.Clear();

  double u1, v1, u2, v2;
  mySurfInit->Bounds(u1, v1, u2, v2);
  GeomAdaptor_Surface Surf(mySurfInit);
  myProj.Initialize(Surf, u1, v1, u2, v2, Surf.UResolution(myTol3d), Surf.VResolution(myTol3d));
  int NTCurve   = myLinCont->Length();
  int NTPntCont = myPntCont->Length();

  gp_Pnt P3d;
  gp_Vec v1h, v2h, v3h;
  gp_XYZ Pos;
  int    i;

  for (i = 1; i <= NTPntCont; i++)
    if (myPntCont->Value(i)->Order() != -1)
    {
      if (iordre == 0)
      {
        myPntCont->Value(i)->D0(P3d);
        Pos.SetX(P3d.X());
        Pos.SetY(P3d.Y());
        Pos.SetZ(P3d.Z());
        Seq3d.Append(Pos);
      }
      else
      {
        myPntCont->Value(i)->D1(P3d, v1h, v2h);
        v3h = v1h ^ v2h;
        Pos.SetX(v3h.X());
        Pos.SetY(v3h.Y());
        Pos.SetZ(v3h.Z());
        Seq3d.Append(Pos);
      }
    }

  for (i = 1; i <= NTCurve; i++)
    if (myLinCont->Value(i)->Order() != -1)

    {
      int NbPt = myParCont->Value(i).Length();

      if (iordre == 0)
      {
        myLinCont->Value(i)->D0(myParCont->Value(i).Value(1), P3d);
        Pos.SetX(P3d.X());
        Pos.SetY(P3d.Y());
        Pos.SetZ(P3d.Z());
        Seq3d.Append(Pos);
      }
      else
      {
        myLinCont->Value(i)->D1(myParCont->Value(i).Value(1), P3d, v1h, v2h);
        v3h = v1h ^ v2h;
        Pos.SetX(v3h.X());
        Pos.SetY(v3h.Y());
        Pos.SetZ(v3h.Z());
        Seq3d.Append(Pos);
      }

      for (int j = 2; j < NbPt; j++)
      {
        double Uj = myParCont->Value(i).Value(j), Ujp1 = myParCont->Value(i).Value(j + 1);
        if (iordre == 0)
        {

          myLinCont->Value(i)->D0((Ujp1 + 3 * Uj) / 4, P3d);
          Pos.SetX(P3d.X());
          Pos.SetY(P3d.Y());
          Pos.SetZ(P3d.Z());
          Seq3d.Append(Pos);

          myLinCont->Value(i)->D0((Ujp1 + Uj) / 2, P3d);
          Pos.SetX(P3d.X());
          Pos.SetY(P3d.Y());
          Pos.SetZ(P3d.Z());
          Seq3d.Append(Pos);

          myLinCont->Value(i)->D0((3 * Ujp1 + Uj) / 4, P3d);
          Pos.SetX(P3d.X());
          Pos.SetY(P3d.Y());
          Pos.SetZ(P3d.Z());
          Seq3d.Append(Pos);

          myLinCont->Value(i)->D0(Ujp1, P3d);
          Pos.SetX(P3d.X());
          Pos.SetY(P3d.Y());
          Pos.SetZ(P3d.Z());
          Seq3d.Append(Pos);
        }
        else
        {

          myLinCont->Value(i)->D1((Ujp1 + 3 * Uj) / 4, P3d, v1h, v2h);
          v3h = v1h ^ v2h;
          Pos.SetX(v3h.X());
          Pos.SetY(v3h.Y());
          Pos.SetZ(v3h.Z());
          Seq3d.Append(Pos);

          myLinCont->Value(i)->D1((Ujp1 + Uj) / 2, P3d, v1h, v2h);
          v3h = v1h ^ v2h;
          Pos.SetX(v3h.X());
          Pos.SetY(v3h.Y());
          Pos.SetZ(v3h.Z());
          Seq3d.Append(Pos);

          myLinCont->Value(i)->D1((3 * Ujp1 + Uj) / 4, P3d, v1h, v2h);
          v3h = v1h ^ v2h;
          Pos.SetX(v3h.X());
          Pos.SetY(v3h.Y());
          Pos.SetZ(v3h.Z());
          Seq3d.Append(Pos);

          myLinCont->Value(i)->D1(Ujp1, P3d, v1h, v2h);
          v3h = v1h ^ v2h;
          Pos.SetX(v3h.X());
          Pos.SetY(v3h.Y());
          Pos.SetZ(v3h.Z());
          Seq3d.Append(Pos);
        }
      }
    }
}

bool GeomPlate_BuildPlateSurface::IsDone() const
{
  return myPlate.IsDone();
}

occ::handle<GeomPlate_Surface> GeomPlate_BuildPlateSurface::Surface() const
{
  return myGeomPlateSurface;
}

occ::handle<Geom_Surface> GeomPlate_BuildPlateSurface::SurfInit() const
{
  return mySurfInit;
}

occ::handle<NCollection_HArray1<int>> GeomPlate_BuildPlateSurface::Sense() const
{
  int                                   NTCurve = myLinCont->Length();
  occ::handle<NCollection_HArray1<int>> Sens    = new NCollection_HArray1<int>(1, NTCurve);
  for (int i = 1; i <= NTCurve; i++)
    Sens->SetValue(i, mySense->Value(myInitOrder->Value(i)));
  return Sens;
}

occ::handle<NCollection_HArray1<occ::handle<Geom2d_Curve>>> GeomPlate_BuildPlateSurface::Curves2d()
  const
{
  int                                                         NTCurve = myLinCont->Length();
  occ::handle<NCollection_HArray1<occ::handle<Geom2d_Curve>>> C2dfin =
    new NCollection_HArray1<occ::handle<Geom2d_Curve>>(1, NTCurve);

  for (int i = 1; i <= NTCurve; i++)
    C2dfin->SetValue(i, myLinCont->Value(myInitOrder->Value(i))->Curve2dOnSurf());
  return C2dfin;
}

occ::handle<NCollection_HArray1<int>> GeomPlate_BuildPlateSurface::Order() const
{
  occ::handle<NCollection_HArray1<int>> result =
    new NCollection_HArray1<int>(1, myLinCont->Length());
  for (int i = 1; i <= myLinCont->Length(); i++)
    result->SetValue(myInitOrder->Value(i), i);
  return result;
}

double GeomPlate_BuildPlateSurface::G0Error() const
{
  return myG0Error;
}

double GeomPlate_BuildPlateSurface::G1Error() const
{
  return myG1Error;
}

double GeomPlate_BuildPlateSurface::G2Error() const
{
  return myG2Error;
}

double GeomPlate_BuildPlateSurface::G0Error(const int Index)
{
  occ::handle<NCollection_HArray1<double>> tdistance =
    new NCollection_HArray1<double>(1, myNbPtsOnCur);
  occ::handle<NCollection_HArray1<double>> tangle =
    new NCollection_HArray1<double>(1, myNbPtsOnCur);
  occ::handle<NCollection_HArray1<double>> tcurvature =
    new NCollection_HArray1<double>(1, myNbPtsOnCur);
  EcartContraintesMil(Index, tdistance, tangle, tcurvature);
  double MaxDistance = 0.;
  for (int i = 1; i <= myNbPtsOnCur; i++)
    if (tdistance->Value(i) > MaxDistance)
      MaxDistance = tdistance->Value(i);
  return MaxDistance;
}

double GeomPlate_BuildPlateSurface::G1Error(const int Index)
{
  occ::handle<NCollection_HArray1<double>> tdistance =
    new NCollection_HArray1<double>(1, myNbPtsOnCur);
  occ::handle<NCollection_HArray1<double>> tangle =
    new NCollection_HArray1<double>(1, myNbPtsOnCur);
  occ::handle<NCollection_HArray1<double>> tcurvature =
    new NCollection_HArray1<double>(1, myNbPtsOnCur);
  EcartContraintesMil(Index, tdistance, tangle, tcurvature);
  double MaxAngle = 0.;
  for (int i = 1; i <= myNbPtsOnCur; i++)
    if (tangle->Value(i) > MaxAngle)
      MaxAngle = tangle->Value(i);
  return MaxAngle;
}

double GeomPlate_BuildPlateSurface::G2Error(const int Index)
{
  occ::handle<NCollection_HArray1<double>> tdistance =
    new NCollection_HArray1<double>(1, myNbPtsOnCur);
  occ::handle<NCollection_HArray1<double>> tangle =
    new NCollection_HArray1<double>(1, myNbPtsOnCur);
  occ::handle<NCollection_HArray1<double>> tcurvature =
    new NCollection_HArray1<double>(1, myNbPtsOnCur);
  EcartContraintesMil(Index, tdistance, tangle, tcurvature);
  double MaxCurvature = 0.;
  for (int i = 1; i <= myNbPtsOnCur; i++)
    if (tcurvature->Value(i) > MaxCurvature)
      MaxCurvature = tcurvature->Value(i);
  return MaxCurvature;
}

occ::handle<GeomPlate_CurveConstraint> GeomPlate_BuildPlateSurface::CurveConstraint(
  const int order) const
{
  return myLinCont->Value(order);
}

occ::handle<GeomPlate_PointConstraint> GeomPlate_BuildPlateSurface::PointConstraint(
  const int order) const
{
  return myPntCont->Value(order);
}

bool GeomPlate_BuildPlateSurface::CourbeJointive(const double tolerance)
{
  int    nbf = myLinCont->Length();
  double Ufinal1, Uinit1, Ufinal2, Uinit2;
  mySense       = new NCollection_HArray1<int>(1, nbf, 0);
  bool   result = true;
  int    j      = 1, i;
  gp_Pnt P1, P2;

  while (j <= (myNbBounds - 1))
  {
    int a = 0;
    i     = j + 1;
    if (i > myNbBounds)
    {
      result = false;
      a      = 2;
    }
    while (a < 1)
    {
      if (i > myNbBounds)
      {
        result = false;
        a      = 2;
      }
      else
      {
        Uinit1  = myLinCont->Value(j)->FirstParameter();
        Ufinal1 = myLinCont->Value(j)->LastParameter();
        Uinit2  = myLinCont->Value(i)->FirstParameter();
        Ufinal2 = myLinCont->Value(i)->LastParameter();
        if (mySense->Value(j) == 1)
          Ufinal1 = Uinit1;
        myLinCont->Value(j)->D0(Ufinal1, P1);
        myLinCont->Value(i)->D0(Uinit2, P2);
        if (P1.Distance(P2) < tolerance)
        {
          if (i != j + 1)
          {
            occ::handle<GeomPlate_CurveConstraint> tampon = myLinCont->Value(j + 1);
            myLinCont->SetValue(j + 1, myLinCont->Value(i));
            myLinCont->SetValue(i, tampon);
            int Tmp = myInitOrder->Value(j + 1);

            myInitOrder->SetValue(j + 1, myInitOrder->Value(i));
            myInitOrder->SetValue(i, Tmp);
          };
          a = 2;
          mySense->SetValue(j + 1, 0);
        }
        else
        {
          myLinCont->Value(i)->D0(Ufinal2, P2);

          if (P1.Distance(P2) < tolerance)
          {
            if (i != j + 1)
            {
              occ::handle<GeomPlate_CurveConstraint> tampon = myLinCont->Value(j + 1);
              myLinCont->SetValue(j + 1, myLinCont->Value(i));
              myLinCont->SetValue(i, tampon);
              int Tmp = myInitOrder->Value(j + 1);

              myInitOrder->SetValue(j + 1, myInitOrder->Value(i));
              myInitOrder->SetValue(i, Tmp);
            };
            a = 2;
            mySense->SetValue(j + 1, 1);
          }
        }
      }
      i++;
    }
    j++;
  }
  Uinit1  = myLinCont->Value(myNbBounds)->FirstParameter();
  Ufinal1 = myLinCont->Value(myNbBounds)->LastParameter();
  Uinit2  = myLinCont->Value(1)->FirstParameter();
  Ufinal2 = myLinCont->Value(1)->LastParameter();
  myLinCont->Value(myNbBounds)->D0(Ufinal1, P1);
  myLinCont->Value(1)->D0(Uinit2, P2);
  if ((mySense->Value(myNbBounds) == 0) && (P1.Distance(P2) < tolerance))
  {
    return ((result));
  }
  myLinCont->Value(myNbBounds)->D0(Uinit1, P1);
  if ((mySense->Value(myNbBounds) == 1) && (P1.Distance(P2) < tolerance))
  {
    return ((result));
  }
  else
    return false;
}

void GeomPlate_BuildPlateSurface::ComputeSurfInit(const Message_ProgressRange& theProgress)
{
  int    nopt = 2, popt = 2, Np = 1;
  bool   isHalfSpace = true;
  double LinTol = 0.001, AngTol = 0.001;

  int NTLinCont = myLinCont->Length(), NTPntCont = myPntCont->Length();

  if (NTLinCont != 0)
  {
    myInitOrder = new NCollection_HArray1<int>(1, NTLinCont);
    for (int i = 1; i <= NTLinCont; i++)
      myInitOrder->SetValue(i, i);
  }

  bool CourbeJoint = (NTLinCont != 0) && CourbeJointive(myTol3d);
  if (CourbeJoint && IsOrderG1())
  {
    nopt = 3;

    int                                      NbPoint = 20, Discr = NbPoint / 4, pnum = 0;
    occ::handle<NCollection_HArray1<gp_Pnt>> Pts =
      new NCollection_HArray1<gp_Pnt>(1, (NbPoint + 1) * NTLinCont + NTPntCont);
    NCollection_Sequence<gp_Vec>        Vecs, NewVecs;
    NCollection_Sequence<GeomPlate_Aij> Aset;
    double                              Uinit, Ufinal, Uif;
    gp_Vec                              LastVec;
    int                                 i;
    for (i = 1; i <= NTLinCont; i++)
    {
      int Order = myLinCont->Value(i)->Order();

      NewVecs.Clear();

      Uinit  = myLinCont->Value(i)->FirstParameter();
      Ufinal = myLinCont->Value(i)->LastParameter();
      Uif    = Ufinal - Uinit;
      if (mySense->Value(i) == 1)
      {
        Uinit = Ufinal;
        Uif   = -Uif;
      }

      gp_Vec Vec1, Vec2, Normal;
      bool   ToReverse = false;
      if (i > 1 && Order >= GeomAbs_G1)
      {
        gp_Pnt P;
        myLinCont->Value(i)->D1(Uinit, P, Vec1, Vec2);
        Normal = Vec1 ^ Vec2;
        if (LastVec.IsOpposite(Normal, AngTol))
          ToReverse = true;
      }

      for (int j = 0; j <= NbPoint; j++)
      {

        double Inter = j * Uif / (NbPoint);
        if (Order < GeomAbs_G1 || j % Discr != 0)
          myLinCont->Value(i)->D0(Uinit + Inter, Pts->ChangeValue(++pnum));
        else
        {
          myLinCont->Value(i)->D1(Uinit + Inter, Pts->ChangeValue(++pnum), Vec1, Vec2);
          Normal = Vec1 ^ Vec2;
          Normal.Normalize();
          if (ToReverse)
            Normal.Reverse();
          bool isNew = true;
          int  k;
          for (k = 1; k <= Vecs.Length(); k++)
            if (Vecs(k).IsEqual(Normal, LinTol, AngTol))
            {
              isNew = false;
              break;
            }
          if (isNew)
            for (k = 1; k <= NewVecs.Length(); k++)
              if (NewVecs(k).IsEqual(Normal, LinTol, AngTol))
              {
                isNew = false;
                break;
              }
          if (isNew)
            NewVecs.Append(Normal);
        }
      }
      if (Order >= GeomAbs_G1)
      {
        isHalfSpace = GeomPlate_BuildAveragePlane::HalfSpace(NewVecs, Vecs, Aset, LinTol, AngTol);
        if (!isHalfSpace)
          break;
        LastVec = Normal;
      }
    }

    if (isHalfSpace)
    {
      for (i = 1; i <= NTPntCont; i++)
      {
        int Order = myPntCont->Value(i)->Order();

        NewVecs.Clear();
        gp_Vec Vec1, Vec2, Normal;
        if (Order < GeomAbs_G1)
          myPntCont->Value(i)->D0(Pts->ChangeValue(++pnum));
        else
        {
          myPntCont->Value(i)->D1(Pts->ChangeValue(++pnum), Vec1, Vec2);
          Normal = Vec1 ^ Vec2;
          Normal.Normalize();
          bool isNew = true;
          for (int k = 1; k <= Vecs.Length(); k++)
            if (Vecs(k).IsEqual(Normal, LinTol, AngTol))
            {
              isNew = false;
              break;
            }
          if (isNew)
          {
            NewVecs.Append(Normal);
            isHalfSpace =
              GeomPlate_BuildAveragePlane::HalfSpace(NewVecs, Vecs, Aset, LinTol, AngTol);
            if (!isHalfSpace)
            {
              NewVecs(1).Reverse();
              isHalfSpace =
                GeomPlate_BuildAveragePlane::HalfSpace(NewVecs, Vecs, Aset, LinTol, AngTol);
            }
            if (!isHalfSpace)
              break;
          }
        }
      }

      if (isHalfSpace)
      {
        bool NullExist = true;
        while (NullExist)
        {
          NullExist = false;
          for (i = 1; i <= Vecs.Length(); i++)
            if (Vecs(i).SquareMagnitude() == 0.)
            {
              NullExist = true;
              Vecs.Remove(i);
              break;
            }
        }
        GeomPlate_BuildAveragePlane BAP(Vecs, Pts);
        double                      u1, u2, v1, v2;
        BAP.MinMaxBox(u1, u2, v1, v2);

        double du = u2 - u1;
        double dv = v2 - v1;
        u1 -= du;
        u2 += du;
        v1 -= dv;
        v2 += dv;
        mySurfInit = new Geom_RectangularTrimmedSurface(BAP.Plane(), u1, u2, v1, v2);
      }
    }
    if (!isHalfSpace)
    {
#ifdef OCCT_DEBUG
      std::cout << std::endl << "Normals are not in half space" << std::endl << std::endl;
#endif
      myIsLinear = false;
      nopt       = 2;
    }
  }

  if (NTLinCont != 0)
    TrierTab(myInitOrder);

  if (nopt != 3)
  {
    if (NTPntCont != 0)
      nopt = 1;
    else if (!CourbeJoint || NTLinCont != myNbBounds)
    {
#ifdef OCCT_DEBUG
      std::cout << "WARNING : Curves are non-adjacent with tolerance " << myTol3d << std::endl;
#endif
      nopt = 1;
    }

    double LenT    = 0;
    int    Npt     = 0;
    int    NTPoint = 20 * NTLinCont;
    int    i;
    for (i = 1; i <= NTLinCont; i++)
      LenT += myLinCont->Value(i)->Length();
    for (i = 1; i <= NTLinCont; i++)
    {
      int NbPoint = (int)(NTPoint * (myLinCont->Value(i)->Length()) / LenT);
      if (NbPoint < 10)
        NbPoint = 10;

      (void)Npt;
      Npt += NbPoint;
    }

    occ::handle<NCollection_HArray1<gp_Pnt>> Pts =
      new NCollection_HArray1<gp_Pnt>(1, 20 * NTLinCont + NTPntCont);
    int    NbPoint = 20;
    double Uinit, Ufinal, Uif;
    for (i = 1; i <= NTLinCont; i++)
    {
      Uinit  = myLinCont->Value(i)->FirstParameter();
      Ufinal = myLinCont->Value(i)->LastParameter();
      Uif    = Ufinal - Uinit;
      if (mySense->Value(i) == 1)
      {
        Uinit = Ufinal;
        Uif   = -Uif;
      }
      for (int j = 0; j < NbPoint; j++)
      {

        double Inter = j * Uif / (NbPoint);
        gp_Pnt P;
        myLinCont->Value(i)->D0(Uinit + Inter, P);
        Pts->SetValue(Np++, P);
      }
    }
    for (i = 1; i <= NTPntCont; i++)
    {
      gp_Pnt P;
      myPntCont->Value(i)->D0(P);
      Pts->SetValue(Np++, P);
    }
    if (!CourbeJoint)
      myNbBounds = 0;
    GeomPlate_BuildAveragePlane BAP(Pts, NbPoint * myNbBounds, myTol3d / 1000, popt, nopt);
    if (!BAP.IsPlane())
    {
#ifdef OCCT_DEBUG
      std::cout << "WARNING : GeomPlate : the initial surface is not a plane." << std::endl;
#endif

      return;
    }
    double u1, u2, v1, v2;
    BAP.MinMaxBox(u1, u2, v1, v2);

    double du = u2 - u1;
    double dv = v2 - v1;
    u1 -= du;
    u2 += du;
    v1 -= dv;
    v2 += dv;
    mySurfInit = new Geom_RectangularTrimmedSurface(BAP.Plane(), u1, u2, v1, v2);
  }

  if (NTLinCont != 0 && myIsLinear)
  {
    occ::handle<Geom_Surface> InitPlane =
      (occ::down_cast<Geom_RectangularTrimmedSurface>(mySurfInit))->BasisSurface();

    double Ratio = 0., R1 = 2., R2 = 0.6;

    occ::handle<GeomAdaptor_Surface> hsur    = new GeomAdaptor_Surface(InitPlane);
    int                              NbPoint = 20;

    for (int i = 1; i <= NTLinCont && myIsLinear; i++)
    {
      double FirstPar = myLinCont->Value(i)->FirstParameter();
      double LastPar  = myLinCont->Value(i)->LastParameter();
      double Uif      = (LastPar - FirstPar) / (NbPoint);

      occ::handle<Adaptor3d_Curve>             Curve = myLinCont->Value(i)->Curve3d();
      occ::handle<ProjLib_HCompProjectedCurve> ProjCurve =
        new ProjLib_HCompProjectedCurve(hsur, Curve, myTol3d, myTol3d);
      Adaptor3d_CurveOnSurface AProj(ProjCurve, hsur);

      gp_Pnt P;
      gp_Vec DerC, DerCproj;
      for (int j = 1; j < NbPoint && myIsLinear; j++)
      {
        double Inter = FirstPar + j * Uif;
        Curve->D1(Inter, P, DerC);
        AProj.D1(Inter, P, DerCproj);

        double A1 = DerC.Magnitude();
        double A2 = DerCproj.Magnitude();
        if (A2 <= 1.e-20)
        {
          Ratio = 1.e20;
        }
        else
        {
          Ratio = A1 / A2;
        }
        if (Ratio > R1 || Ratio < R2)
        {
          myIsLinear = false;
          break;
        }
      }
    }
#ifdef OCCT_DEBUG
    if (!myIsLinear)
      std::cout << "Metrics are too different :" << Ratio << std::endl;
#endif
  }

  if (!myIsLinear)
  {
    myPlanarSurfInit = mySurfInit;
    double u1, v1, u2, v2;
    mySurfInit->Bounds(u1, v1, u2, v2);
    GeomAdaptor_Surface Surf(mySurfInit);
    myTolU = Surf.UResolution(myTol3d);
    myTolV = Surf.VResolution(myTol3d);
    myProj.Initialize(Surf, u1, v1, u2, v2, myTolU, myTolV);

    int i;
    for (i = 1; i <= NTLinCont; i++)
      if (myLinCont->Value(i)->Curve2dOnSurf().IsNull())
        myLinCont->ChangeValue(i)->SetCurve2dOnSurf(ProjectCurve(myLinCont->Value(i)->Curve3d()));

    for (i = 1; i <= NTPntCont; i++)
    {
      gp_Pnt P;
      myPntCont->Value(i)->D0(P);
      if (!myPntCont->Value(i)->HasPnt2dOnSurf())
        myPntCont->ChangeValue(i)->SetPnt2dOnSurf(ProjectPoint(P));
    }

    if ((NTLinCont != 0) && (myNbPtsOnCur != 0))
      CalculNbPtsInit();

    occ::handle<NCollection_HArray1<NCollection_Sequence<double>>> PntInter;
    occ::handle<NCollection_HArray1<NCollection_Sequence<double>>> PntG1G1;
    if (NTLinCont != 0)
    {
      PntInter = new NCollection_HArray1<NCollection_Sequence<double>>(1, NTLinCont);
      PntG1G1  = new NCollection_HArray1<NCollection_Sequence<double>>(1, NTLinCont);
      Intersect(PntInter, PntG1G1);
    }

    Discretise(PntInter, PntG1G1);

    LoadCurve(0, 0);
    if (myPntCont->Length() != 0)
      LoadPoint(0, 0);

    Message_ProgressScope aPS(theProgress, "ComputeSurfInit", 1);
    myPlate.SolveTI(2, ComputeAnisotropie(), aPS.Next());
    if (theProgress.UserBreak())
    {
      return;
    }

    if (!myPlate.IsDone())
    {
#ifdef OCCT_DEBUG
      std::cout << "WARNING : GeomPlate : calculation of Plate failed" << std::endl;
#endif
      return;
    }

    myGeomPlateSurface = new GeomPlate_Surface(mySurfInit, myPlate);

    GeomPlate_MakeApprox App(myGeomPlateSurface, myTol3d, 1, 3, 15 * myTol3d, -1, GeomAbs_C0);
    mySurfInit = App.Surface();

    mySurfInitIsGive = true;
    myPlate.Init();

    for (i = 1; i <= NTLinCont; i++)
    {
      occ::handle<Geom2d_Curve> NullCurve;
      NullCurve.Nullify();
      myLinCont->ChangeValue(i)->SetCurve2dOnSurf(NullCurve);
    }
  }
}

void GeomPlate_BuildPlateSurface::Intersect(
  occ::handle<NCollection_HArray1<NCollection_Sequence<double>>>& PntInter,
  occ::handle<NCollection_HArray1<NCollection_Sequence<double>>>& PntG1G1)
{
  int                        NTLinCont = myLinCont->Length();
  Geom2dInt_GInter           Intersection;
  Geom2dAdaptor_Curve        Ci, Cj;
  IntRes2d_IntersectionPoint int2d;
  gp_Pnt                     P1, P2;
  gp_Pnt2d                   P2d;
  gp_Vec2d                   V2d;

  for (int i = 1; i <= NTLinCont; i++)
  {

    Ci.Load(myLinCont->Value(i)->Curve2dOnSurf());
    for (int j = i; j <= NTLinCont; j++)
    {
      Cj.Load(myLinCont->Value(j)->Curve2dOnSurf());
      if (i == j)
        Intersection.Perform(Ci, myTol2d * 10, myTol2d * 10);
      else
        Intersection.Perform(Ci, Cj, myTol2d * 10, myTol2d * 10);

      if (!Intersection.IsEmpty())
      {
        int nbpt = Intersection.NbPoints();

        for (int k = 1; k <= nbpt; k++)
        {
          int2d = Intersection.Point(k);
          myLinCont->Value(i)->D0(int2d.ParamOnFirst(), P1);
          myLinCont->Value(j)->D0(int2d.ParamOnSecond(), P2);
#ifdef OCCT_DEBUG
          if (Affich > 1)
          {
            std::cout << " Intersection " << k << " entre " << i << " &" << j << std::endl;
            std::cout << "  Distance = " << P1.Distance(P2) << std::endl;
          }
#endif
          if (P1.Distance(P2) < myTol3d)
          {

            double tolint = Ci.Resolution(myTol3d);
            Ci.D1(int2d.ParamOnFirst(), P2d, V2d);
            double aux = V2d.Magnitude();
            if (aux > 1.e-7)
            {
              aux = myTol3d / aux;
              if (aux > 100 * tolint)
                tolint *= 100;
              else
                tolint = aux;
            }
            else
              tolint *= 100;

            PntInter->ChangeValue(i).Append(int2d.ParamOnFirst() - tolint);
            PntInter->ChangeValue(i).Append(int2d.ParamOnFirst() + tolint);

            if ((myLinCont->Value(i)->Order() == 1) && (myLinCont->Value(j)->Order() == 1))
            {
              gp_Vec v11, v12, v13, v14, v15, v16, v21, v22, v23, v24, v25, v26;
              myLinCont->Value(i)->D2(int2d.ParamOnFirst(), P1, v11, v12, v13, v14, v15);
              myLinCont->Value(j)->D2(int2d.ParamOnSecond(), P2, v21, v22, v23, v24, v25);
              v16        = v11 ^ v12;
              v26        = v21 ^ v22;
              double ant = v16.Angle(v26);
              if (ant > (M_PI / 2))
                ant = M_PI - ant;
              if ((std::abs(v16 * v15 - v16 * v25) > (myTol3d / 1000))
                  || (std::abs(ant) > myTol3d / 1000))

              {
                double   coin;
                double   Tol = 100 * myTol3d;
                double   A1;
                gp_Pnt2d P1temp, P2temp;
                gp_Vec2d V1, V2;
                myLinCont->Value(i)->Curve2dOnSurf()->D1(int2d.ParamOnFirst(), P1temp, V1);
                myLinCont->Value(j)->Curve2dOnSurf()->D1(int2d.ParamOnSecond(), P2temp, V2);
                A1 = V1.Angle(V2);
                if (A1 > (M_PI / 2))
                  A1 = M_PI - A1;
                if (std::abs(std::abs(A1) - M_PI) < myTolAng)
                  Tol = 100000 * myTol3d;
#ifdef OCCT_DEBUG
                if (Affich)
                  std::cout << "Angle between curves " << i << "," << j << " "
                            << std::abs(std::abs(A1) - M_PI) << std::endl;
#endif

                coin        = Ci.Resolution(Tol);
                double Par1 = int2d.ParamOnFirst() - coin, Par2 = int2d.ParamOnFirst() + coin;

                PntG1G1->ChangeValue(i).Append(Par1);
                PntG1G1->ChangeValue(i).Append(Par2);
                coin = Cj.Resolution(Tol);
                Par1 = int2d.ParamOnSecond() - coin;
                Par2 = int2d.ParamOnSecond() + coin;

                PntG1G1->ChangeValue(j).Append(Par1);
                PntG1G1->ChangeValue(j).Append(Par2);
              }
            }

            if ((myLinCont->Value(i)->Order() == 0 && myLinCont->Value(j)->Order() == 1)
                || (myLinCont->Value(i)->Order() == 1 && myLinCont->Value(j)->Order() == 0))
            {
              gp_Vec vec, vecU, vecV, N;
              if (myLinCont->Value(i)->Order() == 0)
              {
                occ::handle<Adaptor3d_Curve> theCurve = myLinCont->Value(i)->Curve3d();
                theCurve->D1(int2d.ParamOnFirst(), P1, vec);
                myLinCont->Value(j)->D1(int2d.ParamOnSecond(), P2, vecU, vecV);
              }
              else
              {
                occ::handle<Adaptor3d_Curve> theCurve = myLinCont->Value(j)->Curve3d();
                theCurve->D1(int2d.ParamOnSecond(), P2, vec);
                myLinCont->Value(i)->D1(int2d.ParamOnFirst(), P1, vecU, vecV);
              }
              N            = vecU ^ vecV;
              double Angle = vec.Angle(N);
              Angle        = std::abs(M_PI / 2 - Angle);
              if (Angle > myTolAng / 10.)
              {

                double   coin;
                double   Tol = 100 * myTol3d;
                double   A1;
                gp_Pnt2d P1temp, P2temp;
                gp_Vec2d V1, V2;
                myLinCont->Value(i)->Curve2dOnSurf()->D1(int2d.ParamOnFirst(), P1temp, V1);
                myLinCont->Value(j)->Curve2dOnSurf()->D1(int2d.ParamOnSecond(), P2temp, V2);
                A1 = V1.Angle(V2);
                if (A1 > M_PI / 2)
                  A1 = M_PI - A1;
                if (std::abs(std::abs(A1) - M_PI) < myTolAng)
                  Tol = 100000 * myTol3d;
#ifdef OCCT_DEBUG
                if (Affich)
                  std::cout << "Angle entre Courbe " << i << "," << j << " "
                            << std::abs(std::abs(A1) - M_PI) << std::endl;
#endif
                if (myLinCont->Value(i)->Order() == 1)
                {
                  coin = Ci.Resolution(Tol);
                  coin *= Angle / myTolAng * 10.;
#ifdef OCCT_DEBUG
                  std::cout << std::endl << "coin = " << coin << std::endl;
#endif
                  double Par1 = int2d.ParamOnFirst() - coin;
                  double Par2 = int2d.ParamOnFirst() + coin;

                  PntG1G1->ChangeValue(i).Append(Par1);
                  PntG1G1->ChangeValue(i).Append(Par2);
                }
                else
                {
                  coin = Cj.Resolution(Tol);
                  coin *= Angle / myTolAng * 10.;
#ifdef OCCT_DEBUG
                  std::cout << std::endl << "coin = " << coin << std::endl;
#endif
                  double Par1 = int2d.ParamOnSecond() - coin;
                  double Par2 = int2d.ParamOnSecond() + coin;

                  PntG1G1->ChangeValue(j).Append(Par1);
                  PntG1G1->ChangeValue(j).Append(Par2);
                }
              }
            }
          }
          else
          {

            double tolint, Dist;
            Dist   = P1.Distance(P2);
            tolint = Ci.Resolution(Dist);
            PntInter->ChangeValue(i).Append(int2d.ParamOnFirst() - tolint);
            PntInter->ChangeValue(i).Append(int2d.ParamOnFirst() + tolint);
            if (j != i)
            {
              tolint = Cj.Resolution(Dist);
              PntInter->ChangeValue(j).Append(int2d.ParamOnSecond() - tolint);
              PntInter->ChangeValue(j).Append(int2d.ParamOnSecond() + tolint);
            }

#ifdef OCCT_DEBUG
            std::cout << "Attention: Two points 3d have the same projection dist = " << Dist
                      << std::endl;
#endif
          }
        }
      }
    }
  }
}

void GeomPlate_BuildPlateSurface::Discretise(
  const occ::handle<NCollection_HArray1<NCollection_Sequence<double>>>& PntInter,
  const occ::handle<NCollection_HArray1<NCollection_Sequence<double>>>& PntG1G1)
{
  int                       NTLinCont = myLinCont->Length();
  bool                      ACR;
  occ::handle<Geom2d_Curve> C2d;
  Geom2dAdaptor_Curve       AC2d;

  occ::handle<Law_Interpol> acrlaw = new (Law_Interpol)();
  myPlateCont = new NCollection_HArray1<NCollection_Sequence<double>>(1, NTLinCont);
  myParCont   = new NCollection_HArray1<NCollection_Sequence<double>>(1, NTLinCont);

  double                                 Uinit, Ufinal, Length2d = 0, Inter;
  double                                 CurLength;
  int                                    NbPnt_i, NbPtInter, NbPtG1G1;
  occ::handle<GeomPlate_CurveConstraint> LinCont;

  for (int i = 1; i <= NTLinCont; i++)
  {
    LinCont = myLinCont->Value(i);
    Uinit   = LinCont->FirstParameter();
    Ufinal  = LinCont->LastParameter();

    C2d = LinCont->Curve2dOnSurf();
    ACR = (!C2d.IsNull());
    if (ACR)
    {

      if (!C2d.IsNull())
        AC2d.Load(C2d);

      int                          ii, Nbint = 20;
      double                       U;
      NCollection_Array1<gp_Pnt2d> tabP2d(1, Nbint + 1);
      tabP2d(1).SetY(Uinit);
      tabP2d(1).SetX(0.);
      tabP2d(Nbint + 1).SetY(Ufinal);

      Length2d = GCPnts_AbscissaPoint::Length(AC2d, Uinit, Ufinal);

      tabP2d(Nbint + 1).SetX(Length2d);
      for (ii = 2; ii <= Nbint; ii++)
      {
        U = Uinit + (Ufinal - Uinit) * ((1 - std::cos((ii - 1) * M_PI / (Nbint))) / 2);
        tabP2d(ii).SetY(U);

        tabP2d(ii).SetX(GCPnts_AbscissaPoint::Length(AC2d, Uinit, U));
      }
      acrlaw->Set(tabP2d);
    }

    NbPnt_i   = (int)(LinCont->NbPoints());
    NbPtInter = PntInter->Value(i).Length();
    NbPtG1G1  = PntG1G1->Value(i).Length();

#ifdef OCCT_DEBUG
    if (Affich > 1)
    {
      std::cout << "Courbe : " << i << std::endl;
      std::cout << "  NbPnt, NbPtInter, NbPtG1G1 :" << NbPnt_i << ", " << NbPtInter << ", "
                << NbPtG1G1 << std::endl;
    }
#endif
    for (int j = 1; j <= NbPnt_i; j++)
    {

      if (j == NbPnt_i)
        Inter = Ufinal;
      else if (ACR)
      {
        CurLength = Length2d * (1 - std::cos((j - 1) * M_PI / (NbPnt_i - 1))) / 2;
        Inter     = acrlaw->Value(CurLength);
      }
      else
      {
        Inter = Uinit + (Ufinal - Uinit) * ((1 - std::cos((j - 1) * M_PI / (NbPnt_i - 1))) / 2);
      }
      myParCont->ChangeValue(i).Append(Inter);
      if (NbPtInter != 0)
      {
        for (int l = 1; l <= NbPtInter; l += 2)
        {

          if ((Inter > PntInter->Value(i).Value(l)) && (Inter < PntInter->Value(i).Value(l + 1)))
          {
            l = NbPtInter + 2;
          }
          else
          {
            if (l + 1 >= NbPtInter)
            {

              if (NbPtG1G1 != 0)
              {

                for (int k = 1; k <= NbPtG1G1; k += 2)
                {
                  if ((Inter > PntG1G1->Value(i).Value(k))
                      && (Inter < PntG1G1->Value(i).Value(k + 1)))
                  {
                    k = NbPtG1G1 + 2;

                    gp_Pnt   P3d, PP, Pdif;
                    gp_Pnt2d P2d;

                    AC2d.D0(Inter, P2d);
                    LinCont->D0(Inter, P3d);
                    mySurfInit->D0(P2d.Coord(1), P2d.Coord(2), PP);
                    Pdif.SetCoord(-PP.Coord(1) + P3d.Coord(1),
                                  -PP.Coord(2) + P3d.Coord(2),
                                  -PP.Coord(3) + P3d.Coord(3));
                    Plate_PinpointConstraint PC(P2d.XY(), Pdif.XYZ(), 0, 0);
                    myPlate.Load(PC);
                  }
                  else
                  {
                    if (k + 1 >= NbPtG1G1)
                    {
                      myPlateCont->ChangeValue(i).Append(Inter);
                    }
                  }
                }
              }
              else
              {
                myPlateCont->ChangeValue(i).Append(Inter);
              }
            }
          }
        }
      }
      else
      {
        if (NbPtG1G1 != 0)
        {
          for (int k = 1; k <= NbPtG1G1; k += 2)
          {
            if ((Inter > PntG1G1->Value(i).Value(k)) && (Inter < PntG1G1->Value(i).Value(k + 1)))
            {
              k = NbPtG1G1 + 2;

              gp_Pnt   P3d, PP, Pdif;
              gp_Pnt2d P2d;

              AC2d.D0(Inter, P2d);
              LinCont->D0(Inter, P3d);
              mySurfInit->D0(P2d.Coord(1), P2d.Coord(2), PP);
              Pdif.SetCoord(-PP.Coord(1) + P3d.Coord(1),
                            -PP.Coord(2) + P3d.Coord(2),
                            -PP.Coord(3) + P3d.Coord(3));
              Plate_PinpointConstraint PC(P2d.XY(), Pdif.XYZ(), 0, 0);
              myPlate.Load(PC);
            }
            else
            {
              if (k + 1 >= NbPtG1G1)
              {
                myPlateCont->ChangeValue(i).Append(Inter);
              }
            }
          }
        }
        else
        {
          if (((!mySurfInitIsGive)
               && (Geom2dAdaptor_Curve(LinCont->Curve2dOnSurf()).GetType() != GeomAbs_Circle))
              || ((j > 1) && (j < NbPnt_i)))
            myPlateCont->ChangeValue(i).Append(Inter);
        }
      }
    }
  }
}

void GeomPlate_BuildPlateSurface::CalculNbPtsInit()
{
  double LenT      = 0;
  int    NTLinCont = myLinCont->Length();
  int    NTPoint   = (int)(myNbPtsOnCur * NTLinCont);
  int    i;

  for (i = 1; i <= NTLinCont; i++)
    LenT += myLinCont->Value(i)->Length();
  for (i = 1; i <= NTLinCont; i++)
  {
    int Cont = myLinCont->Value(i)->Order();
    switch (Cont)
    {
      case 0:
        myLinCont->ChangeValue(i)->SetNbPoints(
          int(1.2 * NTPoint * (myLinCont->Value(i)->Length()) / LenT));
        break;
      case 1:
        myLinCont->ChangeValue(i)->SetNbPoints(
          int(NTPoint * (myLinCont->Value(i)->Length()) / LenT));
        break;
      case 2:
        myLinCont->ChangeValue(i)->SetNbPoints(
          int(0.7 * NTPoint * (myLinCont->Value(i)->Length()) / LenT));
        break;
    }
    if (myLinCont->Value(i)->NbPoints() < 3)
      myLinCont->ChangeValue(i)->SetNbPoints(3);
  }
}

void GeomPlate_BuildPlateSurface::LoadCurve(const int NbBoucle, const int OrderMax)
{
  gp_Pnt   P3d, Pdif, PP;
  gp_Pnt2d P2d;
  int      NTLinCont = myLinCont->Length(), i, j;
  int      Tang, Nt;

  for (i = 1; i <= NTLinCont; i++)
  {
    occ::handle<GeomPlate_CurveConstraint> CC = myLinCont->Value(i);
    if (CC->Order() != -1)
    {
      Tang = std::min(CC->Order(), OrderMax);
      Nt   = myPlateCont->Value(i).Length();
      if (Tang != -1)
        for (j = 1; j <= Nt; j++)
        {
          CC->D0(myPlateCont->Value(i).Value(j), P3d);
          if (!CC->ProjectedCurve().IsNull())
            P2d = CC->ProjectedCurve()->Value(myPlateCont->Value(i).Value(j));

          else
          {
            if (!CC->Curve2dOnSurf().IsNull())
              P2d = CC->Curve2dOnSurf()->Value(myPlateCont->Value(i).Value(j));
            else
              P2d = ProjectPoint(P3d);
          }
          mySurfInit->D0(P2d.Coord(1), P2d.Coord(2), PP);
          Pdif.SetCoord(-PP.Coord(1) + P3d.Coord(1),
                        -PP.Coord(2) + P3d.Coord(2),
                        -PP.Coord(3) + P3d.Coord(3));
          Plate_PinpointConstraint PC(P2d.XY(), Pdif.XYZ(), 0, 0);
          myPlate.Load(PC);

          if (Tang == 1)
          {
            gp_Vec V1, V2, V3, V4;
            CC->D1(myPlateCont->Value(i).Value(j), PP, V1, V2);
            mySurfInit->D1(P2d.Coord(1), P2d.Coord(2), PP, V3, V4);

            Plate_D1 D1final(V1.XYZ(), V2.XYZ());
            Plate_D1 D1init(V3.XYZ(), V4.XYZ());
            if (!myFree)
            {
              Plate_GtoCConstraint GCC(P2d.XY(), D1init, D1final);
              myPlate.Load(GCC);
            }
            else if (NbBoucle == 1)
            {
              Plate_FreeGtoCConstraint FreeGCC(P2d.XY(), D1init, D1final);
              myPlate.Load(FreeGCC);
            }
            else
            {
              gp_Vec DU, DV, Normal, DerPlateU, DerPlateV;

              Normal = V1 ^ V2;

              double norm = Normal.Magnitude();
              if (norm > 1.e-12)
                Normal /= norm;
              DerPlateU = myPrevPlate.EvaluateDerivative(P2d.XY(), 1, 0);
              DerPlateV = myPrevPlate.EvaluateDerivative(P2d.XY(), 0, 1);

              DU.SetLinearForm(-(V3 + DerPlateU).Dot(Normal), Normal, DerPlateU);
              DV.SetLinearForm(-(V4 + DerPlateV).Dot(Normal), Normal, DerPlateV);
              Plate_PinpointConstraint PinU(P2d.XY(), DU.XYZ(), 1, 0);
              Plate_PinpointConstraint PinV(P2d.XY(), DV.XYZ(), 0, 1);
              myPlate.Load(PinU);
              myPlate.Load(PinV);
            }
          }

          if (Tang == 2)
          {
            gp_Vec V1, V2, V3, V4, V5, V6, V7, V8, V9, V10;
            CC->D2(myPlateCont->Value(i).Value(j), PP, V1, V2, V5, V6, V7);
            mySurfInit->D2(P2d.Coord(1), P2d.Coord(2), PP, V3, V4, V8, V9, V10);

            Plate_D1 D1final(V1.XYZ(), V2.XYZ());
            Plate_D1 D1init(V3.XYZ(), V4.XYZ());
            Plate_D2 D2final(V5.XYZ(), V6.XYZ(), V7.XYZ());
            Plate_D2 D2init(V8.XYZ(), V9.XYZ(), V10.XYZ());

            Plate_GtoCConstraint GCC(P2d.XY(), D1init, D1final, D2init, D2final);
            myPlate.Load(GCC);
          }
        }
    }
  }
}

void GeomPlate_BuildPlateSurface::LoadPoint(const int, const int OrderMax)
{
  gp_Pnt   P3d, Pdif, PP;
  gp_Pnt2d P2d;
  int      NTPntCont = myPntCont->Length();
  int      Tang, i;

  for (i = 1; i <= NTPntCont; i++)
  {
    myPntCont->Value(i)->D0(P3d);
    P2d = myPntCont->Value(i)->Pnt2dOnSurf();
    mySurfInit->D0(P2d.Coord(1), P2d.Coord(2), PP);
    Pdif.SetCoord(-PP.Coord(1) + P3d.Coord(1),
                  -PP.Coord(2) + P3d.Coord(2),
                  -PP.Coord(3) + P3d.Coord(3));
    Plate_PinpointConstraint PC(P2d.XY(), Pdif.XYZ(), 0, 0);
    myPlate.Load(PC);
    Tang = std::min(myPntCont->Value(i)->Order(), OrderMax);
    if (Tang == 1)
    {
      gp_Vec V1, V2, V3, V4;
      myPntCont->Value(i)->D1(PP, V1, V2);
      mySurfInit->D1(P2d.Coord(1), P2d.Coord(2), PP, V3, V4);
      Plate_D1 D1final(V1.XYZ(), V2.XYZ());
      Plate_D1 D1init(V3.XYZ(), V4.XYZ());
      if (!myFree)
      {
        Plate_GtoCConstraint GCC(P2d.XY(), D1init, D1final);
        myPlate.Load(GCC);
      }
      else
      {
        Plate_FreeGtoCConstraint FreeGCC(P2d.XY(), D1init, D1final);
        myPlate.Load(FreeGCC);
      }
    }

    if (Tang == 2)
    {
      gp_Vec V1, V2, V3, V4, V5, V6, V7, V8, V9, V10;
      myPntCont->Value(i)->D2(PP, V1, V2, V5, V6, V7);

      mySurfInit->D2(P2d.Coord(1), P2d.Coord(2), PP, V3, V4, V8, V9, V10);
      Plate_D1 D1final(V1.XYZ(), V2.XYZ());
      Plate_D1 D1init(V3.XYZ(), V4.XYZ());
      Plate_D2 D2final(V5.XYZ(), V6.XYZ(), V7.XYZ());
      Plate_D2 D2init(V8.XYZ(), V9.XYZ(), V10.XYZ());

      Plate_GtoCConstraint GCC(P2d.XY(), D1init, D1final, D2init, D2final);
      myPlate.Load(GCC);
    }
  }
}

bool GeomPlate_BuildPlateSurface::VerifSurface(const int NbBoucle)
{

  int  NTLinCont = myLinCont->Length();
  bool Result    = true;

  myG0Error = 0, myG1Error = 0, myG2Error = 0;

  for (int i = 1; i <= NTLinCont; i++)
  {
    occ::handle<GeomPlate_CurveConstraint> LinCont;
    LinCont = myLinCont->Value(i);
    if (LinCont->Order() != -1)
    {
      int NbPts_i = myParCont->Value(i).Length();
      if (NbPts_i < 3)
        NbPts_i = 4;
      occ::handle<NCollection_HArray1<double>> tdist =
        new NCollection_HArray1<double>(1, NbPts_i - 1);
      occ::handle<NCollection_HArray1<double>> tang =
        new NCollection_HArray1<double>(1, NbPts_i - 1);
      occ::handle<NCollection_HArray1<double>> tcourb =
        new NCollection_HArray1<double>(1, NbPts_i - 1);

      EcartContraintesMil(i, tdist, tang, tcourb);

      double diffDistMax = 0, diffAngMax = 0;

      int NdiffDist = 0, NdiffAng = 0;

      for (int j = 1; j < NbPts_i; j++)
      {
        if (tdist->Value(j) > myG0Error)
          myG0Error = tdist->Value(j);
        if (tang->Value(j) > myG1Error)
          myG1Error = tang->Value(j);
        if (tcourb->Value(j) > myG2Error)
          myG2Error = tcourb->Value(j);
        double U;
        if (myParCont->Value(i).Length() > 3)
          U = (myParCont->Value(i).Value(j) + myParCont->Value(i).Value(j + 1)) / 2;
        else
          U = LinCont->FirstParameter()
              + (LinCont->LastParameter() - LinCont->FirstParameter()) * (j - 1) / (NbPts_i - 2);
        double diffDist = tdist->Value(j) - LinCont->G0Criterion(U), diffAng;
        if (LinCont->Order() > 0)
          diffAng = tang->Value(j) - LinCont->G1Criterion(U);
        else
          diffAng = 0;

        if (diffDist > 0)
        {
          diffDist = diffDist / LinCont->G0Criterion(U);
          if (diffDist > diffDistMax)
            diffDistMax = diffDist;

          NdiffDist++;
        }
        else if ((diffAng > 0) && (LinCont->Order() == 1))
        {
          diffAng = diffAng / myLinCont->Value(i)->G1Criterion(U);
          if (diffAng > diffAngMax)
            diffAngMax = diffAng;

          NdiffAng++;
        }
      }

      if (NdiffDist > 0)
      {
        double Coef;
        if (LinCont->Order() == 0)
          Coef = 0.6 * std::log(diffDistMax + 7.4);

        else
          Coef = std::log(diffDistMax + 3.3);

        if (Coef > 3)
          Coef = 3;

        if ((NbBoucle > 1) && (diffDistMax > 2))
        {
          Coef = 1.6;
        }

        if (LinCont->NbPoints() >= std::floor(LinCont->NbPoints() * Coef))
          Coef = 2;

        LinCont->SetNbPoints(int(LinCont->NbPoints() * Coef));
        Result = false;
      }
      else if (NdiffAng > 0)
      {
        double Coef = 1.5;
        if ((LinCont->NbPoints() + 1) >= std::floor(LinCont->NbPoints() * Coef))
          Coef = 2;

        LinCont->SetNbPoints(int(LinCont->NbPoints() * Coef));
        Result = false;
      }
    }
  }
  if (!Result)
  {
    if (myFree && NbBoucle == 1)
      myPrevPlate = myPlate;
    myPlate.Init();
  }
  return Result;
}

void GeomPlate_BuildPlateSurface::VerifPoints(double& Dist, double& Ang, double& Curv) const
{
  int      NTPntCont = myPntCont->Length();
  gp_Pnt   Pi, Pf;
  gp_Pnt2d P2d;
  gp_Vec   v1i, v1f, v2i, v2f, v3i, v3f;
  Ang  = 0;
  Dist = 0, Curv = 0;
  occ::handle<GeomPlate_PointConstraint> PntCont;
  for (int i = 1; i <= NTPntCont; i++)
  {
    PntCont = myPntCont->Value(i);
    switch (PntCont->Order())
    {
      case 0:
        P2d = PntCont->Pnt2dOnSurf();
        PntCont->D0(Pi);
        myGeomPlateSurface->D0(P2d.Coord(1), P2d.Coord(2), Pf);
        Dist = Pf.Distance(Pi);
        break;
      case 1:
        PntCont->D1(Pi, v1i, v2i);
        P2d = PntCont->Pnt2dOnSurf();
        myGeomPlateSurface->D1(P2d.Coord(1), P2d.Coord(2), Pf, v1f, v2f);
        Dist = Pf.Distance(Pi);
        v3i  = v1i ^ v2i;
        v3f  = v1f ^ v2f;
        Ang  = v3f.Angle(v3i);
        if (Ang > (M_PI / 2))
          Ang = M_PI - Ang;
        break;
      case 2:
        occ::handle<Geom_Surface>       Splate(myGeomPlateSurface);
        LocalAnalysis_SurfaceContinuity CG2;
        P2d = PntCont->Pnt2dOnSurf();
        GeomLProp_SLProps Prop(Splate, P2d.Coord(1), P2d.Coord(2), 2, 0.001);
        CG2.ComputeAnalysis(Prop, PntCont->LPropSurf(), GeomAbs_G2);
        Dist = CG2.C0Value();
        Ang  = CG2.G1Angle();
        Curv = CG2.G2CurvatureGap();
        break;
    }
  }
}

double GeomPlate_BuildPlateSurface::ComputeAnisotropie() const
{
  if (myAnisotropie)
  {

    return 1.0;
  }
  else
    return 1.0;
}

bool GeomPlate_BuildPlateSurface::IsOrderG1() const
{
  bool result = true;
  for (int i = 1; i <= myLinCont->Length(); i++)
    if (myLinCont->Value(i)->Order() < 1)
    {
      result = false;
      break;
    }
  return result;
}
