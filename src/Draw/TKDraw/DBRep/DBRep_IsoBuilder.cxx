#include <BRep_Tool.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepTools.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <DBRep_Face.hpp>
#include <DBRep_IsoBuilder.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom2dHatch_Intersector.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Pnt2d.hpp>
#include <HatchGen_Domain.hpp>
#include <Precision.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>

static double IntersectorConfusion = Precision::PConfusion();
static double IntersectorTangency  = Precision::PConfusion();
static double HatcherConfusion2d   = 1.e-8;
static double HatcherConfusion3d   = 1.e-8;

DBRep_IsoBuilder::DBRep_IsoBuilder(const TopoDS_Face& TopologicalFace,
                                   const double       Infinite,
                                   const int          NbIsos)
    : Geom2dHatch_Hatcher(Geom2dHatch_Intersector(IntersectorConfusion, IntersectorTangency),
                          HatcherConfusion2d,
                          HatcherConfusion3d,
                          true,
                          false),
      myInfinite(Infinite),
      myUMin(0.0),
      myUMax(0.0),
      myVMin(0.0),
      myVMax(0.0),
      myUPrm(1, NbIsos),
      myUInd(1, NbIsos),
      myVPrm(1, NbIsos),
      myVInd(1, NbIsos),
      myNbDom(0)
{
  myUInd.Init(0);
  myVInd.Init(0);

  BRepTools::UVBounds(TopologicalFace, myUMin, myUMax, myVMin, myVMax);
  bool InfiniteUMin = Precision::IsNegativeInfinite(myUMin);
  bool InfiniteUMax = Precision::IsPositiveInfinite(myUMax);
  bool InfiniteVMin = Precision::IsNegativeInfinite(myVMin);
  bool InfiniteVMax = Precision::IsPositiveInfinite(myVMax);
  if (InfiniteUMin && InfiniteUMax)
  {
    myUMin = -Infinite;
    myUMax = Infinite;
  }
  else if (InfiniteUMin)
  {
    myUMin = myUMax - Infinite;
  }
  else if (InfiniteUMax)
  {
    myUMax = myUMin + Infinite;
  }
  if (InfiniteVMin && InfiniteVMax)
  {
    myVMin = -Infinite;
    myVMax = Infinite;
  }
  else if (InfiniteVMin)
  {
    myVMin = myVMax - Infinite;
  }
  else if (InfiniteVMax)
  {
    myVMax = myVMin + Infinite;
  }

  DataMapOfEdgePCurve anEdgePCurveMap;

  TopExp_Explorer ExpEdges;
  for (ExpEdges.Init(TopologicalFace, TopAbs_EDGE); ExpEdges.More(); ExpEdges.Next())
  {
    const TopoDS_Edge&              TopologicalEdge = TopoDS::Edge(ExpEdges.Current());
    double                          U1, U2;
    const occ::handle<Geom2d_Curve> PCurve =
      BRep_Tool::CurveOnSurface(TopologicalEdge, TopologicalFace, U1, U2);

    if (PCurve.IsNull())
    {
#ifdef OCCT_DEBUG
      std::cout << "DBRep_IsoBuilder : PCurve is null\n";
#endif
      return;
    }
    else if (U1 == U2)
    {
#ifdef OCCT_DEBUG
      std::cout << "DBRep_IsoBuilder PCurve : U1==U2\n";
#endif
      return;
    }

    if (std::abs(PCurve->FirstParameter() - U1) <= Precision::PConfusion()
        && std::abs(PCurve->LastParameter() - U2) <= Precision::PConfusion())
    {
      anEdgePCurveMap.Add(TopologicalEdge, PCurve);
    }
    else
    {
      if (!PCurve->IsPeriodic())
      {
        occ::handle<Geom2d_TrimmedCurve> TrimPCurve = occ::down_cast<Geom2d_TrimmedCurve>(PCurve);
        if (!TrimPCurve.IsNull())
        {
          if (TrimPCurve->BasisCurve()->FirstParameter() - U1 > Precision::PConfusion()
              || TrimPCurve->BasisCurve()->FirstParameter() - U2 > Precision::PConfusion()
              || U1 - TrimPCurve->BasisCurve()->LastParameter() > Precision::PConfusion()
              || U2 - TrimPCurve->BasisCurve()->LastParameter() > Precision::PConfusion())
          {
#ifdef OCCT_DEBUG
            std::cout << "DBRep_IsoBuilder TrimPCurve : parameters out of range\n";
            std::cout << "    U1(" << U1 << "), Umin(" << PCurve->FirstParameter() << "), U2(" << U2
                      << "), Umax(" << PCurve->LastParameter() << ")\n";
#endif
            return;
          }
        }
        else
        {
          if (PCurve->FirstParameter() - U1 > Precision::PConfusion())
          {
#ifdef OCCT_DEBUG
            std::cout << "DBRep_IsoBuilder PCurve : parameters out of range\n";
            std::cout << "    U1(" << U1 << "), Umin(" << PCurve->FirstParameter() << ")\n";
#endif
            U1 = PCurve->FirstParameter();
          }
          if (PCurve->FirstParameter() - U2 > Precision::PConfusion())
          {
#ifdef OCCT_DEBUG
            std::cout << "DBRep_IsoBuilder PCurve : parameters out of range\n";
            std::cout << "    U2(" << U2 << "), Umin(" << PCurve->FirstParameter() << ")\n";
#endif
            U2 = PCurve->FirstParameter();
          }
          if (U1 - PCurve->LastParameter() > Precision::PConfusion())
          {
#ifdef OCCT_DEBUG
            std::cout << "DBRep_IsoBuilder PCurve : parameters out of range\n";
            std::cout << "    U1(" << U1 << "), Umax(" << PCurve->LastParameter() << ")\n";
#endif
            U1 = PCurve->LastParameter();
          }
          if (U2 - PCurve->LastParameter() > Precision::PConfusion())
          {
#ifdef OCCT_DEBUG
            std::cout << "DBRep_IsoBuilder PCurve : parameters out of range\n";
            std::cout << "    U2(" << U2 << "), Umax(" << PCurve->LastParameter() << ")\n";
#endif
            U2 = PCurve->LastParameter();
          }
        }
      }

      if (std::abs(U1 - U2) <= Precision::PConfusion())
        continue;
      occ::handle<Geom2d_TrimmedCurve> TrimPCurve = new Geom2d_TrimmedCurve(PCurve, U1, U2);
      anEdgePCurveMap.Add(TopologicalEdge, TrimPCurve);
    }
  }

  FillGaps(TopologicalFace, anEdgePCurveMap);

  int aNbE = anEdgePCurveMap.Extent();
  for (int iE = 1; iE <= aNbE; ++iE)
  {
    AddElement(Geom2dAdaptor_Curve(anEdgePCurveMap(iE)), anEdgePCurveMap.FindKey(iE).Orientation());
  }

  int    IIso;
  double DeltaU    = std::abs(myUMax - myUMin);
  double DeltaV    = std::abs(myVMax - myVMin);
  double confusion = std::min(DeltaU, DeltaV) * HatcherConfusion3d;
  Confusion3d(confusion);

  double StepU = DeltaU / (double)NbIsos;
  if (StepU > confusion)
  {
    double   UPrm = myUMin + StepU / 2.;
    gp_Dir2d Dir(gp_Dir2d::D::Y);
    for (IIso = 1; IIso <= NbIsos; IIso++)
    {
      myUPrm(IIso) = UPrm;
      gp_Pnt2d            Ori(UPrm, 0.);
      Geom2dAdaptor_Curve HCur(new Geom2d_Line(Ori, Dir));
      myUInd(IIso) = AddHatching(HCur);
      UPrm += StepU;
    }
  }

  double StepV = DeltaV / (double)NbIsos;
  if (StepV > confusion)
  {
    double   VPrm = myVMin + StepV / 2.;
    gp_Dir2d Dir(gp_Dir2d::D::X);
    for (IIso = 1; IIso <= NbIsos; IIso++)
    {
      myVPrm(IIso) = VPrm;
      gp_Pnt2d            Ori(0., VPrm);
      Geom2dAdaptor_Curve HCur(new Geom2d_Line(Ori, Dir));
      myVInd(IIso) = AddHatching(HCur);
      VPrm += StepV;
    }
  }

  Trim();

  myNbDom = 0;
  for (IIso = 1; IIso <= NbIsos; IIso++)
  {
    int Index;

    Index = myUInd(IIso);
    if (Index != 0)
    {
      if (TrimDone(Index) && !TrimFailed(Index))
      {
        ComputeDomains(Index);
        if (IsDone(Index))
          myNbDom = myNbDom + Geom2dHatch_Hatcher::NbDomains(Index);
      }
    }

    Index = myVInd(IIso);
    if (Index != 0)
    {
      if (TrimDone(Index) && !TrimFailed(Index))
      {
        ComputeDomains(Index);
        if (IsDone(Index))
          myNbDom = myNbDom + Geom2dHatch_Hatcher::NbDomains(Index);
      }
    }
  }
}

