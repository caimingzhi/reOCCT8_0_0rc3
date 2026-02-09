#include <TopOpeBRepDS_Association.hpp>
#include <TopOpeBRepDS_Interference.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopOpeBRepDS_Association, Standard_Transient)

static bool Contains(const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
                     const occ::handle<TopOpeBRepDS_Interference>&                   I)
{
  for (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(LI); it.More();
       it.Next())
  {
    if (I->HasSameGeometry(it.Value()))
      return true;
  }
  return false;
}

TopOpeBRepDS_Association::TopOpeBRepDS_Association() = default;

void TopOpeBRepDS_Association::Associate(const occ::handle<TopOpeBRepDS_Interference>& I,
                                         const occ::handle<TopOpeBRepDS_Interference>& K)
{
  if (!myMap.IsBound(I))
  {
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> empty;
    myMap.Bind(I, empty);
    myMap(I).Append(K);
  }
  else if (!Contains(myMap(I), K))
  {
    myMap(I).Append(K);
  }
  if (!myMap.IsBound(K))
  {
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> empty;
    myMap.Bind(K, empty);
    myMap(K).Append(I);
  }
  else if (!Contains(myMap(K), I))
  {
    myMap(K).Append(I);
  }
}

void TopOpeBRepDS_Association::Associate(
  const occ::handle<TopOpeBRepDS_Interference>&                   I,
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI)
{
  for (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(LI); it.More();
       it.Next())
  {
    Associate(I, it.Value());
  }
}

bool TopOpeBRepDS_Association::HasAssociation(const occ::handle<TopOpeBRepDS_Interference>& I) const
{
  return myMap.IsBound(I);
}

NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& TopOpeBRepDS_Association::Associated(
  const occ::handle<TopOpeBRepDS_Interference>& I)
{
  if (myMap.IsBound(I))
  {
    return myMap.ChangeFind(I);
  }
  static NCollection_List<occ::handle<TopOpeBRepDS_Interference>> empty;
  return empty;
}

bool TopOpeBRepDS_Association::AreAssociated(const occ::handle<TopOpeBRepDS_Interference>& I,
                                             const occ::handle<TopOpeBRepDS_Interference>& K) const
{
  return (myMap.IsBound(I) && Contains(myMap(I), K));
}
