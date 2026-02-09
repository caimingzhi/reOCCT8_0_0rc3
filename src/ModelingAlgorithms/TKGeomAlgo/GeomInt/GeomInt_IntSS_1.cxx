#include <algorithm>
#include <GeomInt_IntSS.hpp>

#include <Adaptor3d_TopolTool.hpp>
#include <Approx_CurveOnSurface.hpp>
#include <ElSLib.hpp>
#include <Extrema_ExtPS.hpp>
#include <Geom2dAdaptor.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom2dInt_GInter.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <GeomAdaptor.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomInt.hpp>
#include <GeomInt_LineTool.hpp>
#include <GeomInt_WLApprox.hpp>
#include <GeomLib_Check2dBSplineCurve.hpp>
#include <GeomLib_CheckBSplineCurve.hpp>
#include <GeomProjLib.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_Hyperbola.hpp>
#include <Geom_Line.hpp>
#include <Geom_Parabola.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <IntPatch_GLine.hpp>
#include <IntPatch_RLine.hpp>
#include <IntPatch_WLine.hpp>
#include <IntRes2d_IntersectionSegment.hpp>
#include <IntSurf_Quadric.hpp>
#include <Precision.hpp>
#include <ApproxInt_KnotTools.hpp>

static void AdjustUPeriodic(const occ::handle<Geom_Surface>& aS,
                            const occ::handle<Geom2d_Curve>& aC2D)
{
  if (aC2D.IsNull() || !aS->IsUPeriodic())
    return;

  constexpr double aEps     = Precision::PConfusion();
  const double     aEpsilon = Epsilon(10.);

  double umin, umax, vmin, vmax;
  aS->Bounds(umin, umax, vmin, vmax);
  const double aPeriod = aS->UPeriod();

  const double   aT1 = aC2D->FirstParameter();
  const double   aT2 = aC2D->LastParameter();
  const double   aTx = aT1 + 0.467 * (aT2 - aT1);
  const gp_Pnt2d aPx = aC2D->Value(aTx);

  double aUx = aPx.X();
  if (fabs(aUx) < aEpsilon)
    aUx = 0.;
  if (fabs(aUx - aPeriod) < aEpsilon)
    aUx = aPeriod;

  double dU = 0.;
  while (aUx < (umin - aEps))
  {
    aUx += aPeriod;
    dU += aPeriod;
  }
  while (aUx > (umax + aEps))
  {
    aUx -= aPeriod;
    dU -= aPeriod;
  }

  if (dU != 0.)
  {
    gp_Vec2d aV2D(dU, 0.);
    aC2D->Translate(aV2D);
  }
}

static void GetQuadric(const occ::handle<GeomAdaptor_Surface>& HS1, IntSurf_Quadric& quad1)
{
  switch (HS1->GetType())
  {
    case GeomAbs_Plane:
      quad1.SetValue(HS1->Plane());
      break;
    case GeomAbs_Cylinder:
      quad1.SetValue(HS1->Cylinder());
      break;
    case GeomAbs_Cone:
      quad1.SetValue(HS1->Cone());
      break;
    case GeomAbs_Sphere:
      quad1.SetValue(HS1->Sphere());
      break;
    case GeomAbs_Torus:
      quad1.SetValue(HS1->Torus());
      break;
    default:
      throw Standard_ConstructionError("GeomInt_IntSS::MakeCurve");
  }
}

static void Parameters(const occ::handle<GeomAdaptor_Surface>& HS1,
                       const occ::handle<GeomAdaptor_Surface>& HS2,
                       const gp_Pnt&                           Ptref,
                       double&                                 U1,
                       double&                                 V1,
                       double&                                 U2,
                       double&                                 V2)
{
  IntSurf_Quadric quad1, quad2;

  GetQuadric(HS1, quad1);
  GetQuadric(HS2, quad2);

  quad1.Parameters(Ptref, U1, V1);
  quad2.Parameters(Ptref, U2, V2);
}

static bool ParametersOfNearestPointOnSurface(const Extrema_ExtPS& theExtr,
                                              double&              theU,
                                              double&              theV)
{
  if (!theExtr.IsDone() || !theExtr.NbExt())
    return false;

  int    anIndex    = 1;
  double aMinSQDist = theExtr.SquareDistance(anIndex);
  for (int i = 2; i <= theExtr.NbExt(); i++)
  {
    double aSQD = theExtr.SquareDistance(i);
    if (aSQD < aMinSQDist)
    {
      aMinSQDist = aSQD;
      anIndex    = i;
    }
  }

  theExtr.Point(anIndex).Parameter(theU, theV);

  return true;
}

static void GetSegmentBoundary(const IntRes2d_IntersectionSegment& theSegm,
                               const occ::handle<Geom2d_Curve>&    theCurve,
                               NCollection_Vector<double>&         theArrayOfParameters)
{
  double aU1 = theCurve->FirstParameter(), aU2 = theCurve->LastParameter();

  if (theSegm.HasFirstPoint())
  {
    const IntRes2d_IntersectionPoint& anIPF = theSegm.FirstPoint();
    aU1                                     = anIPF.ParamOnFirst();
  }

  if (theSegm.HasLastPoint())
  {
    const IntRes2d_IntersectionPoint& anIPL = theSegm.LastPoint();
    aU2                                     = anIPL.ParamOnFirst();
  }

  theArrayOfParameters.Append(aU1);
  theArrayOfParameters.Append(aU2);
}

static void IntersectCurveAndBoundary(const occ::handle<Geom2d_Curve>&       theC2d,
                                      const occ::handle<Geom2d_Curve>* const theArrBounds,
                                      const int                              theNumberOfCurves,
                                      const double                           theTol,
                                      NCollection_Vector<double>&            theArrayOfParameters)
{
  if (theC2d.IsNull())
    return;

  Geom2dAdaptor_Curve anAC1(theC2d);
  for (int aCurID = 0; aCurID < theNumberOfCurves; aCurID++)
  {
    if (theArrBounds[aCurID].IsNull())
      continue;

    Geom2dAdaptor_Curve anAC2(theArrBounds[aCurID]);
    Geom2dInt_GInter    anIntCC2d(anAC1, anAC2, theTol, theTol);

    if (!anIntCC2d.IsDone() || anIntCC2d.IsEmpty())
      continue;

    for (int aPntID = 1; aPntID <= anIntCC2d.NbPoints(); aPntID++)
    {
      const double aParam = anIntCC2d.Point(aPntID).ParamOnFirst();
      theArrayOfParameters.Append(aParam);
    }

    for (int aSegmID = 1; aSegmID <= anIntCC2d.NbSegments(); aSegmID++)
    {
      GetSegmentBoundary(anIntCC2d.Segment(aSegmID), theC2d, theArrayOfParameters);
    }
  }
}

