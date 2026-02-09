#include <BRep_Tool.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Failure.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRep_EdgesIntersector.hpp>
#include <TopOpeBRep_Point2d.hpp>
#include <TopOpeBRepDS_Transition.hpp>
#include <TopOpeBRepTool_ShapeTool.hpp>

const IntRes2d_IntersectionSegment& TopOpeBRep_EdgesIntersector::Segment1() const
{
  if (!IsPointOfSegment1())
    throw Standard_Failure("TopOpeBRep_EdgesIntersector : Not a segment point");
  int iseg = 1 + (myPointIndex - myNbPoints - 1) / 2;
  return mylseg.Value(iseg);
}

bool TopOpeBRep_EdgesIntersector::IsOpposite1() const
{
  bool b = Segment1().IsOpposite();
  return b;
}

void TopOpeBRep_EdgesIntersector::InitPoint1()
{
  myPointIndex         = 1;
  myIsVertexPointIndex = 0;
  myIsVertexIndex      = 0;
  myIsVertexValue      = false;
}

bool TopOpeBRep_EdgesIntersector::MorePoint1() const
{
  return myPointIndex <= myTrueNbPoints;
}

void TopOpeBRep_EdgesIntersector::NextPoint1()
{
  myPointIndex++;
}

const IntRes2d_IntersectionPoint& TopOpeBRep_EdgesIntersector::Point1() const
{
  if (!IsPointOfSegment1())
  {
    return mylpnt.Value(myPointIndex);
  }
  else
  {
    int i = myPointIndex - myNbPoints - 1;
    if (i % 2 == 0)
      return Segment1().FirstPoint();
    else
      return Segment1().LastPoint();
  }
}

TopOpeBRep_P2Dstatus TopOpeBRep_EdgesIntersector::Status1() const
{
  if (!IsPointOfSegment1())
  {
    return TopOpeBRep_P2DINT;
  }
  else
  {
    int i = myPointIndex - myNbPoints - 1;
    if (i % 2 == 0)
      return TopOpeBRep_P2DSGF;
    else
      return TopOpeBRep_P2DSGL;
  }
}

bool TopOpeBRep_EdgesIntersector::IsPointOfSegment1() const
{
  bool b = (myPointIndex > myNbPoints);
  return b;
}

int TopOpeBRep_EdgesIntersector::Index1() const
{
  return myPointIndex;
}

TopOpeBRepDS_Config TopOpeBRep_EdgesIntersector::EdgesConfig1() const
{
  TopOpeBRepDS_Config c  = TopOpeBRepDS_UNSHGEOMETRY;
  bool                ps = IsPointOfSegment1();
  if (ps)
  {
    bool so;
    so = TopOpeBRepTool_ShapeTool::EdgesSameOriented(myEdge2, myEdge1);
    c  = (so) ? TopOpeBRepDS_SAMEORIENTED : TopOpeBRepDS_DIFFORIENTED;
  }
  return c;
}

