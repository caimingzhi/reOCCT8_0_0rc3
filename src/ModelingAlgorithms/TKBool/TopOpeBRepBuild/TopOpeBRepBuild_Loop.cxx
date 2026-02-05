#include <TopOpeBRepBuild_Loop.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopOpeBRepBuild_Loop, Standard_Transient)

//=================================================================================================

TopOpeBRepBuild_Loop::TopOpeBRepBuild_Loop(const TopoDS_Shape& S)
    : myIsShape(true),
      myShape(S),
      myBlockIterator(0, 0)
{
}

//=================================================================================================

TopOpeBRepBuild_Loop::TopOpeBRepBuild_Loop(const TopOpeBRepBuild_BlockIterator& BI)
    : myIsShape(false),
      myBlockIterator(BI)
{
}

//=================================================================================================

bool TopOpeBRepBuild_Loop::IsShape() const
{
  return myIsShape;
}

//=================================================================================================

const TopoDS_Shape& TopOpeBRepBuild_Loop::Shape() const
{
  return myShape;
}

//=================================================================================================

const TopOpeBRepBuild_BlockIterator& TopOpeBRepBuild_Loop::BlockIterator() const
{
  return myBlockIterator;
}

//=================================================================================================

void TopOpeBRepBuild_Loop::Dump() const {}