static bool isDegenerated(const occ::handle<GeomAdaptor_Surface>& theGAHS,
                          const occ::handle<Adaptor2d_Curve2d>&   theAHC2d,
                          const double                            theFirstPar,
                          const double                            theLastPar)
{
  constexpr double aSqTol = Precision::Confusion() * Precision::Confusion();
  gp_Pnt2d         aP2d;
  gp_Pnt           aP1, aP2;

  theAHC2d->D0(theFirstPar, aP2d);
  theGAHS->D0(aP2d.X(), aP2d.Y(), aP1);

  theAHC2d->D0(theLastPar, aP2d);
  theGAHS->D0(aP2d.X(), aP2d.Y(), aP2);

  if (aP1.SquareDistance(aP2) > aSqTol)
    return false;

  theAHC2d->D0(0.5 * (theFirstPar + theLastPar), aP2d);
  theGAHS->D0(aP2d.X(), aP2d.Y(), aP2);

  return aP1.SquareDistance(aP2) <= aSqTol;
}

void GeomInt_IntSS::MakeCurve(const int                               Index,
                              const occ::handle<Adaptor3d_TopolTool>& dom1,
                              const occ::handle<Adaptor3d_TopolTool>& dom2,
                              const double                            Tol,
                              const bool                              Approx,
                              const bool                              ApproxS1,
                              const bool                              ApproxS2)

