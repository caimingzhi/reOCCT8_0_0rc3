#include <ChFi2d_FilletAPI.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS.hpp>

ChFi2d_FilletAPI::ChFi2d_FilletAPI()
    : myIsAnalytical(false)
{
}

ChFi2d_FilletAPI::ChFi2d_FilletAPI(const TopoDS_Wire& theWire, const gp_Pln& thePlane)
    : myIsAnalytical(false)
{
  Init(theWire, thePlane);
}

ChFi2d_FilletAPI::ChFi2d_FilletAPI(const TopoDS_Edge& theEdge1,
                                   const TopoDS_Edge& theEdge2,
                                   const gp_Pln&      thePlane)
    : myIsAnalytical(false)
{
  Init(theEdge1, theEdge2, thePlane);
}

void ChFi2d_FilletAPI::Init(const TopoDS_Wire& theWire, const gp_Pln& thePlane)
{

  TopoDS_Edge     E1, E2;
  TopoDS_Iterator itr(theWire);
  for (; itr.More(); itr.Next())
  {
    if (E1.IsNull())
      E1 = TopoDS::Edge(itr.Value());
    else if (E2.IsNull())
      E2 = TopoDS::Edge(itr.Value());
    else
      break;
  }
  if (!E1.IsNull() && !E2.IsNull())
    myIsAnalytical = IsAnalytical(E1, E2);

  myIsAnalytical ? myAnaFilletAlgo.Init(theWire, thePlane) : myFilletAlgo.Init(theWire, thePlane);
}

void ChFi2d_FilletAPI::Init(const TopoDS_Edge& theEdge1,
                            const TopoDS_Edge& theEdge2,
                            const gp_Pln&      thePlane)
{

  myIsAnalytical = IsAnalytical(theEdge1, theEdge2);

  myIsAnalytical ? myAnaFilletAlgo.Init(theEdge1, theEdge2, thePlane)
                 : myFilletAlgo.Init(theEdge1, theEdge2, thePlane);
}

bool ChFi2d_FilletAPI::Perform(const double theRadius)
{
  return myIsAnalytical ? myAnaFilletAlgo.Perform(theRadius) : myFilletAlgo.Perform(theRadius);
}

int ChFi2d_FilletAPI::NbResults(const gp_Pnt& thePoint)
{
  return myIsAnalytical ? 1 : myFilletAlgo.NbResults(thePoint);
}

TopoDS_Edge ChFi2d_FilletAPI::Result(const gp_Pnt& thePoint,
                                     TopoDS_Edge&  theEdge1,
                                     TopoDS_Edge&  theEdge2,
                                     const int     iSolution)
{
  return myIsAnalytical ? myAnaFilletAlgo.Result(theEdge1, theEdge2)
                        : myFilletAlgo.Result(thePoint, theEdge1, theEdge2, iSolution);
}

bool ChFi2d_FilletAPI::IsAnalytical(const TopoDS_Edge& theEdge1, const TopoDS_Edge& theEdge2)
{
  bool              ret(false);
  BRepAdaptor_Curve AC1(theEdge1), AC2(theEdge2);
  if ((AC1.GetType() == GeomAbs_Line || AC1.GetType() == GeomAbs_Circle)
      && (AC2.GetType() == GeomAbs_Line || AC2.GetType() == GeomAbs_Circle))
  {

    gp_Pnt p11 = AC1.Value(AC1.FirstParameter());
    gp_Pnt p12 = AC1.Value(AC1.LastParameter());
    gp_Pnt p21 = AC2.Value(AC2.FirstParameter());
    gp_Pnt p22 = AC2.Value(AC2.LastParameter());
    if (p11.SquareDistance(p21) < Precision::SquareConfusion()
        || p11.SquareDistance(p22) < Precision::SquareConfusion()
        || p12.SquareDistance(p21) < Precision::SquareConfusion()
        || p12.SquareDistance(p22) < Precision::SquareConfusion())
    {
      ret = true;
    }
  }
  return ret;
}
