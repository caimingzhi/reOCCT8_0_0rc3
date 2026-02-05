#include <TopOpeBRepDS_DataStructure.hpp>
#include <TopOpeBRepDS_ShapeData.hpp>

//=================================================================================================

TopOpeBRepDS_ShapeData::TopOpeBRepDS_ShapeData()
    : mySameDomainRef(0),
      mySameDomainOri(TopOpeBRepDS_UNSHGEOMETRY),
      mySameDomainInd(0),
      myOrientation(TopAbs_FORWARD),
      myOrientationDef(false),
      myAncestorRank(0),
      myKeep(true)
{
}

//=================================================================================================

const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& TopOpeBRepDS_ShapeData::
  Interferences() const
{
  return myInterferences;
}

//=================================================================================================

NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& TopOpeBRepDS_ShapeData::
  ChangeInterferences()
{
  return myInterferences;
}

//=================================================================================================

bool TopOpeBRepDS_ShapeData::Keep() const
{
  return myKeep;
}

//=================================================================================================

void TopOpeBRepDS_ShapeData::ChangeKeep(const bool b)
{
  myKeep = b;
}
