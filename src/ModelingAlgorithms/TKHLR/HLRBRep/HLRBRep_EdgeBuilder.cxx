#ifndef No_Exception
  #define No_Exception
#endif

#include <HLRAlgo_Intersection.hpp>
#include <HLRBRep_AreaLimit.hpp>
#include <HLRBRep_EdgeBuilder.hpp>
#include <HLRBRep_VertexList.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_NoMoreObject.hpp>
#include <Standard_NoSuchObject.hpp>
#include <TopAbs.hpp>

HLRBRep_EdgeBuilder::HLRBRep_EdgeBuilder(HLRBRep_VertexList& VList)
{

  Standard_DomainError_Raise_if(!VList.More(), "EdgeBuilder  : Empty vertex list");

  occ::handle<HLRBRep_AreaLimit> last, cur;
  TopAbs_State                   before, after, ebefore, eafter;
  HLRAlgo_Intersection           V;

  for (; VList.More(); VList.Next())
  {
    before = after = ebefore = eafter = TopAbs_UNKNOWN;

    if (VList.IsBoundary())
    {
      switch (VList.Orientation())
      {

        case TopAbs_FORWARD:
          ebefore = TopAbs_OUT;
          eafter  = TopAbs_IN;
          break;

        case TopAbs_REVERSED:
          ebefore = TopAbs_IN;
          eafter  = TopAbs_OUT;
          break;

        case TopAbs_INTERNAL:
          ebefore = TopAbs_IN;
          eafter  = TopAbs_IN;
          break;

        case TopAbs_EXTERNAL:
          ebefore = TopAbs_OUT;
          eafter  = TopAbs_OUT;
          break;
      }
    }

    if (VList.IsInterference())
    {
      switch (VList.Transition())
      {

        case TopAbs_FORWARD:
          before = TopAbs_OUT;
          after  = TopAbs_IN;
          break;

        case TopAbs_REVERSED:
          before = TopAbs_IN;
          after  = TopAbs_OUT;
          break;

        case TopAbs_INTERNAL:
          before = TopAbs_IN;
          after  = TopAbs_IN;
          break;

        case TopAbs_EXTERNAL:
          before = TopAbs_OUT;
          after  = TopAbs_OUT;
          break;
      }

      switch (VList.BoundaryTransition())
      {

        case TopAbs_FORWARD:
          after = TopAbs_ON;
          break;

        case TopAbs_REVERSED:
          before = TopAbs_ON;
          break;

        case TopAbs_INTERNAL:
          before = TopAbs_ON;
          after  = TopAbs_ON;
          break;

        case TopAbs_EXTERNAL:
          break;
      }
    }

    V   = VList.Current();
    cur = new HLRBRep_AreaLimit(V,
                                VList.IsBoundary(),
                                VList.IsInterference(),
                                before,
                                after,
                                ebefore,
                                eafter);
    if (myLimits.IsNull())
    {
      myLimits = cur;
      last     = cur;
    }
    else
    {
      last->Next(cur);
      cur->Previous(last);
      last = cur;
    }
  }

  if (VList.IsPeriodic())
  {
    last->Next(myLimits);
    myLimits->Previous(last);
  }

  TopAbs_State stat  = TopAbs_UNKNOWN;
  TopAbs_State estat = TopAbs_UNKNOWN;

  cur = myLimits;
  while (!cur.IsNull())
  {
    if (stat == TopAbs_UNKNOWN)
    {
      stat = cur->StateBefore();
      if (stat == TopAbs_UNKNOWN)
      {
        stat = cur->StateAfter();
      }
    }
    if (estat == TopAbs_UNKNOWN)
    {
      estat = cur->EdgeBefore();
      if (estat == TopAbs_UNKNOWN)
      {
        estat = cur->EdgeAfter();
      }
    }
    cur = cur->Next();

    if (cur == myLimits)
      break;
  }

  Standard_DomainError_Raise_if(stat == TopAbs_UNKNOWN, "EdgeBuilder : No interferences");

  if (estat == TopAbs_UNKNOWN)
    estat = TopAbs_IN;

  cur = myLimits;
  while (!cur.IsNull())
  {
    if (cur->StateBefore() == TopAbs_UNKNOWN)
      cur->StateBefore(stat);
    else
      stat = cur->StateAfter();
    if (cur->StateAfter() == TopAbs_UNKNOWN)
      cur->StateAfter(stat);
    if (cur->EdgeBefore() == TopAbs_UNKNOWN)
      cur->EdgeBefore(estat);
    else
      estat = cur->EdgeAfter();
    if (cur->EdgeAfter() == TopAbs_UNKNOWN)
      cur->EdgeAfter(estat);

    cur = cur->Next();
    if (cur == myLimits)
      break;
  }

  Builds(TopAbs_IN);
}

