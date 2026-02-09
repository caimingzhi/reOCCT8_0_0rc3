#include <TopOpeBRep_LineInter.hpp>
#include <TopOpeBRep_VPointInter.hpp>
#include <TopOpeBRep_VPointInterIterator.hpp>

TopOpeBRep_VPointInterIterator::TopOpeBRep_VPointInterIterator()
    : myLineInter(nullptr),
      myVPointIndex(0),
      myVPointNb(0),
      mycheckkeep(false)
{
}

TopOpeBRep_VPointInterIterator::TopOpeBRep_VPointInterIterator(const TopOpeBRep_LineInter& LI)
{
  Init(LI);
}

void TopOpeBRep_VPointInterIterator::Init(const TopOpeBRep_LineInter& LI, const bool checkkeep)
{
  myLineInter = (TopOpeBRep_LineInter*)&LI;
  mycheckkeep = checkkeep;
  Init();
}

void TopOpeBRep_VPointInterIterator::Init()
{
  myVPointIndex = 1;
  myVPointNb    = myLineInter->NbVPoint();
  if (mycheckkeep)
  {
    while (More())
    {
      const TopOpeBRep_VPointInter& VP = CurrentVP();
      if (VP.Keep())
        break;
      else
        myVPointIndex++;
    }
  }
}

bool TopOpeBRep_VPointInterIterator::More() const
{
  return (myVPointIndex <= myVPointNb);
}

void TopOpeBRep_VPointInterIterator::Next()
{
  myVPointIndex++;
  if (mycheckkeep)
  {
    while (More())
    {
      const TopOpeBRep_VPointInter& VP = CurrentVP();
      if (VP.Keep())
        break;
      else
        myVPointIndex++;
    }
  }
}

const TopOpeBRep_VPointInter& TopOpeBRep_VPointInterIterator::CurrentVP()
{
  if (!More())
    throw Standard_ProgramError("TopOpeBRep_VPointInterIterator::CurrentVP");
  const TopOpeBRep_VPointInter& VP = myLineInter->VPoint(myVPointIndex);
  return VP;
}

TopOpeBRep_VPointInter& TopOpeBRep_VPointInterIterator::ChangeCurrentVP()
{
  if (!More())
    throw Standard_ProgramError("TopOpeBRep_VPointInterIterator::ChangeCurrentVP");
  TopOpeBRep_VPointInter& VP = myLineInter->ChangeVPoint(myVPointIndex);
  return VP;
}

int TopOpeBRep_VPointInterIterator::CurrentVPIndex() const
{
  if (!More())
    throw Standard_ProgramError("TopOpeBRep_VPointInterIterator::CurrentVPIndex");
  return myVPointIndex;
}

TopOpeBRep_PLineInter TopOpeBRep_VPointInterIterator::PLineInterDummy() const
{
  return myLineInter;
}
