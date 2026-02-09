#include <BRepCheck_Result.hpp>

#include <BRepCheck.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepCheck_Result, Standard_Transient)

BRepCheck_Result::BRepCheck_Result()
    : myMin(false),
      myBlind(false)
{
}

void BRepCheck_Result::Init(const TopoDS_Shape& S)
{
  myShape = S;
  myMin   = false;
  myBlind = false;
  myMap.Clear();
  Minimum();
}

void BRepCheck_Result::SetFailStatus(const TopoDS_Shape& S)
{
  std::unique_lock<std::mutex> aLock =
    myMutex ? std::unique_lock<std::mutex>(*myMutex) : std::unique_lock<std::mutex>();
  occ::handle<NCollection_Shared<NCollection_List<BRepCheck_Status>>> aList;
  if (!myMap.Find(S, aList))
  {
    aList = new NCollection_Shared<NCollection_List<BRepCheck_Status>>();
    myMap.Bind(S, aList);
  }

  BRepCheck::Add(*aList, BRepCheck_CheckFail);
}

void BRepCheck_Result::InitContextIterator()
{
  myIter.Initialize(myMap);

  if (myIter.Key().IsSame(myShape))
  {
    myIter.Next();
  }
}

void BRepCheck_Result::NextShapeInContext()
{
  myIter.Next();
  if (myIter.More() && myIter.Key().IsSame(myShape))
  {
    myIter.Next();
  }
}

void BRepCheck_Result::SetParallel(bool theIsParallel)
{
  if (theIsParallel && !myMutex)
  {
    myMutex = opencascade::make_unique<std::mutex>();
  }
}