TopOpeBRepDS_Transition TopOpeBRep_EdgesIntersector::Transition1(
  const int                Index,
  const TopAbs_Orientation EdgeOrientation) const
{
  bool pointofsegment = IsPointOfSegment1();
  bool pur1d          = (pointofsegment && mySameDomain);

  TopAbs_State     staB = TopAbs_UNKNOWN, staA = TopAbs_UNKNOWN;
  TopAbs_ShapeEnum shaB = TopAbs_COMPOUND, shaA = TopAbs_COMPOUND;
  bool             pextremity;

  TopAbs_State staINON = TopAbs_IN;
  int          dim     = myDimension;
  if (dim == 1)
  {
    shaA = shaB = TopAbs_EDGE;
  }
  else if (dim == 2 && pur1d)
  {
    shaA = shaB = TopAbs_EDGE;
  }
  else if (dim == 2 && !pur1d)
  {
    shaA = shaB = TopAbs_FACE;
  }

  if ((EdgeOrientation == TopAbs_INTERNAL) || (EdgeOrientation == TopAbs_EXTERNAL))
  {
    TopOpeBRepDS_Transition TR(staINON, staINON, shaB, shaA);
    TR.Set(EdgeOrientation);
    return TR;
  }

  pextremity = false;

  const IntRes2d_IntersectionPoint& IP = Point1();
  const IntRes2d_Transition& T = (Index == 1) ? IP.TransitionOfFirst() : IP.TransitionOfSecond();

  switch (T.TransitionType())
  {

    case IntRes2d_In:
      staB = TopAbs_OUT;
      staA = staINON;
      break;

    case IntRes2d_Out:
      staB = staINON;
      staA = TopAbs_OUT;
      break;

    case IntRes2d_Touch:
      switch (T.Situation())
      {

        case IntRes2d_Inside:
          staB = staINON;
          staA = staINON;
          break;

        case IntRes2d_Outside:
          staB = TopAbs_OUT;
          staA = TopAbs_OUT;
          break;

        case IntRes2d_Unknown:
        {

          IntRes2d_Position posindex = (Index == 1) ? IP.TransitionOfFirst().PositionOnCurve()
                                                    : IP.TransitionOfSecond().PositionOnCurve();

          if (pointofsegment)
          {

            IntRes2d_Position posother = (Index == 1) ? IP.TransitionOfSecond().PositionOnCurve()
                                                      : IP.TransitionOfFirst().PositionOnCurve();

            if (posother == IntRes2d_Middle)
            {
              if (posindex != IntRes2d_Middle)
              {
                staB = staINON;
                staA = staINON;
              }
              else
                throw Standard_Failure("TopOpeBRep_EdgesIntersector : Situation Unknown MM");
            }
            else
            {
              bool opposite = IsOpposite1();
              if (opposite)
              {
                if (posother == IntRes2d_Head)
                {
                  staB = staINON;
                  staA = TopAbs_OUT;
                }
                else if (posother == IntRes2d_End)
                {
                  staB = TopAbs_OUT;
                  staA = staINON;
                }
              }
              else
              {
                if (posother == IntRes2d_Head)
                {
                  staB = TopAbs_OUT;
                  staA = staINON;
                }
                else if (posother == IntRes2d_End)
                {
                  staB = staINON;
                  staA = TopAbs_OUT;
                }
              }
            }
          }

          else
          {

            pextremity = true;
            shaA = shaB = TopAbs_EDGE;

            if (posindex == IntRes2d_Head)
            {
              staB = staINON;
              staA = TopAbs_OUT;
            }
            else if (posindex == IntRes2d_End)
            {
              staB = TopAbs_OUT;
              staA = staINON;
            }
            else
            {
              throw Standard_Failure("TopOpeBRep_EdgesIntersector : Situation Unknown M");
            }
          }
        }
        break;
      }
      break;

    case IntRes2d_Undecided:
      throw Standard_Failure("TopOpeBRep_EdgesIntersector : TransitionType Undecided");
      break;
  }

  TopOpeBRepDS_Transition TR;
  if (pur1d || pextremity)
  {
    TR.Set(staB, staA, shaB, shaA);
  }
  else
  {
    bool composori = false;
    composori      = composori || ((Index == 1) && (!myf2surf1F_sameoriented));
    composori      = composori || ((Index == 2) && (!myf1surf1F_sameoriented));

    TopAbs_Orientation eori = EdgeOrientation;
    if (composori)
    {
      eori = TopAbs::Reverse(eori);
    }

    TR.Set(staB, staA, shaB, shaA);
    if (eori == TopAbs_REVERSED)
    {
      TR = TR.Complement();
    }
  }
  return TR;
}

double TopOpeBRep_EdgesIntersector::Parameter1(const int Index) const
{
  if (Index == 1)
    return Point1().ParamOnFirst();
  else
    return Point1().ParamOnSecond();
}

bool TopOpeBRep_EdgesIntersector::IsVertex1(const int Index)
{

  if (myIsVertexPointIndex == myPointIndex && myIsVertexIndex == Index)
    return myIsVertexValue;

  myIsVertexValue = false;
  IntRes2d_Position pos;
  if (Index == 1)
    pos = Point1().TransitionOfFirst().PositionOnCurve();
  else
    pos = Point1().TransitionOfSecond().PositionOnCurve();

  if (pos == IntRes2d_Middle)
  {

    double             par = Parameter1(Index);
    const TopoDS_Edge* pE  = nullptr;
    pE                     = (Index == 1) ? &myEdge1 : &myEdge2;
    const TopoDS_Edge& E   = *pE;
    TopExp_Explorer    ex;
    for (ex.Init(E, TopAbs_VERTEX); ex.More(); ex.Next())
    {

      const TopoDS_Vertex& V = TopoDS::Vertex(ex.Current());
      if (V.Orientation() == TopAbs_INTERNAL)
      {
        double parV = BRep_Tool::Parameter(V, E, myFace1);
        if (std::abs(par - parV) <= Precision::PConfusion())
        {
          myIsVertexValue  = true;
          myIsVertexVertex = V;
          break;
        }
      }
    }
  }
  else
  {
    TopoDS_Vertex V1, V2;
    if (Index == 1)
      TopExp::Vertices(myEdge1, V1, V2);
    else
      TopExp::Vertices(myEdge2, V1, V2);
    if (pos == IntRes2d_Head && !V1.IsNull())
    {
      myIsVertexValue  = true;
      myIsVertexVertex = V1;
    }
    else if (pos == IntRes2d_End && !V2.IsNull())
    {
      myIsVertexValue  = true;
      myIsVertexVertex = V2;
    }
  }

  myIsVertexPointIndex = myPointIndex;
  myIsVertexIndex      = Index;

  return myIsVertexValue;
}

const TopoDS_Shape& TopOpeBRep_EdgesIntersector::Vertex1(const int Index)
{
  if (!IsVertex1(Index))
    throw Standard_Failure("TopOpeBRep_EdgesIntersector : Vertex1");
  return myIsVertexVertex;
}

gp_Pnt TopOpeBRep_EdgesIntersector::Value1() const
{
  gp_Pnt2d p2 = Point1().Value();
  gp_Pnt   p;
  if (Precision::IsInfinite(p2.X()) || Precision::IsInfinite(p2.Y()))
  {
    double inf = Precision::Infinite();
    p.SetCoord(inf, inf, inf);
  }
  else
    mySurface1->Surface().D0(p2.X(), p2.Y(), p);
  return p;
}
