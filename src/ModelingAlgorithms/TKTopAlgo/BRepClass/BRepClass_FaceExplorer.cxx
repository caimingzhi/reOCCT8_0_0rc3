#include <BRep_Tool.hpp>
#include <BRepClass_Edge.hpp>
#include <BRepClass_FaceExplorer.hpp>
#include <BRepTools.hpp>
#include <Geom2d_Curve.hpp>
#include <Precision.hpp>
#include <TopoDS.hpp>
#include <TopExp.hpp>
#include <Geom2dAPI_ProjectPointOnCurve.hpp>

static const double Probing_Start = 0.123;
static const double Probing_End   = 0.7;
static const double Probing_Step  = 0.2111;

BRepClass_FaceExplorer::BRepClass_FaceExplorer(const TopoDS_Face& F)
    : myFace(F),
      myCurEdgeInd(1),
      myCurEdgePar(Probing_Start),
      myMaxTolerance(0.1),
      myUseBndBox(false),
      myUMin(Precision::Infinite()),
      myUMax(-Precision::Infinite()),
      myVMin(Precision::Infinite()),
      myVMax(-Precision::Infinite())

{
  myFace.Orientation(TopAbs_FORWARD);
}

void BRepClass_FaceExplorer::ComputeFaceBounds()
{
  TopLoc_Location                  aLocation;
  const occ::handle<Geom_Surface>& aSurface = BRep_Tool::Surface(myFace, aLocation);
  aSurface->Bounds(myUMin, myUMax, myVMin, myVMax);
  if (Precision::IsInfinite(myUMin) || Precision::IsInfinite(myUMax)
      || Precision::IsInfinite(myVMin) || Precision::IsInfinite(myVMax))
  {
    BRepTools::UVBounds(myFace, myUMin, myUMax, myVMin, myVMax);
  }
}

bool BRepClass_FaceExplorer::CheckPoint(gp_Pnt2d& thePoint)
{
  if (myUMin > myUMax)
  {
    ComputeFaceBounds();
  }

  if (Precision::IsInfinite(myUMin) || Precision::IsInfinite(myUMax)
      || Precision::IsInfinite(myVMin) || Precision::IsInfinite(myVMax))
  {
    return true;
  }

  gp_Pnt2d aCenterPnt((myUMin + myUMax) / 2, (myVMin + myVMax) / 2);
  double   aDistance = aCenterPnt.Distance(thePoint);
  if (Precision::IsInfinite(aDistance))
  {
    thePoint.SetCoord(myUMin - (myUMax - myUMin), myVMin - (myVMax - myVMin));
    return false;
  }
  else
  {
    double anEpsilon = Epsilon(aDistance);
    if (anEpsilon > std::max(myUMax - myUMin, myVMax - myVMin))
    {
      gp_Vec2d aLinVec(aCenterPnt, thePoint);
      gp_Dir2d aLinDir(aLinVec);
      thePoint = aCenterPnt.XY() + aLinDir.XY() * (2. * anEpsilon);
      return false;
    }
  }

  return true;
}

bool BRepClass_FaceExplorer::Reject(const gp_Pnt2d&) const
{
  return false;
}

bool BRepClass_FaceExplorer::Segment(const gp_Pnt2d& P, gp_Lin2d& L, double& Par)
{
  myCurEdgeInd = 1;
  myCurEdgePar = Probing_Start;

  return OtherSegment(P, L, Par);
}