void DBRep_IsoBuilder::LoadIsos(const occ::handle<DBRep_Face>& Face) const
{
  int NumIso = 0;

  for (int UIso = myUPrm.Lower(); UIso <= myUPrm.Upper(); UIso++)
  {
    int UInd = myUInd.Value(UIso);
    if (UInd != 0)
    {
      double UPrm = myUPrm.Value(UIso);
      if (!IsDone(UInd))
      {
        std::cout << "DBRep_IsoBuilder:: U iso of parameter: " << UPrm;
        switch (Status(UInd))
        {
          case HatchGen_NoProblem:
            std::cout << " No Problem" << std::endl;
            break;
          case HatchGen_TrimFailure:
            std::cout << " Trim Failure" << std::endl;
            break;
          case HatchGen_TransitionFailure:
            std::cout << " Transition Failure" << std::endl;
            break;
          case HatchGen_IncoherentParity:
            std::cout << " Incoherent Parity" << std::endl;
            break;
          case HatchGen_IncompatibleStates:
            std::cout << " Incompatible States" << std::endl;
            break;
        }
      }
      else
      {
        int NbDom = Geom2dHatch_Hatcher::NbDomains(UInd);
        for (int IDom = 1; IDom <= NbDom; IDom++)
        {
          const HatchGen_Domain& Dom = Domain(UInd, IDom);
          double V1 = Dom.HasFirstPoint() ? Dom.FirstPoint().Parameter() : myVMin - myInfinite;
          double V2 = Dom.HasSecondPoint() ? Dom.SecondPoint().Parameter() : myVMax + myInfinite;
          NumIso++;
          Face->Iso(NumIso, GeomAbs_IsoU, UPrm, V1, V2);
        }
      }
    }
  }

  for (int VIso = myVPrm.Lower(); VIso <= myVPrm.Upper(); VIso++)
  {
    int VInd = myVInd.Value(VIso);
    if (VInd != 0)
    {
      double VPrm = myVPrm.Value(VIso);
      if (!IsDone(VInd))
      {
        std::cout << "DBRep_IsoBuilder:: V iso of parameter: " << VPrm;
        switch (Status(VInd))
        {
          case HatchGen_NoProblem:
            std::cout << " No Problem" << std::endl;
            break;
          case HatchGen_TrimFailure:
            std::cout << " Trim Failure" << std::endl;
            break;
          case HatchGen_TransitionFailure:
            std::cout << " Transition Failure" << std::endl;
            break;
          case HatchGen_IncoherentParity:
            std::cout << " Incoherent Parity" << std::endl;
            break;
          case HatchGen_IncompatibleStates:
            std::cout << " Incompatible States" << std::endl;
            break;
        }
      }
      else
      {
        int NbDom = Geom2dHatch_Hatcher::NbDomains(VInd);
        for (int IDom = 1; IDom <= NbDom; IDom++)
        {
          const HatchGen_Domain& Dom = Domain(VInd, IDom);
          double U1 = Dom.HasFirstPoint() ? Dom.FirstPoint().Parameter() : myVMin - myInfinite;
          double U2 = Dom.HasSecondPoint() ? Dom.SecondPoint().Parameter() : myVMax + myInfinite;
          NumIso++;
          Face->Iso(NumIso, GeomAbs_IsoV, VPrm, U1, U2);
        }
      }
    }
  }
}

