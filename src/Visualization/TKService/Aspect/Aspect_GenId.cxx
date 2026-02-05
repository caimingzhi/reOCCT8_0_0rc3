#include <Aspect_GenId.hpp>
#include <Aspect_IdentDefinitionError.hpp>

#include <Standard_Dump.hpp>

//=================================================================================================

Aspect_GenId::Aspect_GenId()
    : myFreeCount(INT_MAX / 2 + 1),
      myLength(INT_MAX / 2 + 1),
      myLowerBound(0),
      myUpperBound(INT_MAX / 2)
{
}

//=================================================================================================

Aspect_GenId::Aspect_GenId(const int theLow, const int theUpper)
    : myFreeCount(theUpper - theLow + 1),
      myLength(theUpper - theLow + 1),
      myLowerBound(theLow),
      myUpperBound(theUpper)
{
  if (theLow > theUpper)
  {
    throw Aspect_IdentDefinitionError("GenId Create Error: wrong interval");
  }
}

//=================================================================================================

void Aspect_GenId::Free()
{
  myFreeCount = myLength;
  myFreeIds.Clear();
}

//=================================================================================================

void Aspect_GenId::Free(const int theId)
{
  if (theId >= myLowerBound && theId <= myUpperBound)
  {
    if (myFreeCount + myFreeIds.Extent() + 1 == myLength)
    {
      myFreeCount = myLength;
      myFreeIds.Clear();
    }
    else
    {
      myFreeIds.Prepend(theId);
    }
  }
}

//=================================================================================================

int Aspect_GenId::Next()
{
  int aNewId = 0;
  if (!Next(aNewId))
  {
    throw Aspect_IdentDefinitionError("Aspect_GenId::Next(), Error: Available == 0");
  }
  return aNewId;
}

//=================================================================================================

bool Aspect_GenId::Next(int& theId)
{
  if (!myFreeIds.IsEmpty())
  {
    theId = myFreeIds.First();
    myFreeIds.RemoveFirst();
    return true;
  }
  else if (myFreeCount < 1)
  {
    return false;
  }

  --myFreeCount;
  theId = myLowerBound + myLength - myFreeCount - 1;
  return true;
}

//=================================================================================================

void Aspect_GenId::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myFreeCount)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myLength)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myLowerBound)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myUpperBound)

  for (NCollection_List<int>::Iterator anIter(myFreeIds); anIter.More(); anIter.Next())
  {
    int aFreeId = anIter.Value();
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, aFreeId)
  }
}