{
  bool                             myApprox1, myApprox2, myApprox;
  double                           Tolpc, myTolApprox;
  IntPatch_IType                   typl;
  occ::handle<Geom2d_BSplineCurve> H1;
  occ::handle<Geom_Surface>        aS1, aS2;

  Tolpc       = Tol;
  myApprox    = Approx;
  myApprox1   = ApproxS1;
  myApprox2   = ApproxS2;
  myTolApprox = 0.0000001;

  aS1 = myHS1->Surface();
  aS2 = myHS2->Surface();

  occ::handle<IntPatch_Line> L = myIntersector.Line(Index);
  typl                         = L->ArcType();

  if (typl == IntPatch_Walking)
  {
    occ::handle<IntPatch_WLine> aWLine(occ::down_cast<IntPatch_WLine>(L));
    if (aWLine.IsNull())
    {
      return;
    }
    L = aWLine;
  }

  myLConstruct.Perform(L);
  if (!myLConstruct.IsDone() || myLConstruct.NbParts() <= 0)
  {
    return;
  }

  bool                    ok;
  int                     i, j, aNbParts;
  double                  fprm, lprm;
  occ::handle<Geom_Curve> newc;

  switch (typl)
  {

    case IntPatch_Lin:
    case IntPatch_Parabola:
    case IntPatch_Hyperbola:
    {
      if (typl == IntPatch_Lin)
      {
        newc = new Geom_Line(occ::down_cast<IntPatch_GLine>(L)->Line());
      }
      else if (typl == IntPatch_Parabola)
      {
        newc = new Geom_Parabola(occ::down_cast<IntPatch_GLine>(L)->Parabola());
      }
      else if (typl == IntPatch_Hyperbola)
      {
        newc = new Geom_Hyperbola(occ::down_cast<IntPatch_GLine>(L)->Hyperbola());
      }

      aNbParts = myLConstruct.NbParts();
      for (i = 1; i <= aNbParts; i++)
      {
        myLConstruct.Part(i, fprm, lprm);

        if (!Precision::IsNegativeInfinite(fprm) && !Precision::IsPositiveInfinite(lprm))
        {
          occ::handle<Geom_TrimmedCurve> aCT3D = new Geom_TrimmedCurve(newc, fprm, lprm);
          sline.Append(aCT3D);

          if (myApprox1)
          {
            occ::handle<Geom2d_Curve> C2d;
            BuildPCurves(fprm, lprm, Tolpc, myHS1->Surface(), newc, C2d);
            if (Tolpc > myTolReached2d || myTolReached2d == 0.)
            {
              myTolReached2d = Tolpc;
            }
            slineS1.Append(new Geom2d_TrimmedCurve(C2d, fprm, lprm));
          }
          else
          {
            slineS1.Append(H1);
          }

          if (myApprox2)
          {
            occ::handle<Geom2d_Curve> C2d;
            BuildPCurves(fprm, lprm, Tolpc, myHS2->Surface(), newc, C2d);
            if (Tolpc > myTolReached2d || myTolReached2d == 0.)
            {
              myTolReached2d = Tolpc;
            }

            slineS2.Append(new Geom2d_TrimmedCurve(C2d, fprm, lprm));
          }
          else
          {
            slineS2.Append(H1);
          }
        }

        else
        {
          GeomAbs_SurfaceType typS1 = myHS1->GetType();
          GeomAbs_SurfaceType typS2 = myHS2->GetType();
          if (typS1 == GeomAbs_SurfaceOfExtrusion || typS1 == GeomAbs_OffsetSurface
              || typS1 == GeomAbs_SurfaceOfRevolution || typS2 == GeomAbs_SurfaceOfExtrusion
              || typS2 == GeomAbs_OffsetSurface || typS2 == GeomAbs_SurfaceOfRevolution)
          {
            sline.Append(newc);
            slineS1.Append(H1);
            slineS2.Append(H1);
            continue;
          }
          bool   bFNIt, bLPIt;
          double aTestPrm, dT = 100.;
          double u1, v1, u2, v2, TolX;

          bFNIt = Precision::IsNegativeInfinite(fprm);
          bLPIt = Precision::IsPositiveInfinite(lprm);

          aTestPrm = 0.;

          if (bFNIt && !bLPIt)
          {
            aTestPrm = lprm - dT;
          }
          else if (!bFNIt && bLPIt)
          {
            aTestPrm = fprm + dT;
          }

          gp_Pnt ptref(newc->Value(aTestPrm));

          TolX = Precision::Confusion();
          Parameters(myHS1, myHS2, ptref, u1, v1, u2, v2);
          ok = (dom1->Classify(gp_Pnt2d(u1, v1), TolX) != TopAbs_OUT);
          if (ok)
          {
            ok = (dom2->Classify(gp_Pnt2d(u2, v2), TolX) != TopAbs_OUT);
          }
          if (ok)
          {
            sline.Append(newc);
            slineS1.Append(H1);
            slineS2.Append(H1);
          }
        }
      }
    }
    break;

    case IntPatch_Circle:
    case IntPatch_Ellipse:
    {

      if (typl == IntPatch_Circle)
      {
        newc = new Geom_Circle(occ::down_cast<IntPatch_GLine>(L)->Circle());
      }
      else
      {
        newc = new Geom_Ellipse(occ::down_cast<IntPatch_GLine>(L)->Ellipse());
      }

      double aPeriod, aRealEpsilon;

      aRealEpsilon = RealEpsilon();
      aPeriod      = M_PI + M_PI;

      aNbParts = myLConstruct.NbParts();

      for (i = 1; i <= aNbParts; i++)
      {
        myLConstruct.Part(i, fprm, lprm);

        if (std::abs(fprm) > aRealEpsilon || std::abs(lprm - aPeriod) > aRealEpsilon)
        {

          occ::handle<Geom_TrimmedCurve> aTC3D = new Geom_TrimmedCurve(newc, fprm, lprm);

          sline.Append(aTC3D);

          fprm = aTC3D->FirstParameter();
          lprm = aTC3D->LastParameter();

          if (myApprox1)
          {
            occ::handle<Geom2d_Curve> C2d;
            BuildPCurves(fprm, lprm, Tolpc, myHS1->Surface(), newc, C2d);
            if (Tolpc > myTolReached2d || myTolReached2d == 0.)
            {
              myTolReached2d = Tolpc;
            }
            slineS1.Append(C2d);
          }
          else
          {
            slineS1.Append(H1);
          }

          if (myApprox2)
          {
            occ::handle<Geom2d_Curve> C2d;
            BuildPCurves(fprm, lprm, Tolpc, myHS2->Surface(), newc, C2d);
            if (Tolpc > myTolReached2d || myTolReached2d == 0)
            {
              myTolReached2d = Tolpc;
            }
            slineS2.Append(C2d);
          }
          else
          {
            slineS2.Append(H1);
          }
        }

        else
        {

          if (aNbParts == 1)
          {
            if (std::abs(fprm) < RealEpsilon() && std::abs(lprm - 2. * M_PI) < RealEpsilon())
            {
              occ::handle<Geom_TrimmedCurve> aTC3D = new Geom_TrimmedCurve(newc, fprm, lprm);

              sline.Append(aTC3D);
              fprm = aTC3D->FirstParameter();
              lprm = aTC3D->LastParameter();

              if (myApprox1)
              {
                occ::handle<Geom2d_Curve> C2d;
                BuildPCurves(fprm, lprm, Tolpc, myHS1->Surface(), newc, C2d);
                if (Tolpc > myTolReached2d || myTolReached2d == 0)
                {
                  myTolReached2d = Tolpc;
                }
                slineS1.Append(C2d);
              }
              else
              {
                slineS1.Append(H1);
              }

              if (myApprox2)
              {
                occ::handle<Geom2d_Curve> C2d;
                BuildPCurves(fprm, lprm, Tolpc, myHS2->Surface(), newc, C2d);
                if (Tolpc > myTolReached2d || myTolReached2d == 0)
                {
                  myTolReached2d = Tolpc;
                }
                slineS2.Append(C2d);
              }
              else
              {
                slineS2.Append(H1);
              }
              break;
            }
          }

          double aTwoPIdiv17, u1, v1, u2, v2, TolX;

          aTwoPIdiv17 = 2. * M_PI / 17.;

          for (j = 0; j <= 17; j++)
          {
            gp_Pnt ptref(newc->Value(j * aTwoPIdiv17));
            TolX = Precision::Confusion();

            Parameters(myHS1, myHS2, ptref, u1, v1, u2, v2);
            ok = (dom1->Classify(gp_Pnt2d(u1, v1), TolX) != TopAbs_OUT);
            if (ok)
            {
              ok = (dom2->Classify(gp_Pnt2d(u2, v2), TolX) != TopAbs_OUT);
            }
            if (ok)
            {
              sline.Append(newc);

              if (myApprox1)
              {
                occ::handle<Geom2d_Curve> C2d;
                BuildPCurves(fprm, lprm, Tolpc, myHS1->Surface(), newc, C2d);
                if (Tolpc > myTolReached2d || myTolReached2d == 0)
                {
                  myTolReached2d = Tolpc;
                }
                slineS1.Append(C2d);
              }
              else
              {
                slineS1.Append(H1);
              }

              if (myApprox2)
              {
                occ::handle<Geom2d_Curve> C2d;
                BuildPCurves(fprm, lprm, Tolpc, myHS2->Surface(), newc, C2d);
                if (Tolpc > myTolReached2d || myTolReached2d == 0)
                {
                  myTolReached2d = Tolpc;
                }
                slineS2.Append(C2d);
              }
              else
              {
                slineS2.Append(H1);
              }
              break;
            }
          }
        }
      }
    }
    break;

    case IntPatch_Analytic:

      break;

    case IntPatch_Walking:
    {
      occ::handle<IntPatch_WLine> WL = occ::down_cast<IntPatch_WLine>(L);

#ifdef GEOMINT_INTSS_DEBUG
      WL->Dump(0);
#endif

      int ifprm, ilprm;

      if (!myApprox)
      {
        aNbParts = myLConstruct.NbParts();
        for (i = 1; i <= aNbParts; i++)
        {
          myLConstruct.Part(i, fprm, lprm);
          ifprm = (int)fprm;
          ilprm = (int)lprm;

          occ::handle<Geom2d_BSplineCurve> aH1, aH2;

          if (myApprox1)
          {
            aH1 = MakeBSpline2d(WL, ifprm, ilprm, true);
          }
          if (myApprox2)
          {
            aH2 = MakeBSpline2d(WL, ifprm, ilprm, false);
          }

          occ::handle<Geom_Curve> aBSp = MakeBSpline(WL, ifprm, ilprm);

          sline.Append(aBSp);
          slineS1.Append(aH1);
          slineS2.Append(aH2);
        }
      }

      else
      {
        bool                                             bIsDecomposited;
        int                                              nbiter, aNbSeqOfL;
        GeomInt_WLApprox                                 theapp3d;
        NCollection_Sequence<occ::handle<IntPatch_Line>> aSeqOfL;
        double                                           tol2d, aTolSS;

        tol2d  = myTolApprox;
        aTolSS = 2.e-7;
        theapp3d.SetParameters(myTolApprox, tol2d, 4, 8, 0, 30, myHS1 != myHS2);

        bIsDecomposited =
          GeomInt_LineTool::DecompositionOfWLine(WL, myHS1, myHS2, aTolSS, myLConstruct, aSeqOfL);

        aNbParts  = myLConstruct.NbParts();
        aNbSeqOfL = aSeqOfL.Length();

        nbiter = (bIsDecomposited) ? aNbSeqOfL : aNbParts;

        for (i = 1; i <= nbiter; i++)
        {
          if (bIsDecomposited)
          {
            WL    = occ::down_cast<IntPatch_WLine>(aSeqOfL.Value(i));
            ifprm = 1;
            ilprm = WL->NbPnts();
          }
          else
          {
            myLConstruct.Part(i, fprm, lprm);
            ifprm = (int)fprm;
            ilprm = (int)lprm;
          }

          bool                anApprox  = myApprox;
          bool                anApprox1 = myApprox1;
          bool                anApprox2 = myApprox2;
          GeomAbs_SurfaceType typs1, typs2;
          typs1 = myHS1->GetType();
          typs2 = myHS2->GetType();

          if (typs1 == GeomAbs_Plane)
          {
            anApprox  = false;
            anApprox1 = true;
          }
          else if (typs2 == GeomAbs_Plane)
          {
            anApprox  = false;
            anApprox2 = true;
          }

          Approx_ParametrizationType aParType =
            ApproxInt_KnotTools::DefineParType(WL, ifprm, ilprm, anApprox, anApprox1, anApprox2);

          theapp3d.SetParameters(myTolApprox, tol2d, 4, 8, 0, 30, myHS1 != myHS2, aParType);

          if (typs1 == GeomAbs_Plane)
          {
            theapp3d.Perform(myHS1, myHS2, WL, false, true, myApprox2, ifprm, ilprm);
          }
          else if (typs2 == GeomAbs_Plane)
          {
            theapp3d.Perform(myHS1, myHS2, WL, false, myApprox1, true, ifprm, ilprm);
          }
          else
          {

            if (myHS1 != myHS2)
            {
              if ((typs1 == GeomAbs_BezierSurface || typs1 == GeomAbs_BSplineSurface)
                  && (typs2 == GeomAbs_BezierSurface || typs2 == GeomAbs_BSplineSurface))
              {

                theapp3d.SetParameters(myTolApprox, tol2d, 4, 8, 0, 30, true, aParType);
              }
            }

            theapp3d.Perform(myHS1, myHS2, WL, true, myApprox1, myApprox2, ifprm, ilprm);
          }

          if (!theapp3d.IsDone())
          {

            occ::handle<Geom2d_BSplineCurve> aH1, aH2;

            occ::handle<Geom_Curve> aBSp = MakeBSpline(WL, ifprm, ilprm);
            if (myApprox1)
            {
              aH1 = MakeBSpline2d(WL, ifprm, ilprm, true);
            }
            if (myApprox2)
            {
              aH2 = MakeBSpline2d(WL, ifprm, ilprm, false);
            }

            sline.Append(aBSp);
            slineS1.Append(aH1);
            slineS2.Append(aH2);
          }

          else
          {
            if (myApprox1 || myApprox2 || (typs1 == GeomAbs_Plane || typs2 == GeomAbs_Plane))
            {
              if (theapp3d.TolReached2d() > myTolReached2d || myTolReached2d == 0.)
              {
                myTolReached2d = theapp3d.TolReached2d();
              }
            }
            if (typs1 == GeomAbs_Plane || typs2 == GeomAbs_Plane)
            {
              myTolReached3d = myTolReached2d;
            }
            else if (theapp3d.TolReached3d() > myTolReached3d || myTolReached3d == 0.)
            {
              myTolReached3d = theapp3d.TolReached3d();
            }

            int aNbMultiCurves, nbpoles;

            aNbMultiCurves = theapp3d.NbMultiCurves();
            for (j = 1; j <= aNbMultiCurves; j++)
            {
              if (typs1 == GeomAbs_Plane)
              {
                const AppParCurves_MultiBSpCurve& mbspc = theapp3d.Value(j);
                nbpoles                                 = mbspc.NbPoles();

                NCollection_Array1<gp_Pnt2d> tpoles2d(1, nbpoles);
                NCollection_Array1<gp_Pnt>   tpoles(1, nbpoles);

                mbspc.Curve(1, tpoles2d);
                const gp_Pln& Pln = myHS1->Plane();

                int ik;
                for (ik = 1; ik <= nbpoles; ik++)
                {
                  tpoles.SetValue(
                    ik,
                    ElSLib::Value(tpoles2d.Value(ik).X(), tpoles2d.Value(ik).Y(), Pln));
                }

                occ::handle<Geom_BSplineCurve> BS = new Geom_BSplineCurve(tpoles,
                                                                          mbspc.Knots(),
                                                                          mbspc.Multiplicities(),
                                                                          mbspc.Degree());
                GeomLib_CheckBSplineCurve      Check(BS, myTolCheck, myTolAngCheck);
                Check.FixTangent(true, true);

                sline.Append(BS);

                if (myApprox1)
                {
                  occ::handle<Geom2d_BSplineCurve> BS1 =
                    new Geom2d_BSplineCurve(tpoles2d,
                                            mbspc.Knots(),
                                            mbspc.Multiplicities(),
                                            mbspc.Degree());
                  GeomLib_Check2dBSplineCurve Check1(BS1, myTolCheck, myTolAngCheck);
                  Check1.FixTangent(true, true);

                  AdjustUPeriodic(aS1, BS1);

                  slineS1.Append(BS1);
                }
                else
                {
                  slineS1.Append(H1);
                }

                if (myApprox2)
                {
                  mbspc.Curve(2, tpoles2d);

                  occ::handle<Geom2d_BSplineCurve> BS2 =
                    new Geom2d_BSplineCurve(tpoles2d,
                                            mbspc.Knots(),
                                            mbspc.Multiplicities(),
                                            mbspc.Degree());
                  GeomLib_Check2dBSplineCurve newCheck(BS2, myTolCheck, myTolAngCheck);
                  newCheck.FixTangent(true, true);

                  AdjustUPeriodic(aS2, BS2);

                  slineS2.Append(BS2);
                }
                else
                {
                  slineS2.Append(H1);
                }
              }

              else if (typs2 == GeomAbs_Plane)
              {
                const AppParCurves_MultiBSpCurve& mbspc = theapp3d.Value(j);
                nbpoles                                 = mbspc.NbPoles();

                NCollection_Array1<gp_Pnt2d> tpoles2d(1, nbpoles);
                NCollection_Array1<gp_Pnt>   tpoles(1, nbpoles);
                mbspc.Curve((myApprox1) ? 2 : 1, tpoles2d);
                const gp_Pln& Pln = myHS2->Plane();

                int ik;
                for (ik = 1; ik <= nbpoles; ik++)
                {
                  tpoles.SetValue(
                    ik,
                    ElSLib::Value(tpoles2d.Value(ik).X(), tpoles2d.Value(ik).Y(), Pln));
                }

                occ::handle<Geom_BSplineCurve> BS = new Geom_BSplineCurve(tpoles,
                                                                          mbspc.Knots(),
                                                                          mbspc.Multiplicities(),
                                                                          mbspc.Degree());
                GeomLib_CheckBSplineCurve      Check(BS, myTolCheck, myTolAngCheck);
                Check.FixTangent(true, true);

                sline.Append(BS);

                if (myApprox2)
                {
                  occ::handle<Geom2d_BSplineCurve> BS1 =
                    new Geom2d_BSplineCurve(tpoles2d,
                                            mbspc.Knots(),
                                            mbspc.Multiplicities(),
                                            mbspc.Degree());
                  GeomLib_Check2dBSplineCurve Check1(BS1, myTolCheck, myTolAngCheck);
                  Check1.FixTangent(true, true);

                  AdjustUPeriodic(aS2, BS1);

                  slineS2.Append(BS1);
                }
                else
                {
                  slineS2.Append(H1);
                }

                if (myApprox1)
                {
                  mbspc.Curve(1, tpoles2d);
                  occ::handle<Geom2d_BSplineCurve> BS2 =
                    new Geom2d_BSplineCurve(tpoles2d,
                                            mbspc.Knots(),
                                            mbspc.Multiplicities(),
                                            mbspc.Degree());
                  GeomLib_Check2dBSplineCurve Check2(BS2, myTolCheck, myTolAngCheck);
                  Check2.FixTangent(true, true);

                  AdjustUPeriodic(aS1, BS2);

                  slineS1.Append(BS2);
                }
                else
                {
                  slineS1.Append(H1);
                }
              }

              else
              {
                const AppParCurves_MultiBSpCurve& mbspc = theapp3d.Value(j);
                nbpoles                                 = mbspc.NbPoles();
                NCollection_Array1<gp_Pnt> tpoles(1, nbpoles);
                mbspc.Curve(1, tpoles);
                occ::handle<Geom_BSplineCurve> BS = new Geom_BSplineCurve(tpoles,
                                                                          mbspc.Knots(),
                                                                          mbspc.Multiplicities(),
                                                                          mbspc.Degree());
                GeomLib_CheckBSplineCurve      Check(BS, myTolCheck, myTolAngCheck);
                Check.FixTangent(true, true);

                double aDist = std::max(BS->StartPoint().XYZ().SquareModulus(),
                                        BS->EndPoint().XYZ().SquareModulus());
                double eps   = Epsilon(aDist);
                if (BS->StartPoint().SquareDistance(BS->EndPoint()) < 2. * eps)
                {

                  if (mbspc.Degree() == 1 && nbpoles == 2)
                    continue;

                  if (!BS->IsClosed() && !BS->IsPeriodic())
                  {

                    gp_Pnt aPm((BS->Pole(1).XYZ() + BS->Pole(BS->NbPoles()).XYZ()) / 2.);
                    BS->SetPole(1, aPm);
                    BS->SetPole(BS->NbPoles(), aPm);
                  }
                }
                sline.Append(BS);

                if (myApprox1)
                {
                  NCollection_Array1<gp_Pnt2d> tpoles2d(1, nbpoles);
                  mbspc.Curve(2, tpoles2d);
                  occ::handle<Geom2d_BSplineCurve> BS1 =
                    new Geom2d_BSplineCurve(tpoles2d,
                                            mbspc.Knots(),
                                            mbspc.Multiplicities(),
                                            mbspc.Degree());
                  GeomLib_Check2dBSplineCurve newCheck(BS1, myTolCheck, myTolAngCheck);
                  newCheck.FixTangent(true, true);

                  AdjustUPeriodic(aS1, BS1);

                  slineS1.Append(BS1);
                }
                else
                {
                  slineS1.Append(H1);
                }
                if (myApprox2)
                {
                  NCollection_Array1<gp_Pnt2d> tpoles2d(1, nbpoles);
                  mbspc.Curve((myApprox1) ? 3 : 2, tpoles2d);
                  occ::handle<Geom2d_BSplineCurve> BS2 =
                    new Geom2d_BSplineCurve(tpoles2d,
                                            mbspc.Knots(),
                                            mbspc.Multiplicities(),
                                            mbspc.Degree());
                  GeomLib_Check2dBSplineCurve newCheck(BS2, myTolCheck, myTolAngCheck);
                  newCheck.FixTangent(true, true);

                  AdjustUPeriodic(aS2, BS2);

                  slineS2.Append(BS2);
                }
                else
                {
                  slineS2.Append(H1);
                }
              }
            }
          }
        }
      }
    }
    break;

    case IntPatch_Restriction:
    {
      occ::handle<IntPatch_RLine> RL = occ::down_cast<IntPatch_RLine>(L);
      occ::handle<Geom_Curve>     aC3d;
      occ::handle<Geom2d_Curve>   aC2d1, aC2d2;
      double                      aTolReached;
      TreatRLine(RL, myHS1, myHS2, aC3d, aC2d1, aC2d2, aTolReached);

      if (aC3d.IsNull())
        break;

      Bnd_Box2d aBox1, aBox2;

      const double aU1f = myHS1->FirstUParameter(), aV1f = myHS1->FirstVParameter(),
                   aU1l = myHS1->LastUParameter(), aV1l = myHS1->LastVParameter();
      const double aU2f = myHS2->FirstUParameter(), aV2f = myHS2->FirstVParameter(),
                   aU2l = myHS2->LastUParameter(), aV2l = myHS2->LastVParameter();

      aBox1.Add(gp_Pnt2d(aU1f, aV1f));
      aBox1.Add(gp_Pnt2d(aU1l, aV1l));
      aBox2.Add(gp_Pnt2d(aU2f, aV2f));
      aBox2.Add(gp_Pnt2d(aU2l, aV2l));

      NCollection_Vector<double> anArrayOfParameters;

      anArrayOfParameters.Append(aC3d->FirstParameter());
      anArrayOfParameters.Append(aC3d->LastParameter());

      TrimILineOnSurfBoundaries(aC2d1, aC2d2, aBox1, aBox2, anArrayOfParameters);

      const int aNbIntersSolutionsm1 = anArrayOfParameters.Length() - 1;

      for (int anInd = 0; anInd < aNbIntersSolutionsm1; anInd++)
      {
        const double aParF = anArrayOfParameters(anInd), aParL = anArrayOfParameters(anInd + 1);

        if ((aParL - aParF) <= Precision::PConfusion())
          continue;

        const double aPar = 0.5 * (aParF + aParL);
        gp_Pnt2d     aPt;

        occ::handle<Geom2d_Curve> aCurv2d1, aCurv2d2;
        if (!aC2d1.IsNull())
        {
          aC2d1->D0(aPar, aPt);

          if (aBox1.IsOut(aPt))
            continue;

          if (myApprox1)
            aCurv2d1 = new Geom2d_TrimmedCurve(aC2d1, aParF, aParL);
        }

        if (!aC2d2.IsNull())
        {
          aC2d2->D0(aPar, aPt);

          if (aBox2.IsOut(aPt))
            continue;

          if (myApprox2)
            aCurv2d2 = new Geom2d_TrimmedCurve(aC2d2, aParF, aParL);
        }

        occ::handle<Geom_Curve> aCurv3d = new Geom_TrimmedCurve(aC3d, aParF, aParL);

        sline.Append(aCurv3d);
        slineS1.Append(aCurv2d1);
        slineS2.Append(aCurv2d2);
      }
    }
    break;
  }
}

