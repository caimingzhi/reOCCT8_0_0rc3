#include <TDF_ChildIDIterator.hpp>
#include <TDF_ChildIterator.hpp>
#include <TDF_Label.hpp>
#include <TDF_LabelNode.hpp>

#define ChildIDIterator_FindNext                                                                   \
  {                                                                                                \
    while (myItr.More() && !myItr.Value().FindAttribute(myID, myAtt))                              \
      myItr.Next();                                                                                \
  }

TDF_ChildIDIterator::TDF_ChildIDIterator() = default;

TDF_ChildIDIterator::TDF_ChildIDIterator(const TDF_Label&     aLabel,
                                         const Standard_GUID& anID,
                                         const bool           allLevels)
    : myID(anID),
      myItr(aLabel, allLevels)
{
  ChildIDIterator_FindNext;
}

void TDF_ChildIDIterator::Initialize(const TDF_Label&     aLabel,
                                     const Standard_GUID& anID,
                                     const bool           allLevels)
{
  myID = anID;
  myItr.Initialize(aLabel, allLevels);
  myAtt.Nullify();
  ChildIDIterator_FindNext;
}

void TDF_ChildIDIterator::Next()
{
  myAtt.Nullify();
  if (myItr.More())
  {
    myItr.Next();
    ChildIDIterator_FindNext;
  }
}

void TDF_ChildIDIterator::NextBrother()
{
  myAtt.Nullify();
  if (myItr.More())
  {
    myItr.NextBrother();
    while (myItr.More() && !myItr.Value().FindAttribute(myID, myAtt))
      myItr.NextBrother();
  }
}
