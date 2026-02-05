#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Vertex.hpp>
#include <ChFiDS_Stripe.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Standard_Integer.hpp>
class TopoDS_Vertex;
class ChFiDS_Stripe;

//! encapsulation of IndexedDataMapOfVertexListOfStripe
class ChFiDS_StripeMap
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ChFiDS_StripeMap();

  Standard_EXPORT void Add(const TopoDS_Vertex& V, const occ::handle<ChFiDS_Stripe>& F);

  int Extent() const;

  Standard_EXPORT const NCollection_List<occ::handle<ChFiDS_Stripe>>& FindFromKey(
    const TopoDS_Vertex& V) const;

  const NCollection_List<occ::handle<ChFiDS_Stripe>>& operator()(const TopoDS_Vertex& V) const
  {
    return FindFromKey(V);
  }

  Standard_EXPORT const NCollection_List<occ::handle<ChFiDS_Stripe>>& FindFromIndex(
    const int I) const;

  const NCollection_List<occ::handle<ChFiDS_Stripe>>& operator()(const int I) const
  {
    return FindFromIndex(I);
  }

  const TopoDS_Vertex& FindKey(const int I) const;

  Standard_EXPORT void Clear();

private:
  NCollection_IndexedDataMap<TopoDS_Vertex,
                             NCollection_List<occ::handle<ChFiDS_Stripe>>,
                             TopTools_ShapeMapHasher>
    mymap;
};

inline int ChFiDS_StripeMap::Extent() const
{
  return mymap.Extent();
}

//=================================================================================================

inline const TopoDS_Vertex& ChFiDS_StripeMap::FindKey(const int I) const
{
  return mymap.FindKey(I);
}