void DBRep_IsoBuilder::FillGaps(const TopoDS_Face& theFace, DataMapOfEdgePCurve& theEdgePCurveMap)
{

  BRepAdaptor_Surface aBASurf(theFace, false);

  TopoDS_Iterator aItW(theFace);
  for (; aItW.More(); aItW.Next())
  {
    const TopoDS_Shape& aW = aItW.Value();
    if (aW.ShapeType() != TopAbs_WIRE)
      continue;

    BRepTools_WireExplorer aWExp;
    aWExp.Init(TopoDS::Wire(aW), theFace, myUMin, myUMax, myVMin, myVMax);
    if (!aWExp.More())
      continue;

    if (aW.NbChildren() == 0)
    {
      continue;
    }
    bool SingleEdge = (aW.NbChildren() == 1);

    TopoDS_Edge aPrevEdge, aCurrEdge;

    aCurrEdge = aWExp.Current();

    TopoDS_Edge aFirstEdge = aCurrEdge;
    double      bStop      = false;

    while (!bStop)
    {

      aPrevEdge = aCurrEdge;
      aWExp.Next();

      if (aWExp.More())
      {
        aCurrEdge = aWExp.Current();
      }
      else
      {
        aCurrEdge = aFirstEdge;
        bStop     = true;
      }

      if (aPrevEdge.IsEqual(aCurrEdge) && !SingleEdge)
        continue;

      occ::handle<Geom2d_Curve>* pPC1 = theEdgePCurveMap.ChangeSeek(aPrevEdge);
      occ::handle<Geom2d_Curve>* pPC2 = theEdgePCurveMap.ChangeSeek(aCurrEdge);
      if (!pPC1 || !pPC2)
        continue;

      occ::handle<Geom2d_Curve>& aPrevC2d = *pPC1;
      occ::handle<Geom2d_Curve>& aCurrC2d = *pPC2;

      double fp, lp, fc, lc;
      fp = aPrevC2d->FirstParameter();
      lp = aPrevC2d->LastParameter();
      fc = aCurrC2d->FirstParameter();
      lc = aCurrC2d->LastParameter();

      TopoDS_Vertex aCVOnPrev = TopExp::LastVertex(aPrevEdge, true);
      if (aCVOnPrev.IsNull())
        continue;

      double aTPrev = BRep_Tool::Parameter(aCVOnPrev, aPrevEdge);
      if (aTPrev < fp)
        aTPrev = fp;
      else if (aTPrev > lp)
        aTPrev = lp;

      TopoDS_Vertex aCVOnCurr = TopExp::FirstVertex(aCurrEdge, true);
      if (aCVOnCurr.IsNull() || !aCVOnPrev.IsSame(aCVOnCurr))
        continue;

      double aTCurr = BRep_Tool::Parameter(aCVOnCurr, aCurrEdge);
      if (aTCurr < fc)
        aTCurr = fc;
      else if (aTCurr > lc)
        aTCurr = lc;

      gp_Pnt2d aPrevP2d = aPrevC2d->Value(aTPrev), aCurrP2d = aCurrC2d->Value(aTCurr);

      double aTolV2 = BRep_Tool::Tolerance(aCVOnPrev);
      gp_Pnt aPV    = BRep_Tool::Pnt(aCVOnPrev);

      if (aTolV2 < Precision::Infinite())
      {
        aTolV2 *= aTolV2;

        gp_Pnt aPrevPS = aBASurf.Value(aPrevP2d.X(), aPrevP2d.Y());

        if (aPV.SquareDistance(aPrevPS) > aTolV2)
          continue;

        gp_Pnt aCurrPS = aBASurf.Value(aCurrP2d.X(), aCurrP2d.Y());

        if (aPV.SquareDistance(aCurrPS) > aTolV2)
          continue;
      }

      gp_Vec2d aV2d(aPrevP2d, aCurrP2d);
      double   aSegmLen = aV2d.Magnitude();

      bool bAddSegment = (aSegmLen > Precision::PConfusion());

      if (bAddSegment)
      {
        if (aBASurf.IsUPeriodic())
          bAddSegment = aSegmLen < aBASurf.UPeriod() / 4.;

        if (bAddSegment && aBASurf.IsVPeriodic())
          bAddSegment = aSegmLen < aBASurf.VPeriod() / 4.;
      }

      if (bAddSegment && !aPrevEdge.IsEqual(aCurrEdge))
      {
        Geom2dAdaptor_Curve aPrevGC(aPrevC2d, fp, lp), aCurrGC(aCurrC2d, fc, lc);
        Geom2dInt_GInter    anInter(aPrevGC,
                                 aCurrGC,
                                 Precision::PConfusion(),
                                 Precision::PConfusion());
        if (anInter.IsDone() && !anInter.IsEmpty())
        {

          NCollection_List<IntRes2d_IntersectionPoint> aLPInt;

          int iP, aNbInt = anInter.NbSegments();
          for (iP = 1; iP <= aNbInt; ++iP)
          {
            aLPInt.Append(anInter.Segment(iP).FirstPoint());
            aLPInt.Append(anInter.Segment(iP).LastPoint());
          }

          aNbInt = anInter.NbPoints();
          for (iP = 1; iP <= aNbInt; ++iP)
            aLPInt.Append(anInter.Point(iP));

          bool   bPointFound   = false;
          double aTPrevClosest = 0., aTCurrClosest = 0.;
          double aDeltaPrev = ::RealLast(), aDeltaCurr = ::RealLast();

          NCollection_List<IntRes2d_IntersectionPoint>::Iterator aItLPInt(aLPInt);
          for (; aItLPInt.More(); aItLPInt.Next())
          {
            const IntRes2d_IntersectionPoint& aPnt      = aItLPInt.Value();
            const double                      aTIntPrev = aPnt.ParamOnFirst();
            const double                      aTIntCurr = aPnt.ParamOnSecond();

            if (aTIntPrev < fp || aTIntPrev > lp || aTIntCurr < fc || aTIntCurr > lc)
            {
              continue;
            }

            double aDelta1 = std::abs(aTIntPrev - aTPrev);
            double aDelta2 = std::abs(aTIntCurr - aTCurr);
            if (aDelta1 < aDeltaPrev || aDelta2 < aDeltaCurr)
            {
              aTPrevClosest = aTIntPrev;
              aTCurrClosest = aTIntCurr;
              aDeltaPrev    = aDelta1;
              aDeltaCurr    = aDelta2;
              bPointFound   = true;
            }
          }

          if (bPointFound)
          {

            int aNbCV = 0;
            for (TopoDS_Iterator it1(aPrevEdge); it1.More(); it1.Next())
            {
              for (TopoDS_Iterator it2(aCurrEdge); it2.More(); it2.Next())
              {
                if (it1.Value().IsSame(it2.Value()))
                  ++aNbCV;
              }
            }

            bool bTrim = (aNbCV == 1
                          || (std::abs(aTPrev - aTPrevClosest) < (lp - fp) / 2.
                              || std::abs(aTCurr - aTCurrClosest) < (lc - fc) / 2.));

            if (bTrim)
            {

              gp_Pnt2d     aPInt = aPrevC2d->Value(aTPrevClosest);
              const gp_Pnt aPOnS = aBASurf.Value(aPInt.X(), aPInt.Y());
              if (aTolV2 > Precision::Infinite() || aPOnS.SquareDistance(aPV) < aTolV2)
              {
                double f, l;

                if (std::abs(fp - aTPrev) < std::abs(lp - aTPrev))
                {
                  f = aTPrevClosest;
                  l = lp;
                }
                else
                {
                  f = fp;
                  l = aTPrevClosest;
                }

                if (l - f > Precision::PConfusion())
                  aPrevC2d = new Geom2d_TrimmedCurve(aPrevC2d, f, l);

                if (std::abs(fc - aTCurr) < std::abs(lc - aTCurr))
                {
                  f = aTCurrClosest;
                  l = lc;
                }
                else
                {
                  f = fc;
                  l = aTCurrClosest;
                }

                if (l - f > Precision::PConfusion())
                  aCurrC2d = new Geom2d_TrimmedCurve(aCurrC2d, f, l);

                bAddSegment = false;
              }
            }
          }
        }
      }

      if (bAddSegment)
      {

        occ::handle<Geom2d_Line>         aLine     = new Geom2d_Line(aPrevP2d, aV2d);
        occ::handle<Geom2d_TrimmedCurve> aLineSegm = new Geom2d_TrimmedCurve(aLine, 0.0, aSegmLen);
        AddElement(Geom2dAdaptor_Curve(aLineSegm), TopAbs_FORWARD);
      }
    }
  }
}
