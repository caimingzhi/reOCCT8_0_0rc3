#include <ChFiDS_StripeMap.hpp>
#include <TopoDS_Vertex.hpp>

ChFiDS_StripeMap::ChFiDS_StripeMap() = default;

void ChFiDS_StripeMap::Add(const TopoDS_Vertex& V, const occ::handle<ChFiDS_Stripe>& F)
{
  int Index = mymap.FindIndex(V);
  if (Index == 0)
  {
    NCollection_List<occ::handle<ChFiDS_Stripe>> Empty;
    Index = mymap.Add(V, Empty);
  }
  mymap(Index).Append(F);
}

const NCollection_List<occ::handle<ChFiDS_Stripe>>& ChFiDS_StripeMap::FindFromKey(
  const TopoDS_Vertex& V) const
{
  return mymap.FindFromKey(V);
}

const NCollection_List<occ::handle<ChFiDS_Stripe>>& ChFiDS_StripeMap::FindFromIndex(
  const int I) const
{
  return mymap.FindFromIndex(I);
}

void ChFiDS_StripeMap::Clear()
{
  mymap.Clear();
}
