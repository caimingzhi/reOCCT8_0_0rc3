#include <TopOpeBRep_LineInter.hpp>
#include <TopOpeBRep_WPointInter.hpp>
#include <TopOpeBRep_WPointInterIterator.hpp>

//=================================================================================================

TopOpeBRep_WPointInterIterator::TopOpeBRep_WPointInterIterator()
    : myLineInter(nullptr),
      myWPointIndex(0),
      myWPointNb(0)
{
}

//=================================================================================================

TopOpeBRep_WPointInterIterator::TopOpeBRep_WPointInterIterator(const TopOpeBRep_LineInter& LI)
{
  Init(LI);
}

//=================================================================================================

void TopOpeBRep_WPointInterIterator::Init(const TopOpeBRep_LineInter& LI)
{
  myLineInter = (TopOpeBRep_LineInter*)&LI;
  Init();
}

//=================================================================================================

void TopOpeBRep_WPointInterIterator::Init()
{
  myWPointIndex = 1;
  myWPointNb    = myLineInter->NbWPoint();
}

//=================================================================================================

bool TopOpeBRep_WPointInterIterator::More() const
{
  return (myWPointIndex <= myWPointNb);
}

//=================================================================================================

void TopOpeBRep_WPointInterIterator::Next()
{
  myWPointIndex++;
}

//=================================================================================================

const TopOpeBRep_WPointInter& TopOpeBRep_WPointInterIterator::CurrentWP()
{
  if (!More())
    throw Standard_ProgramError("TopOpeBRep_WPointInterIterator::Current");
  const TopOpeBRep_WPointInter& WP = myLineInter->WPoint(myWPointIndex);
  return WP;
}

TopOpeBRep_PLineInter TopOpeBRep_WPointInterIterator::PLineInterDummy() const
{
  return myLineInter;
}