bool BRepClass_FaceExplorer::OtherSegment(const gp_Pnt2d& P, gp_Lin2d& L, double& Par)
{
  TopExp_Explorer           anExpF(myFace, TopAbs_EDGE);
  int                       i;
  double                    aFPar;
  double                    aLPar;
  occ::handle<Geom2d_Curve> aC2d;
  constexpr double          aTolParConf2 = Precision::PConfusion() * Precision::PConfusion();
  gp_Pnt2d                  aPOnC;
  double                    aParamIn;

  for (i = 1; anExpF.More(); anExpF.Next(), i++)
  {
    if (i != myCurEdgeInd)
      continue;

    const TopoDS_Shape&      aLocalShape   = anExpF.Current();
    const TopAbs_Orientation anOrientation = aLocalShape.Orientation();

    if (anOrientation == TopAbs_FORWARD || anOrientation == TopAbs_REVERSED)
    {
      const TopoDS_Edge& anEdge = TopoDS::Edge(aLocalShape);

      aC2d = BRep_Tool::CurveOnSurface(anEdge, myFace, aFPar, aLPar);

      if (!aC2d.IsNull())
      {

        if (Precision::IsNegativeInfinite(aFPar))
        {
          if (Precision::IsPositiveInfinite(aLPar))
          {
            aFPar = -1.;
            aLPar = 1.;
          }
          else
          {
            aFPar = aLPar - 1.;
          }
        }
        else if (Precision::IsPositiveInfinite(aLPar))
          aLPar = aFPar + 1.;

        for (; myCurEdgePar < Probing_End; myCurEdgePar += Probing_Step)
        {
          aParamIn = myCurEdgePar * aFPar + (1. - myCurEdgePar) * aLPar;

          gp_Vec2d aTanVec;
          aC2d->D1(aParamIn, aPOnC, aTanVec);
          Par = aPOnC.SquareDistance(P);

          if (Par > aTolParConf2)
          {
            gp_Vec2d aLinVec(P, aPOnC);
            gp_Dir2d aLinDir(aLinVec);

            double aTanMod = aTanVec.SquareMagnitude();
            if (aTanMod < aTolParConf2)
              continue;
            aTanVec /= std::sqrt(aTanMod);
            double       aSinA        = aTanVec.Crossed(aLinDir.XY());
            const double SmallAngle   = 0.001;
            bool         isSmallAngle = false;
            if (std::abs(aSinA) < SmallAngle)
            {
              isSmallAngle = true;

              if (myCurEdgePar + Probing_Step < Probing_End)
                continue;
            }

            L = gp_Lin2d(P, aLinDir);

            aC2d->D0(aFPar, aPOnC);
            gp_Pnt2d aFPOnC = aPOnC;
            if (L.SquareDistance(aPOnC) > aTolParConf2)
            {
              aC2d->D0(aLPar, aPOnC);
              if (L.SquareDistance(aPOnC) > aTolParConf2)
              {

                if (isSmallAngle)
                {

                  Geom2dAPI_ProjectPointOnCurve aProj;
                  aProj.Init(P, aC2d, aFPar, aLPar);
                  if (aProj.NbPoints() > 0)
                  {
                    gp_Pnt2d aLPOnC   = aPOnC;
                    double   aFDist   = P.SquareDistance(aFPOnC);
                    double   aLDist   = P.SquareDistance(aLPOnC);
                    double   aMinDist = aProj.LowerDistance();
                    aMinDist *= aMinDist;
                    aPOnC = aProj.NearestPoint();
                    if (aMinDist > aFDist)
                    {
                      aMinDist = aFDist;
                      aPOnC    = aFPOnC;
                    }

                    if (aMinDist > aLDist)
                    {
                      aMinDist = aLDist;
                      aPOnC    = aLPOnC;
                    }

                    if (aMinDist < Par)
                    {
                      Par = aMinDist;
                      if (Par < aTolParConf2)
                      {
                        continue;
                      }
                      aLinVec.SetXY((aPOnC.XY() - P.XY()));
                      aLinDir.SetXY(aLinVec.XY());
                      L = gp_Lin2d(P, aLinDir);
                    }
                  }
                }
                myCurEdgePar += Probing_Step;
                if (myCurEdgePar >= Probing_End)
                {
                  myCurEdgeInd++;
                  myCurEdgePar = Probing_Start;
                }

                Par = std::sqrt(Par);
                return true;
              }
            }
          }
        }
      }
    }

    myCurEdgeInd++;
    myCurEdgePar = Probing_Start;
  }

  Par = RealLast();
  L   = gp_Lin2d(P, gp_Dir2d(gp_Dir2d::D::X));

  return false;
}

void BRepClass_FaceExplorer::InitWires()
{
  myWExplorer.Init(myFace, TopAbs_WIRE);
}

bool BRepClass_FaceExplorer::RejectWire(const gp_Lin2d&, const double) const
{
  return false;
}

void BRepClass_FaceExplorer::InitEdges()
{
  myEExplorer.Init(myWExplorer.Current(), TopAbs_EDGE);
  myMapVE.Clear();
  TopExp::MapShapesAndAncestors(myWExplorer.Current(), TopAbs_VERTEX, TopAbs_EDGE, myMapVE);
}

bool BRepClass_FaceExplorer::RejectEdge(const gp_Lin2d&, const double) const
{
  return false;
}

void BRepClass_FaceExplorer::CurrentEdge(BRepClass_Edge& E, TopAbs_Orientation& Or) const
{
  E.Edge() = TopoDS::Edge(myEExplorer.Current());
  E.Face() = myFace;
  Or       = E.Edge().Orientation();
  E.SetNextEdge(myMapVE);
  E.SetMaxTolerance(myMaxTolerance);
  E.SetUseBndBox(myUseBndBox);
}
