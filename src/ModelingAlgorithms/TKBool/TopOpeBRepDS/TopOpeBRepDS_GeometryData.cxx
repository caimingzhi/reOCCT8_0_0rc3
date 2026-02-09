#include <TopOpeBRepDS_GeometryData.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>

TopOpeBRepDS_GeometryData::TopOpeBRepDS_GeometryData() = default;

TopOpeBRepDS_GeometryData::TopOpeBRepDS_GeometryData(const TopOpeBRepDS_GeometryData& Other)
{
  Assign(Other);
}

void TopOpeBRepDS_GeometryData::Assign(const TopOpeBRepDS_GeometryData& Other)
{
  myInterferences.Clear();

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator anIt(Other.myInterferences);
  for (; anIt.More(); anIt.Next())
  {
    myInterferences.Append(anIt.Value());
  }
}

const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& TopOpeBRepDS_GeometryData::
  Interferences() const
{
  return myInterferences;
}

NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& TopOpeBRepDS_GeometryData::
  ChangeInterferences()
{
  return myInterferences;
}

void TopOpeBRepDS_GeometryData::AddInterference(const occ::handle<TopOpeBRepDS_Interference>& I)
{
  myInterferences.Append(I);
}