void GeomInt_IntSS::TreatRLine(const occ::handle<IntPatch_RLine>&      theRL,
                               const occ::handle<GeomAdaptor_Surface>& theHS1,
                               const occ::handle<GeomAdaptor_Surface>& theHS2,
                               occ::handle<Geom_Curve>&                theC3d,
                               occ::handle<Geom2d_Curve>&              theC2d1,
                               occ::handle<Geom2d_Curve>&              theC2d2,
                               double&                                 theTolReached)
{
  occ::handle<GeomAdaptor_Surface> aGAHS;
  occ::handle<Adaptor2d_Curve2d>   anAHC2d;
  double                           tf, tl;

  if (theRL->IsArcOnS1())
  {
    aGAHS   = theHS1;
    anAHC2d = theRL->ArcOnS1();
    theRL->ParamOnS1(tf, tl);
    theC2d1 = Geom2dAdaptor::MakeCurve(*anAHC2d);
    tf      = std::max(tf, theC2d1->FirstParameter());
    tl      = std::min(tl, theC2d1->LastParameter());
    theC2d1 = new Geom2d_TrimmedCurve(theC2d1, tf, tl);
  }
  else if (theRL->IsArcOnS2())
  {
    aGAHS   = theHS2;
    anAHC2d = theRL->ArcOnS2();
    theRL->ParamOnS2(tf, tl);
    theC2d2 = Geom2dAdaptor::MakeCurve(*anAHC2d);
    tf      = std::max(tf, theC2d2->FirstParameter());
    tl      = std::min(tl, theC2d2->LastParameter());
    theC2d2 = new Geom2d_TrimmedCurve(theC2d2, tf, tl);
  }
  else
  {
    return;
  }

  if (isDegenerated(aGAHS, anAHC2d, tf, tl))
    return;

  int                   aMaxDeg = 8;
  int                   aMaxSeg = 1000;
  Approx_CurveOnSurface anApp(anAHC2d, aGAHS, tf, tl, Precision::Confusion());
  anApp.Perform(aMaxSeg, aMaxDeg, GeomAbs_C1, true, false);
  if (!anApp.HasResult())
    return;

  theC3d        = anApp.Curve3d();
  theTolReached = anApp.MaxError3d();
  double aTol   = Precision::Confusion();
  if (theRL->IsArcOnS1())
  {
    occ::handle<Geom_Surface> aS = GeomAdaptor::MakeSurface(*theHS2);
    BuildPCurves(tf, tl, aTol, aS, theC3d, theC2d2);
  }
  if (theRL->IsArcOnS2())
  {
    occ::handle<Geom_Surface> aS = GeomAdaptor::MakeSurface(*theHS1);
    BuildPCurves(tf, tl, aTol, aS, theC3d, theC2d1);
  }
  theTolReached = std::max(theTolReached, aTol);
}

