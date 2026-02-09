#include <TDataStd_HDataMapOfStringHArray1OfInteger.hpp>

#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataStd_HDataMapOfStringHArray1OfInteger, Standard_Transient)

TDataStd_HDataMapOfStringHArray1OfInteger::TDataStd_HDataMapOfStringHArray1OfInteger(
  const int NbBuckets)
{
  myMap.ReSize(NbBuckets);
}

TDataStd_HDataMapOfStringHArray1OfInteger::TDataStd_HDataMapOfStringHArray1OfInteger(
  const NCollection_DataMap<TCollection_ExtendedString, occ::handle<NCollection_HArray1<int>>>&
    theOther)
{
  myMap.Assign(theOther);
}