void HLRBRep_EdgeBuilder::InitAreas()
{
  left  = myLimits->Previous();
  right = myLimits;
}

void HLRBRep_EdgeBuilder::NextArea()
{
  left = right;
  if (!right.IsNull())
    right = right->Next();
}

void HLRBRep_EdgeBuilder::PreviousArea()
{
  right = left;
  if (!left.IsNull())
    left = left->Previous();
}

bool HLRBRep_EdgeBuilder::HasArea() const
{
  if (left.IsNull())
    if (right.IsNull())
      return false;
  if (right == myLimits)
    return false;
  return true;
}

TopAbs_State HLRBRep_EdgeBuilder::AreaState() const
{
  TopAbs_State stat = TopAbs_UNKNOWN;
  if (!left.IsNull())
    stat = left->StateAfter();
  if (!right.IsNull())
    stat = right->StateBefore();
  return stat;
}

TopAbs_State HLRBRep_EdgeBuilder::AreaEdgeState() const
{
  TopAbs_State stat = TopAbs_UNKNOWN;
  if (!left.IsNull())
    stat = left->EdgeAfter();
  if (!right.IsNull())
    stat = right->EdgeBefore();
  return stat;
}

occ::handle<HLRBRep_AreaLimit> HLRBRep_EdgeBuilder::LeftLimit() const
{
  return left;
}

occ::handle<HLRBRep_AreaLimit> HLRBRep_EdgeBuilder::RightLimit() const
{
  return right;
}

void HLRBRep_EdgeBuilder::Builds(const TopAbs_State ToBuild)
{
  toBuild = ToBuild;
  InitAreas();
  do
  {
    if ((AreaState() == toBuild) && (AreaEdgeState() == TopAbs_IN))
    {
      if (left.IsNull())
        current = 2;
      else
        current = 1;
      return;
    }
    NextArea();
  } while (HasArea());
  current = 3;
}

bool HLRBRep_EdgeBuilder::MoreEdges() const
{
  return HasArea();
}

void HLRBRep_EdgeBuilder::NextEdge()
{

  while (AreaState() == toBuild)
    NextArea();

  while (HasArea())
  {
    if ((AreaState() == toBuild) && (AreaEdgeState() == TopAbs_IN))
    {
      if (left.IsNull())
        current = 2;
      else
        current = 1;
      return;
    }
    NextArea();
  }
}

bool HLRBRep_EdgeBuilder::MoreVertices() const
{
  return (current < 3);
}

void HLRBRep_EdgeBuilder::NextVertex()
{
  if (current == 1)
  {
    current = 2;
    if (right.IsNull())
      current = 3;
  }
  else if (current == 2)
  {
    NextArea();
    if ((AreaState() == toBuild) && (AreaEdgeState() == TopAbs_IN))
      current = 2;
    else
      current = 3;
  }
  else
    throw Standard_NoSuchObject("EdgeBuilder::NextVertex : No current edge");
}

const HLRAlgo_Intersection& HLRBRep_EdgeBuilder::Current() const
{
  if (current == 1)
    return left->Vertex();
  else if (current == 2)
    return right->Vertex();
  else
    throw Standard_NoSuchObject("EdgeBuilder::Current : No current vertex");
}

bool HLRBRep_EdgeBuilder::IsBoundary() const
{
  if (current == 1)
    return left->IsBoundary();
  else if (current == 2)
    return right->IsBoundary();
  else
    throw Standard_NoSuchObject("EdgeBuilder::IsBoundary : No current vertex");
}

bool HLRBRep_EdgeBuilder::IsInterference() const
{
  if (current == 1)
    return left->IsInterference();
  else if (current == 2)
    return right->IsInterference();
  else
    throw Standard_NoSuchObject("EdgeBuilder::IsInterference : No current vertex");
}

TopAbs_Orientation HLRBRep_EdgeBuilder::Orientation() const
{
  if (current == 1)
  {
    if ((left->StateBefore() == left->StateAfter()) && (left->EdgeBefore() == left->EdgeAfter()))
      return TopAbs_INTERNAL;
    else
      return TopAbs_FORWARD;
  }
  else if (current == 2)
  {
    if ((right->StateBefore() == right->StateAfter())
        && (right->EdgeBefore() == right->EdgeAfter()))
      return TopAbs_INTERNAL;
    else
      return TopAbs_REVERSED;
  }
  return TopAbs_EXTERNAL;
}

void HLRBRep_EdgeBuilder::Destroy()
{
  occ::handle<HLRBRep_AreaLimit> cur = myLimits;
  while (!cur.IsNull())
  {
    occ::handle<HLRBRep_AreaLimit> n = cur->Next();
    cur->Clear();
    cur = n;
  }
  left.Nullify();
  right.Nullify();
  myLimits.Nullify();
}
