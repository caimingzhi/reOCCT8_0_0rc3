#include <HatchGen_IntersectionPoint.hpp>

//=================================================================================================

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

//=======================================================================
// Function : SetIndex
// Purpose  : Sets the index of the supporting curve.
//=======================================================================

void HatchGen_IntersectionPoint::SetIndex(const int Index)
{
  myIndex = Index;
}

//=======================================================================
// Function : Index
// Purpose  : Returns the index of the supporting curve.
//=======================================================================

int HatchGen_IntersectionPoint::Index() const
{
  return myIndex;
}

//=======================================================================
// Function : SetParameter
// Purpose  : Sets the parameter on the curve.
//=======================================================================

void HatchGen_IntersectionPoint::SetParameter(const double Parameter)
{
  myParam = Parameter;
}

//=======================================================================
// Function : Parameter
// Purpose  : Returns the parameter on the curve.
//=======================================================================

double HatchGen_IntersectionPoint::Parameter() const
{
  return myParam;
}

//=======================================================================
// Function : SetPosition
// Purpose  : Sets the position of the point on the curve.
//=======================================================================

void HatchGen_IntersectionPoint::SetPosition(const TopAbs_Orientation Position)
{
  myPosit = Position;
}

//=======================================================================
// Function : Position
// Purpose  : Returns the position of the point on the element.
//=======================================================================

TopAbs_Orientation HatchGen_IntersectionPoint::Position() const
{
  return myPosit;
}

//=======================================================================
// Function : SetStateBefore
// Purpose  : Sets the transition state before the intersection.
//=======================================================================

void HatchGen_IntersectionPoint::SetStateBefore(const TopAbs_State State)
{
  myBefore = State;
}

//=======================================================================
// Function : StateBefore
// Purpose  : Returns the transition state before the intersection.
//=======================================================================

TopAbs_State HatchGen_IntersectionPoint::StateBefore() const
{
  return myBefore;
}

//=======================================================================
// Function : SetStateAfter
// Purpose  : Sets the transition state after the intersection.
//=======================================================================

void HatchGen_IntersectionPoint::SetStateAfter(const TopAbs_State State)
{
  myAfter = State;
}

//=======================================================================
// Function : StateAfter
// Purpose  : Returns the transition state after the intersection.
//=======================================================================

TopAbs_State HatchGen_IntersectionPoint::StateAfter() const
{
  return myAfter;
}

//=======================================================================
// Function : SetSegmentBeginning
// Purpose  : Sets the flag that the point is the beginning of a segment.
//=======================================================================

void HatchGen_IntersectionPoint::SetSegmentBeginning(const bool State)
{
  mySegBeg = State;
}

//=======================================================================
// Function : SegmentBeginning
// Purpose  : Returns the flag that the point is the beginning of a
//            segment.
//=======================================================================

bool HatchGen_IntersectionPoint::SegmentBeginning() const
{
  return mySegBeg;
}

//=======================================================================
// Function : SetSegmentEnd
// Purpose  : Sets the flag that the point is the end of a segment.
//=======================================================================

void HatchGen_IntersectionPoint::SetSegmentEnd(const bool State)
{
  mySegEnd = State;
}

//=======================================================================
// Function : SegmentEnd
// Purpose  : Returns the flag that the point is the end of a segment.
//=======================================================================

bool HatchGen_IntersectionPoint::SegmentEnd() const
{
  return mySegEnd;
}
