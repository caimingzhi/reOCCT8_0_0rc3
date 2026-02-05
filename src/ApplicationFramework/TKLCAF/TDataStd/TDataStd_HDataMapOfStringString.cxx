#include <TDataStd_HDataMapOfStringString.hpp>

#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataStd_HDataMapOfStringString, Standard_Transient)

//=======================================================================
// function : TDataStd_HDataMapOfStringString
// purpose  : Constructor of empty map
//=======================================================================
TDataStd_HDataMapOfStringString::TDataStd_HDataMapOfStringString(const int NbBuckets)
{
  myMap.ReSize(NbBuckets);
}

//=======================================================================
// function : TDataStd_HDataMapOfStringString
// purpose  : Constructor from already existing map; performs copying
//=======================================================================
TDataStd_HDataMapOfStringString::TDataStd_HDataMapOfStringString(
  const NCollection_DataMap<TCollection_ExtendedString, TCollection_ExtendedString>& theOther)
{
  myMap.Assign(theOther);
}
