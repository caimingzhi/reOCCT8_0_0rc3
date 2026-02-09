#include <TDataStd_HDataMapOfStringString.hpp>

#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataStd_HDataMapOfStringString, Standard_Transient)

TDataStd_HDataMapOfStringString::TDataStd_HDataMapOfStringString(const int NbBuckets)
{
  myMap.ReSize(NbBuckets);
}

TDataStd_HDataMapOfStringString::TDataStd_HDataMapOfStringString(
  const NCollection_DataMap<TCollection_ExtendedString, TCollection_ExtendedString>& theOther)
{
  myMap.Assign(theOther);
}