void GeomInt_IntSS::BuildPCurves(const double                     theFirst,
                                 const double                     theLast,
                                 const double                     theUmin,
                                 const double                     theUmax,
                                 const double                     theVmin,
                                 const double                     theVmax,
                                 double&                          theTol,
                                 const occ::handle<Geom_Surface>& theSurface,
                                 const occ::handle<Geom_Curve>&   theCurve,
                                 occ::handle<Geom2d_Curve>&       theCurve2d)
{
  if (!theCurve2d.IsNull() || theSurface.IsNull())
  {
    return;
  }

  if ((theLast - theFirst) > 2.e-09)
  {
    theCurve2d = GeomProjLib::Curve2d(theCurve,
                                      theFirst,
                                      theLast,
                                      theSurface,
                                      theUmin,
                                      theUmax,
                                      theVmin,
                                      theVmax,
                                      theTol);
    if (theCurve2d.IsNull())
    {

      theTol += Precision::Confusion();
      theCurve2d = GeomProjLib::Curve2d(theCurve, theFirst, theLast, theSurface, theTol);
    }
    const occ::handle<Standard_Type>& aType = theCurve2d->DynamicType();
    if (aType == STANDARD_TYPE(Geom2d_BSplineCurve))
    {

      if ((theCurve2d->FirstParameter() - theFirst > Precision::PConfusion())
          || (theLast - theCurve2d->LastParameter() > Precision::PConfusion()))
      {
        occ::handle<Geom2d_BSplineCurve> aBspl = occ::down_cast<Geom2d_BSplineCurve>(theCurve2d);
        NCollection_Array1<double>       aKnots(1, aBspl->NbKnots());
        aBspl->Knots(aKnots);
        BSplCLib::Reparametrize(theFirst, theLast, aKnots);
        aBspl->SetKnots(aKnots);
      }
    }
  }
  else
  {
    if ((theLast - theFirst) > Epsilon(std::abs(theFirst)))
    {

      double              aU = 0., aV = 0.;
      GeomAdaptor_Surface anAS;
      anAS.Load(theSurface);
      Extrema_ExtPS anExtr;
      const gp_Pnt  aP3d1 = theCurve->Value(theFirst);
      const gp_Pnt  aP3d2 = theCurve->Value(theLast);

      anExtr.SetAlgo(Extrema_ExtAlgo_Grad);
      anExtr.Initialize(anAS,
                        theUmin,
                        theUmax,
                        theVmin,
                        theVmax,
                        Precision::Confusion(),
                        Precision::Confusion());
      anExtr.Perform(aP3d1);

      if (ParametersOfNearestPointOnSurface(anExtr, aU, aV))
      {
        const gp_Pnt2d aP2d1(aU, aV);

        anExtr.Perform(aP3d2);

        if (ParametersOfNearestPointOnSurface(anExtr, aU, aV))
        {
          const gp_Pnt2d aP2d2(aU, aV);

          if (aP2d1.Distance(aP2d2) > gp::Resolution())
          {
            NCollection_Array1<gp_Pnt2d> poles(1, 2);
            NCollection_Array1<double>   knots(1, 2);
            NCollection_Array1<int>      mults(1, 2);
            poles(1) = aP2d1;
            poles(2) = aP2d2;
            knots(1) = theFirst;
            knots(2) = theLast;
            mults(1) = mults(2) = 2;

            theCurve2d = new Geom2d_BSplineCurve(poles, knots, mults, 1);

            const gp_Pnt   PMid(theCurve->Value(0.5 * (theFirst + theLast)));
            const gp_Pnt2d pmidcurve2d(0.5 * (aP2d1.XY() + aP2d2.XY()));
            const gp_Pnt   aPC(anAS.Value(pmidcurve2d.X(), pmidcurve2d.Y()));
            const double   aDist = PMid.Distance(aPC);
            theTol               = std::max(aDist, theTol);
          }
        }
      }
    }
  }

  if (theSurface->IsUPeriodic() && !theCurve2d.IsNull())
  {

    double aTm, U0, aEps, period, du, U0x;
    bool   bAdjust;

    aEps   = Precision::PConfusion();
    period = theSurface->UPeriod();

    aTm         = .5 * (theFirst + theLast);
    gp_Pnt2d pm = theCurve2d->Value(aTm);
    U0          = pm.X();

    bAdjust = GeomInt::AdjustPeriodic(U0, theUmin, theUmax, period, U0x, du, aEps);
    if (bAdjust)
    {
      gp_Vec2d T1(du, 0.);
      theCurve2d->Translate(T1);
    }
  }
}

