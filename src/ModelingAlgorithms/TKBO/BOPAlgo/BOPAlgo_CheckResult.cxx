#include <BOPAlgo_CheckResult.hpp>
#include <TopoDS_Shape.hpp>

BOPAlgo_CheckResult::BOPAlgo_CheckResult()
    : myStatus(BOPAlgo_CheckUnknown),
      myMaxDist1(0.),
      myMaxDist2(0.),
      myMaxPar1(0.),
      myMaxPar2(0.)
{
}

void BOPAlgo_CheckResult::SetShape1(const TopoDS_Shape& TheShape)
{
  myShape1 = TheShape;
}

void BOPAlgo_CheckResult::AddFaultyShape1(const TopoDS_Shape& TheShape)
{
  myFaulty1.Append(TheShape);
}

void BOPAlgo_CheckResult::SetShape2(const TopoDS_Shape& TheShape)
{
  myShape2 = TheShape;
}

void BOPAlgo_CheckResult::AddFaultyShape2(const TopoDS_Shape& TheShape)
{
  myFaulty2.Append(TheShape);
}

const TopoDS_Shape& BOPAlgo_CheckResult::GetShape1() const
{
  return myShape1;
}

const TopoDS_Shape& BOPAlgo_CheckResult::GetShape2() const
{
  return myShape2;
}

const NCollection_List<TopoDS_Shape>& BOPAlgo_CheckResult::GetFaultyShapes1() const
{
  return myFaulty1;
}

const NCollection_List<TopoDS_Shape>& BOPAlgo_CheckResult::GetFaultyShapes2() const
{
  return myFaulty2;
}

void BOPAlgo_CheckResult::SetCheckStatus(const BOPAlgo_CheckStatus TheStatus)
{
  myStatus = TheStatus;
}

BOPAlgo_CheckStatus BOPAlgo_CheckResult::GetCheckStatus() const
{
  return myStatus;
}

void BOPAlgo_CheckResult::SetMaxDistance1(const double theDist)
{
  myMaxDist1 = theDist;
}

void BOPAlgo_CheckResult::SetMaxDistance2(const double theDist)
{
  myMaxDist2 = theDist;
}

void BOPAlgo_CheckResult::SetMaxParameter1(const double thePar)
{
  myMaxPar1 = thePar;
}

void BOPAlgo_CheckResult::SetMaxParameter2(const double thePar)
{
  myMaxPar2 = thePar;
}

double BOPAlgo_CheckResult::GetMaxDistance1() const
{
  return myMaxDist1;
}

double BOPAlgo_CheckResult::GetMaxDistance2() const
{
  return myMaxDist2;
}

double BOPAlgo_CheckResult::GetMaxParameter1() const
{
  return myMaxPar1;
}

double BOPAlgo_CheckResult::GetMaxParameter2() const
{
  return myMaxPar2;
}
