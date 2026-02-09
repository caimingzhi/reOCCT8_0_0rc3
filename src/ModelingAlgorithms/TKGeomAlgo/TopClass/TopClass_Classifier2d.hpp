#include <IntRes2d_IntersectionSegment.hpp>
#include <IntRes2d_IntersectionPoint.hpp>
#include <gp_Vec2d.hpp>

TopClass_Classifier2d::TopClass_Classifier2d()
    : myIsSet(false),
      myFirstCompare(true),
      myFirstTrans(true),
      myParam(0.0),
      myTolerance(0.0),
      myClosest(0),
      myState(TopAbs_UNKNOWN),
      myIsHeadOrEnd(false)
{
}

void TopClass_Classifier2d::Reset(const gp_Lin2d& L, const double P, const double Tol)
{
  myLin          = L;
  myParam        = P;
  myTolerance    = Tol;
  myState        = TopAbs_UNKNOWN;
  myFirstCompare = true;
  myFirstTrans   = true;
  myClosest      = 0;
  myIsSet        = true;

  myIsHeadOrEnd = false;
}

void TopClass_Classifier2d::Compare(const TheEdge& E, const TopAbs_Orientation Or)
{

  myClosest = 0;
  myIntersector.Perform(myLin, myParam, myTolerance, E);
  if (!myIntersector.IsDone())
    return;
  if ((myIntersector.NbPoints() == 0) && (myIntersector.NbSegments() == 0))
    return;

  int iPoint, iSegment, nbPoints, nbSegments;

  const IntRes2d_IntersectionPoint* PClosest = NULL;

  double dMin = RealLast();
  nbPoints    = myIntersector.NbPoints();
  for (iPoint = 1; iPoint <= nbPoints; iPoint++)
  {
    const IntRes2d_IntersectionPoint& PInter = myIntersector.Point(iPoint);

    if (PInter.TransitionOfFirst().PositionOnCurve() == IntRes2d_Head)
    {
      myClosest = iPoint;
      myState   = TopAbs_ON;
      return;
    }
    double paramfirst = PInter.ParamOnFirst();
    if (paramfirst < dMin)
    {
      myClosest = iPoint;
      PClosest  = &PInter;
      dMin      = paramfirst;
    }
  }

  nbSegments = myIntersector.NbSegments();
  for (iSegment = 1; iSegment <= nbSegments; iSegment++)
  {
    const IntRes2d_IntersectionSegment& SegInter = myIntersector.Segment(iSegment);
    const IntRes2d_IntersectionPoint&   PInter   = SegInter.FirstPoint();
    if (PInter.TransitionOfFirst().PositionOnCurve() == IntRes2d_Head)
    {
      myClosest = nbPoints + iSegment + iSegment - 1;
      myState   = TopAbs_ON;
      return;
    }
    double paramfirst = PInter.ParamOnFirst();
    if (paramfirst < dMin)
    {
      myClosest = nbPoints + iSegment + iSegment - 1;
      PClosest  = &PInter;
      dMin      = paramfirst;
    }
  }

  if (myClosest == 0)
    return;

  if (Or == TopAbs_INTERNAL)
  {
    myState = TopAbs_IN;
    return;
  }
  else if (Or == TopAbs_EXTERNAL)
  {
    myState = TopAbs_OUT;
    return;
  }

  if (!myFirstCompare)
  {
    bool b = (dMin > myParam);
    if (b)
    {

      return;
    }
  }

  myFirstCompare = false;

  if (myParam > dMin)
  {
    myFirstTrans = true;
  }

  myParam                       = dMin;
  const IntRes2d_Transition& T2 = PClosest->TransitionOfSecond();

  myIsHeadOrEnd = (T2.PositionOnCurve() == IntRes2d_Head) || (T2.PositionOnCurve() == IntRes2d_End);

  TopAbs_Orientation SegTrans = TopAbs_FORWARD;

  const IntRes2d_Transition& T1 = PClosest->TransitionOfFirst();
  switch (T1.TransitionType())
  {
    case IntRes2d_In:
      if (Or == TopAbs_REVERSED)
        SegTrans = TopAbs_REVERSED;
      else
        SegTrans = TopAbs_FORWARD;
      break;
    case IntRes2d_Out:
      if (Or == TopAbs_REVERSED)
        SegTrans = TopAbs_FORWARD;
      else
        SegTrans = TopAbs_REVERSED;
      break;
    case IntRes2d_Touch:
      switch (T1.Situation())
      {
        case IntRes2d_Inside:
          if (Or == TopAbs_REVERSED)
            SegTrans = TopAbs_EXTERNAL;
          else
            SegTrans = TopAbs_INTERNAL;
          break;
        case IntRes2d_Outside:
          if (Or == TopAbs_REVERSED)
            SegTrans = TopAbs_INTERNAL;
          else
            SegTrans = TopAbs_EXTERNAL;
          break;
        case IntRes2d_Unknown:
          return;
      }
      break;
    case IntRes2d_Undecided:
      return;
  }

  if (!myIsHeadOrEnd)
  {

    switch (SegTrans)
    {

      case TopAbs_FORWARD:
      case TopAbs_EXTERNAL:
        myState = TopAbs_OUT;
        break;

      case TopAbs_REVERSED:
      case TopAbs_INTERNAL:
        myState = TopAbs_IN;
        break;
    }
  }
  else
  {

    gp_Dir2d Tang2d, Norm2d;
    double   Curv;
    myIntersector.LocalGeometry(E, PClosest->ParamOnSecond(), Tang2d, Norm2d, Curv);
    gp_Dir Tang(Tang2d.X(), Tang2d.Y(), 0.);
    gp_Dir Norm(Norm2d.X(), Norm2d.Y(), 0.);
    if (myFirstTrans)
    {
      gp_Dir D(myLin.Direction().X(), myLin.Direction().Y(), 0.);
      myTrans.Reset(D);
      myFirstTrans = false;
    }

    TopAbs_Orientation Ort;
    if (T2.PositionOnCurve() == IntRes2d_Head)
      Ort = TopAbs_FORWARD;
    else
      Ort = TopAbs_REVERSED;
    myTrans.Compare(RealEpsilon(), Tang, Norm, Curv, SegTrans, Ort);
    myState = myTrans.StateBefore();
  }
}