void GeomInt_IntSS::BuildPCurves(const double                     f,
                                 const double                     l,
                                 double&                          Tol,
                                 const occ::handle<Geom_Surface>& S,
                                 const occ::handle<Geom_Curve>&   C,
                                 occ::handle<Geom2d_Curve>&       C2d)
{
  if (!C2d.IsNull() || S.IsNull())
  {
    return;
  }

  double umin, umax, vmin, vmax;

  S->Bounds(umin, umax, vmin, vmax);

  BuildPCurves(f, l, umin, umax, vmin, vmax, Tol, S, C, C2d);
}

void GeomInt_IntSS::TrimILineOnSurfBoundaries(const occ::handle<Geom2d_Curve>& theC2d1,
                                              const occ::handle<Geom2d_Curve>& theC2d2,
                                              const Bnd_Box2d&                 theBound1,
                                              const Bnd_Box2d&                 theBound2,
                                              NCollection_Vector<double>&      theArrayOfParameters)
{

  const int                 aNumberOfCurves = 4;
  occ::handle<Geom2d_Curve> aCurS1Bounds[aNumberOfCurves];
  occ::handle<Geom2d_Curve> aCurS2Bounds[aNumberOfCurves];

  double aU1f = 0.0, aV1f = 0.0, aU1l = 0.0, aV1l = 0.0;
  double aU2f = 0.0, aV2f = 0.0, aU2l = 0.0, aV2l = 0.0;

  theBound1.Get(aU1f, aV1f, aU1l, aV1l);
  theBound2.Get(aU2f, aV2f, aU2l, aV2l);

  double aDelta = aV1l - aV1f;
  if (std::abs(aDelta) > RealSmall())
  {
    if (!Precision::IsInfinite(aU1f))
    {
      aCurS1Bounds[0] = new Geom2d_Line(gp_Pnt2d(aU1f, aV1f), gp_Dir2d(gp_Dir2d::D::Y));

      if (!Precision::IsInfinite(aDelta))
        aCurS1Bounds[0] = new Geom2d_TrimmedCurve(aCurS1Bounds[0], 0, aDelta);
    }

    if (!Precision::IsInfinite(aU1l))
    {
      aCurS1Bounds[1] = new Geom2d_Line(gp_Pnt2d(aU1l, aV1f), gp_Dir2d(gp_Dir2d::D::Y));
      if (!Precision::IsInfinite(aDelta))
        aCurS1Bounds[1] = new Geom2d_TrimmedCurve(aCurS1Bounds[1], 0, aDelta);
    }
  }

  aDelta = aU1l - aU1f;
  if (std::abs(aDelta) > RealSmall())
  {
    if (!Precision::IsInfinite(aV1f))
    {
      aCurS1Bounds[2] = new Geom2d_Line(gp_Pnt2d(aU1f, aV1f), gp_Dir2d(gp_Dir2d::D::X));
      if (!Precision::IsInfinite(aDelta))
        aCurS1Bounds[2] = new Geom2d_TrimmedCurve(aCurS1Bounds[2], 0, aDelta);
    }

    if (!Precision::IsInfinite(aV1l))
    {
      aCurS1Bounds[3] = new Geom2d_Line(gp_Pnt2d(aU1f, aV1l), gp_Dir2d(gp_Dir2d::D::X));
      if (!Precision::IsInfinite(aDelta))
        aCurS1Bounds[3] = new Geom2d_TrimmedCurve(aCurS1Bounds[3], 0, aDelta);
    }
  }

  aDelta = aV2l - aV2f;
  if (std::abs(aDelta) > RealSmall())
  {
    if (!Precision::IsInfinite(aU2f))
    {
      aCurS2Bounds[0] = new Geom2d_Line(gp_Pnt2d(aU2f, aV2f), gp_Dir2d(gp_Dir2d::D::Y));
      if (!Precision::IsInfinite(aDelta))
        aCurS2Bounds[0] = new Geom2d_TrimmedCurve(aCurS2Bounds[0], 0, aDelta);
    }

    if (!Precision::IsInfinite(aU2l))
    {
      aCurS2Bounds[1] = new Geom2d_Line(gp_Pnt2d(aU2l, aV2f), gp_Dir2d(gp_Dir2d::D::Y));
      if (!Precision::IsInfinite(aDelta))
        aCurS2Bounds[1] = new Geom2d_TrimmedCurve(aCurS2Bounds[1], 0, aDelta);
    }
  }

  aDelta = aU2l - aU2f;
  if (std::abs(aDelta) > RealSmall())
  {
    if (!Precision::IsInfinite(aV2f))
    {
      aCurS2Bounds[2] = new Geom2d_Line(gp_Pnt2d(aU2f, aV2f), gp_Dir2d(gp_Dir2d::D::X));
      if (!Precision::IsInfinite(aDelta))
        aCurS2Bounds[2] = new Geom2d_TrimmedCurve(aCurS2Bounds[2], 0, aDelta);
    }

    if (!Precision::IsInfinite(aV2l))
    {
      aCurS2Bounds[3] = new Geom2d_Line(gp_Pnt2d(aU2f, aV2l), gp_Dir2d(gp_Dir2d::D::X));
      if (!Precision::IsInfinite(aDelta))
        aCurS2Bounds[3] = new Geom2d_TrimmedCurve(aCurS2Bounds[3], 0, aDelta);
    }
  }

  constexpr double anIntTol = 10.0 * Precision::Confusion();

  IntersectCurveAndBoundary(theC2d1, aCurS1Bounds, aNumberOfCurves, anIntTol, theArrayOfParameters);

  IntersectCurveAndBoundary(theC2d2, aCurS2Bounds, aNumberOfCurves, anIntTol, theArrayOfParameters);

  std::sort(theArrayOfParameters.begin(), theArrayOfParameters.end());
}

