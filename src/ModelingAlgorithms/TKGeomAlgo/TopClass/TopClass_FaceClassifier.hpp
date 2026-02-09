#include <IntRes2d_IntersectionSegment.hpp>
#include <IntRes2d_IntersectionPoint.hpp>

TopClass_FaceClassifier::TopClass_FaceClassifier()
    : myEdgeParameter(0.0),
      rejected(false),
      nowires(true)
{
}

TopClass_FaceClassifier::TopClass_FaceClassifier(TheFaceExplorer& FExp,
                                                 const gp_Pnt2d&  P,
                                                 const double     Tol)
    : myEdgeParameter(0.0),
      rejected(false),
      nowires(true)
{
  Perform(FExp, P, Tol);
}

void TopClass_FaceClassifier::Perform(TheFaceExplorer& Fexp, const gp_Pnt2d& P, const double Tol)
{
  gp_Pnt2d aPoint(P);
  bool     aResOfPointCheck = false;
  while (aResOfPointCheck == false)
  {
    aResOfPointCheck = Fexp.CheckPoint(aPoint);
  }

  rejected = Fexp.Reject(aPoint);

  if (rejected)
    return;

  gp_Lin2d                   aLine;
  double                     aParam;
  bool                       IsValidSegment = Fexp.Segment(aPoint, aLine, aParam);
  TheEdge                    anEdge;
  TopAbs_Orientation         anEdgeOri;
  int                        aClosestInd;
  IntRes2d_IntersectionPoint aPInter;
  TopAbs_State               aState = TopAbs_UNKNOWN;
  bool                       IsWReject;
  bool                       IsEReject;

  nowires = true;

  while (IsValidSegment)
  {
    myClassifier.Reset(aLine, aParam, Tol);

    for (Fexp.InitWires(); Fexp.MoreWires(); Fexp.NextWire())
    {
      nowires   = false;
      IsWReject = Fexp.RejectWire(aLine, myClassifier.Parameter());

      if (!IsWReject)
      {

        for (Fexp.InitEdges(); Fexp.MoreEdges(); Fexp.NextEdge())
        {
          IsEReject = Fexp.RejectEdge(aLine, myClassifier.Parameter());

          if (!IsEReject)
          {

            Fexp.CurrentEdge(anEdge, anEdgeOri);

            if (anEdgeOri == TopAbs_FORWARD || anEdgeOri == TopAbs_REVERSED)
            {
              myClassifier.Compare(anEdge, anEdgeOri);
              aClosestInd = myClassifier.ClosestIntersection();

              if (aClosestInd != 0)
              {

                TheIntersection2d& anIntersector = myClassifier.Intersector();
                int                aNbPnts       = anIntersector.NbPoints();

                myEdge = anEdge;

                if (aClosestInd <= aNbPnts)
                {
                  aPInter = anIntersector.Point(aClosestInd);
                }
                else
                {
                  aClosestInd -= aNbPnts;

                  if (aClosestInd & 1)
                  {
                    aPInter = anIntersector.Segment((aClosestInd + 1) / 2).FirstPoint();
                  }
                  else
                  {
                    aPInter = anIntersector.Segment((aClosestInd + 1) / 2).LastPoint();
                  }
                }

                myPosition      = aPInter.TransitionOfSecond().PositionOnCurve();
                myEdgeParameter = aPInter.ParamOnSecond();
              }

              aState = myClassifier.State();

              if (aState == TopAbs_ON)
                return;
            }
          }
        }

        aState = myClassifier.State();

        if (aState == TopAbs_OUT)
          return;
      }
    }

    if (!myClassifier.IsHeadOrEnd() && aState != TopAbs_UNKNOWN)
      break;

    IsValidSegment = Fexp.OtherSegment(aPoint, aLine, aParam);
  }
}

TopAbs_State TopClass_FaceClassifier::State() const
{
  if (rejected)
    return TopAbs_OUT;
  else if (nowires)
    return TopAbs_IN;
  else
    return myClassifier.State();
}

const TheEdge& TopClass_FaceClassifier::Edge() const
{
  Standard_DomainError_Raise_if(rejected, "TopClass_FaceClassifier::Edge:rejected");
  return myEdge;
}

double TopClass_FaceClassifier::EdgeParameter() const
{
  Standard_DomainError_Raise_if(rejected, "TopClass_FaceClassifier::EdgeParameter:rejected");
  return myEdgeParameter;
}
