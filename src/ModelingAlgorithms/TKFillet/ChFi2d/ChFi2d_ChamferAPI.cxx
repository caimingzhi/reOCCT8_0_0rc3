

#include <ChFi2d_ChamferAPI.hpp>

#include <gp_Pnt.hpp>
#include <GC_MakeLine.hpp>
#include <BRep_Tool.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS.hpp>

ChFi2d_ChamferAPI::ChFi2d_ChamferAPI()
    : myStart1(0.0),
      myEnd1(0.0),
      myStart2(0.0),
      myEnd2(0.0),
      myCommonStart1(false),
      myCommonStart2(false)
{
}

ChFi2d_ChamferAPI::ChFi2d_ChamferAPI(const TopoDS_Wire& theWire)
    : myStart1(0.0),
      myEnd1(0.0),
      myStart2(0.0),
      myEnd2(0.0),
      myCommonStart1(false),
      myCommonStart2(false)
{
  Init(theWire);
}

ChFi2d_ChamferAPI::ChFi2d_ChamferAPI(const TopoDS_Edge& theEdge1, const TopoDS_Edge& theEdge2)
    : myEdge1(theEdge1),
      myEdge2(theEdge2),
      myStart1(0.0),
      myEnd1(0.0),
      myStart2(0.0),
      myEnd2(0.0),
      myCommonStart1(false),
      myCommonStart2(false)
{
}

void ChFi2d_ChamferAPI::Init(const TopoDS_Wire& theWire)
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
  Init(E1, E2);
}

void ChFi2d_ChamferAPI::Init(const TopoDS_Edge& theEdge1, const TopoDS_Edge& theEdge2)
{
  myEdge1 = theEdge1;
  myEdge2 = theEdge2;
}

bool ChFi2d_ChamferAPI::Perform()
{
  myCurve1 = BRep_Tool::Curve(myEdge1, myStart1, myEnd1);
  myCurve2 = BRep_Tool::Curve(myEdge2, myStart2, myEnd2);

  if (myCurve1->Value(myStart1).IsEqual(myCurve2->Value(myEnd2), Precision::Confusion()))
  {
    myCommonStart1 = true;
    myCommonStart2 = false;
  }
  else
  {
    if (myCurve1->Value(myEnd1).IsEqual(myCurve2->Value(myStart2), Precision::Confusion()))
    {
      myCommonStart1 = false;
      myCommonStart2 = true;
    }
    else
    {
      if (myCurve1->Value(myEnd1).IsEqual(myCurve2->Value(myEnd2), Precision::Confusion()))
      {
        myCommonStart1 = false;
        myCommonStart2 = false;
      }
      else
      {
        myCommonStart1 = true;
        myCommonStart2 = true;
      }
    }
  }
  return true;
}

TopoDS_Edge ChFi2d_ChamferAPI::Result(TopoDS_Edge& theEdge1,
                                      TopoDS_Edge& theEdge2,
                                      const double theLength1,
                                      const double theLength2)
{
  TopoDS_Edge aResult;
  if (std::abs(myEnd1 - myStart1) < theLength1)
    return aResult;
  if (std::abs(myEnd2 - myStart2) < theLength2)
    return aResult;

  double aCommon1 = (myCommonStart1 ? myStart1 : myEnd1)
                    + (((myStart1 > myEnd1) ^ myCommonStart1) ? theLength1 : -theLength1);
  double aCommon2 = (myCommonStart2 ? myStart2 : myEnd2)
                    + (((myStart2 > myEnd2) ^ myCommonStart2) ? theLength2 : -theLength2);

  GC_MakeLine             aML(myCurve1->Value(aCommon1), myCurve2->Value(aCommon2));
  BRepBuilderAPI_MakeEdge aBuilder(aML.Value(),
                                   myCurve1->Value(aCommon1),
                                   myCurve2->Value(aCommon2));
  aResult = aBuilder.Edge();

  BRepBuilderAPI_MakeEdge aDivider1(myCurve1, aCommon1, (myCommonStart1 ? myEnd1 : myStart1));
  theEdge1 = aDivider1.Edge();

  BRepBuilderAPI_MakeEdge aDivider2(myCurve2, aCommon2, (myCommonStart2 ? myEnd2 : myStart2));
  theEdge2 = aDivider2.Edge();

  return aResult;
}
