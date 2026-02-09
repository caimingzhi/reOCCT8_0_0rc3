#include <HatchGen_IntersectionPoint.hpp>

HatchGen_IntersectionPoint::HatchGen_IntersectionPoint()
    : myIndex(0),
      myParam(RealLast()),
      myPosit(TopAbs_INTERNAL),
      myBefore(TopAbs_UNKNOWN),
      myAfter(TopAbs_UNKNOWN),
      mySegBeg(false),
      mySegEnd(false)
{
}

void HatchGen_IntersectionPoint::SetIndex(const int Index)
{
  myIndex = Index;
}

int HatchGen_IntersectionPoint::Index() const
{
  return myIndex;
}

void HatchGen_IntersectionPoint::SetParameter(const double Parameter)
{
  myParam = Parameter;
}

double HatchGen_IntersectionPoint::Parameter() const
{
  return myParam;
}

void HatchGen_IntersectionPoint::SetPosition(const TopAbs_Orientation Position)
{
  myPosit = Position;
}

TopAbs_Orientation HatchGen_IntersectionPoint::Position() const
{
  return myPosit;
}

void HatchGen_IntersectionPoint::SetStateBefore(const TopAbs_State State)
{
  myBefore = State;
}

TopAbs_State HatchGen_IntersectionPoint::StateBefore() const
{
  return myBefore;
}

void HatchGen_IntersectionPoint::SetStateAfter(const TopAbs_State State)
{
  myAfter = State;
}

TopAbs_State HatchGen_IntersectionPoint::StateAfter() const
{
  return myAfter;
}

void HatchGen_IntersectionPoint::SetSegmentBeginning(const bool State)
{
  mySegBeg = State;
}

bool HatchGen_IntersectionPoint::SegmentBeginning() const
{
  return mySegBeg;
}

void HatchGen_IntersectionPoint::SetSegmentEnd(const bool State)
{
  mySegEnd = State;
}

bool HatchGen_IntersectionPoint::SegmentEnd() const
{
  return mySegEnd;
}
