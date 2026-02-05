#include <Interface_FileParameter.hpp>
#include <Interface_ParamList.hpp>
#include <Standard_OutOfMemory.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Interface_ParamList, Standard_Transient)

//=================================================================================================

Interface_ParamList::Interface_ParamList(const int theIncrement)
    : myVector(theIncrement)
{
}

//=================================================================================================

void Interface_ParamList::SetValue(const int theIndex, const Interface_FileParameter& theValue)
{
  int ind = theIndex - 1;
  myVector.SetValue(ind, theValue);
}

//=================================================================================================

const Interface_FileParameter& Interface_ParamList::Value(const int theIndex) const
{
  int ind = theIndex - 1;
  return myVector.Value(ind);
}

//=================================================================================================

Interface_FileParameter& Interface_ParamList::ChangeValue(const int theIndex)
{
  int ind = theIndex - 1;
  if (ind >= myVector.Length())
  {
    Interface_FileParameter aFP;
    myVector.SetValue(ind, aFP);
  }
  return myVector.ChangeValue(ind);
}

void Interface_ParamList::Clear()
{
  myVector.Clear();
}