occ::handle<Geom_Curve> GeomInt_IntSS::MakeBSpline(const occ::handle<IntPatch_WLine>& WL,
                                                   const int                          ideb,
                                                   const int                          ifin)
{
  const int                  nbpnt = ifin - ideb + 1;
  NCollection_Array1<gp_Pnt> poles(1, nbpnt);
  NCollection_Array1<double> knots(1, nbpnt);
  NCollection_Array1<int>    mults(1, nbpnt);
  int                        i = 1, ipidebm1 = ideb;
  for (; i <= nbpnt; ipidebm1++, i++)
  {
    poles(i) = WL->Point(ipidebm1).Value();
    mults(i) = 1;
    knots(i) = i - 1;
  }
  mults(1) = mults(nbpnt) = 2;
  return new Geom_BSplineCurve(poles, knots, mults, 1);
}

occ::handle<Geom2d_BSplineCurve> GeomInt_IntSS::MakeBSpline2d(
  const occ::handle<IntPatch_WLine>& theWLine,
  const int                          ideb,
  const int                          ifin,
  const bool                         onFirst)
{
  const int                    nbpnt = ifin - ideb + 1;
  NCollection_Array1<gp_Pnt2d> poles(1, nbpnt);
  NCollection_Array1<double>   knots(1, nbpnt);
  NCollection_Array1<int>      mults(1, nbpnt);
  int                          i = 1, ipidebm1 = ideb;
  for (; i <= nbpnt; ipidebm1++, i++)
  {
    double U, V;
    if (onFirst)
      theWLine->Point(ipidebm1).ParametersOnS1(U, V);
    else
      theWLine->Point(ipidebm1).ParametersOnS2(U, V);
    poles(i).SetCoord(U, V);
    mults(i) = 1;
    knots(i) = i - 1;
  }

  mults(1) = mults(nbpnt) = 2;
  return new Geom2d_BSplineCurve(poles, knots, mults, 1);
}
