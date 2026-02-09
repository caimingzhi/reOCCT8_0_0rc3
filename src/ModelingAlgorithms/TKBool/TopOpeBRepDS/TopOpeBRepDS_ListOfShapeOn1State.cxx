#include <TopOpeBRepDS_ListOfShapeOn1State.hpp>

TopOpeBRepDS_ListOfShapeOn1State::TopOpeBRepDS_ListOfShapeOn1State()
    : mySplits(0)
{
}

const NCollection_List<TopoDS_Shape>& TopOpeBRepDS_ListOfShapeOn1State::ListOnState() const
{
  return myList;
}

NCollection_List<TopoDS_Shape>& TopOpeBRepDS_ListOfShapeOn1State::ChangeListOnState()
{
  return myList;
}

void TopOpeBRepDS_ListOfShapeOn1State::Clear()
{
  myList.Clear();
  mySplits = 0;
}

bool TopOpeBRepDS_ListOfShapeOn1State::IsSplit() const
{
  bool res = false;
  if (mySplits & 1)
    res = true;
  return res;
}

void TopOpeBRepDS_ListOfShapeOn1State::Split(const bool B)
{
  int mask = 1;
  if (B)
    mySplits |= mask;
  else
    mySplits &= ~mask;
}
