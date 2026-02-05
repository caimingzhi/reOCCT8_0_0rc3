#include <TopOpeBRepDS_GeometryData.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>

//=================================================================================================

TopOpeBRepDS_GeometryData::TopOpeBRepDS_GeometryData() = default;

// modified by NIZNHY-PKV Tue Oct 30 09:25:59 2001 f
//=================================================================================================

TopOpeBRepDS_GeometryData::TopOpeBRepDS_GeometryData(const TopOpeBRepDS_GeometryData& Other)
{
  Assign(Other);
}

//=================================================================================================

void TopOpeBRepDS_GeometryData::Assign(const TopOpeBRepDS_GeometryData& Other)
{
  myInterferences.Clear();

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator anIt(Other.myInterferences);
  for (; anIt.More(); anIt.Next())
  {
    myInterferences.Append(anIt.Value());
  }
}

// modified by NIZNHY-PKV Tue Oct 30 09:25:49 2001 t

//=================================================================================================

const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& TopOpeBRepDS_GeometryData::
  Interferences() const
{
  return myInterferences;
}

//=================================================================================================

NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& TopOpeBRepDS_GeometryData::
  ChangeInterferences()
{
  return myInterferences;
}

//=================================================================================================

void TopOpeBRepDS_GeometryData::AddInterference(const occ::handle<TopOpeBRepDS_Interference>& I)
{
  myInterferences.Append(I);
}
