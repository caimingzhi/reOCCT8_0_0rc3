#include <HLRAlgo_Intersection.hpp>
#include <HLRBRep_AreaLimit.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(HLRBRep_AreaLimit, Standard_Transient)

HLRBRep_AreaLimit::HLRBRep_AreaLimit(const HLRAlgo_Intersection& V,
                                     const bool                  Boundary,
                                     const bool                  Interference,
                                     const TopAbs_State          StateBefore,
                                     const TopAbs_State          StateAfter,
                                     const TopAbs_State          EdgeBefore,
                                     const TopAbs_State          EdgeAfter)
    : myVertex(V),
      myBoundary(Boundary),
      myInterference(Interference),
      myStateBefore(StateBefore),
      myStateAfter(StateAfter),
      myEdgeBefore(EdgeBefore),
      myEdgeAfter(EdgeAfter)
{
}

void HLRBRep_AreaLimit::StateBefore(const TopAbs_State Stat)
{
  myStateBefore = Stat;
}

void HLRBRep_AreaLimit::StateAfter(const TopAbs_State Stat)
{
  myStateAfter = Stat;
}

void HLRBRep_AreaLimit::EdgeBefore(const TopAbs_State Stat)
{
  myEdgeBefore = Stat;
}

void HLRBRep_AreaLimit::EdgeAfter(const TopAbs_State Stat)
{
  myEdgeAfter = Stat;
}

void HLRBRep_AreaLimit::Previous(const occ::handle<HLRBRep_AreaLimit>& P)
{
  myPrevious = P;
}

void HLRBRep_AreaLimit::Next(const occ::handle<HLRBRep_AreaLimit>& N)
{
  myNext = N;
}

const HLRAlgo_Intersection& HLRBRep_AreaLimit::Vertex() const
{
  return myVertex;
}

bool HLRBRep_AreaLimit::IsBoundary() const
{
  return myBoundary;
}

bool HLRBRep_AreaLimit::IsInterference() const
{
  return myInterference;
}

TopAbs_State HLRBRep_AreaLimit::StateBefore() const
{
  return myStateBefore;
}

TopAbs_State HLRBRep_AreaLimit::StateAfter() const
{
  return myStateAfter;
}

TopAbs_State HLRBRep_AreaLimit::EdgeBefore() const
{
  return myEdgeBefore;
}

TopAbs_State HLRBRep_AreaLimit::EdgeAfter() const
{
  return myEdgeAfter;
}

occ::handle<HLRBRep_AreaLimit> HLRBRep_AreaLimit::Previous() const
{
  return myPrevious;
}

occ::handle<HLRBRep_AreaLimit> HLRBRep_AreaLimit::Next() const
{
  return myNext;
}

void HLRBRep_AreaLimit::Clear()
{
  myPrevious.Nullify();
  myNext.Nullify();
}
