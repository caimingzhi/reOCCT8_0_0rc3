#include <TDataStd_HDataMapOfStringInteger.hpp>

#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataStd_HDataMapOfStringInteger, Standard_Transient)

//=======================================================================
// function : TDataStd_HDataMapOfStringInteger
// purpose  : Constructor of empty map
//=======================================================================
TDataStd_HDataMapOfStringInteger::TDataStd_HDataMapOfStringInteger(const int NbBuckets)
{
  myMap.ReSize(NbBuckets);
}

//=======================================================================
// function : TDataStd_HDataMapOfStringInteger
// purpose  : Constructor from already existing map; performs copying
//=======================================================================
TDataStd_HDataMapOfStringInteger::TDataStd_HDataMapOfStringInteger(
  const NCollection_DataMap<TCollection_ExtendedString, int>& theOther)
{
  myMap.Assign(theOther);
}
