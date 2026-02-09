#include <TObj_SequenceIterator.hpp>

#include <TObj_Object.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TObj_SequenceIterator, TObj_ObjectIterator)

TObj_SequenceIterator::TObj_SequenceIterator()
    : myIndex(1)
{
}

TObj_SequenceIterator::TObj_SequenceIterator(
  const occ::handle<NCollection_HSequence<occ::handle<TObj_Object>>>& theObjects,
  const occ::handle<Standard_Type>&                                   theType)
{
  myIndex   = 1;
  myType    = theType;
  myObjects = theObjects;
}

bool TObj_SequenceIterator::More() const
{
  const bool isMore = (!myObjects.IsNull() && (myIndex <= myObjects->Length() && myIndex > 0)
                       && !myObjects->Value(myIndex).IsNull());

  if (isMore && !myType.IsNull() && !myObjects->Value(myIndex)->IsKind(myType))
  {
    TObj_SequenceIterator* me = (TObj_SequenceIterator*)this;
    me->Next();
    return More();
  }

  return isMore;
}

void TObj_SequenceIterator::Next()
{
  myIndex++;
}

occ::handle<TObj_Object> TObj_SequenceIterator::Value() const
{
  return myObjects->Value(myIndex);
}
