#include <TDataStd_HDataMapOfStringInteger.hpp>

#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataStd_HDataMapOfStringInteger, Standard_Transient)

TDataStd_HDataMapOfStringInteger::TDataStd_HDataMapOfStringInteger(const int NbBuckets)
{
  myMap.ReSize(NbBuckets);
}

TDataStd_HDataMapOfStringInteger::TDataStd_HDataMapOfStringInteger(
  const NCollection_DataMap<TCollection_ExtendedString, int>& theOther)
{
  myMap.Assign(theOther);
}
