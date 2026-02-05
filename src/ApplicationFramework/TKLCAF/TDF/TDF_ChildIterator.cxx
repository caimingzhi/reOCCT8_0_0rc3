#include <TDF_ChildIterator.hpp>
#include <TDF_Label.hpp>
#include <TDF_LabelNode.hpp>

#define ChildIterator_UpToBrother                                                                  \
  {                                                                                                \
    while (myNode && (myNode->Depth() > myFirstLevel) && !myNode->Brother())                       \
      myNode = myNode->Father();                                                                   \
    if (myNode && (myNode->Depth() > myFirstLevel) && myNode->Father())                            \
      myNode = myNode->Brother();                                                                  \
    else                                                                                           \
      myNode = NULL;                                                                               \
  }

//=================================================================================================

TDF_ChildIterator::TDF_ChildIterator()
    : myNode(nullptr),
      myFirstLevel(0)
{
}

//=================================================================================================

TDF_ChildIterator::TDF_ChildIterator(const TDF_Label& aLabel, const bool allLevels)
    : myNode(aLabel.myLabelNode->FirstChild()),
      myFirstLevel(allLevels ? aLabel.Depth() : -1)
{
}

//=================================================================================================

void TDF_ChildIterator::Initialize(const TDF_Label& aLabel, const bool allLevels)
{
  myNode       = aLabel.myLabelNode->FirstChild();
  myFirstLevel = allLevels ? aLabel.Depth() : -1;
}

//=================================================================================================

void TDF_ChildIterator::Next()
{
  if (myFirstLevel == -1)
  {
    myNode = myNode->Brother();
  }
  else
  {
    if (myNode->FirstChild())
      myNode = myNode->FirstChild();
    else
      ChildIterator_UpToBrother;
  }
}

//=================================================================================================

void TDF_ChildIterator::NextBrother()
{
  if ((myFirstLevel == -1) || myNode->Brother())
    myNode = myNode->Brother();
  else
    ChildIterator_UpToBrother;
}
