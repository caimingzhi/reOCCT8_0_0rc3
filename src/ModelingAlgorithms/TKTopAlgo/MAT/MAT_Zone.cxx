#include <MAT_Arc.hpp>
#include <MAT_Node.hpp>
#include <NCollection_Sequence.hpp>
#include <MAT_Zone.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MAT_Zone, Standard_Transient)

MAT_Zone::MAT_Zone()
    : limited(true)
{
}

MAT_Zone::MAT_Zone(const occ::handle<MAT_BasicElt>& aBasicElt)
{
  Perform(aBasicElt);
}

void MAT_Zone::Perform(const occ::handle<MAT_BasicElt>& aBasicElt)
{
  occ::handle<MAT_Node> NextNode, StartNode;
  occ::handle<MAT_Arc>  CurrentArc;

  limited = true;
  frontier.Clear();

  if (aBasicElt->EndArc().IsNull())
    return;

  CurrentArc = aBasicElt->EndArc();
  frontier.Append(CurrentArc);

  NextNode  = NodeForTurn(CurrentArc, aBasicElt, MAT_Left);
  StartNode = CurrentArc->TheOtherNode(NextNode);

  while (!NextNode->PendingNode() && (NextNode != StartNode))
  {
    CurrentArc = CurrentArc->Neighbour(NextNode, MAT_Left);
    frontier.Append(CurrentArc);
    NextNode = CurrentArc->TheOtherNode(NextNode);
  }

  if (NextNode->Infinite())
  {
    limited    = false;
    CurrentArc = aBasicElt->StartArc();
    frontier.Append(CurrentArc);

    NextNode = NodeForTurn(CurrentArc, aBasicElt, MAT_Right);

    while (!NextNode->Infinite())
    {
      CurrentArc = CurrentArc->Neighbour(NextNode, MAT_Right);
      frontier.Append(CurrentArc);
      NextNode = CurrentArc->TheOtherNode(NextNode);
    }
  }
}

int MAT_Zone::NumberOfArcs() const
{
  return frontier.Length();
}

occ::handle<MAT_Arc> MAT_Zone::ArcOnFrontier(const int Index) const
{
  return frontier.Value(Index);
}

bool MAT_Zone::NoEmptyZone() const
{
  return (!frontier.IsEmpty());
}

bool MAT_Zone::Limited() const
{
  return limited;
}

occ::handle<MAT_Node> MAT_Zone::NodeForTurn(const occ::handle<MAT_Arc>&      anArc,
                                            const occ::handle<MAT_BasicElt>& aBE,
                                            const MAT_Side                   aSide) const
{
  occ::handle<MAT_Arc>  NeighbourArc;
  occ::handle<MAT_Node> NodeSol;

  NodeSol      = anArc->FirstNode();
  NeighbourArc = anArc->Neighbour(NodeSol, aSide);
  if (NeighbourArc.IsNull())
  {
    NodeSol      = anArc->SecondNode();
    NeighbourArc = anArc->Neighbour(NodeSol, aSide);
  }
  if (NeighbourArc.IsNull())
  {
    return NodeSol;
  }
  if (NeighbourArc->FirstElement() == aBE)
  {
    return NodeSol;
  }
  else if (NeighbourArc->SecondElement() == aBE)
  {
    return NodeSol;
  }
  else
  {
    return anArc->TheOtherNode(NodeSol);
  }
}
