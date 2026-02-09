#include <TDataStd_HDataMapOfStringByte.hpp>

#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataStd_HDataMapOfStringByte, Standard_Transient)

TDataStd_HDataMapOfStringByte::TDataStd_HDataMapOfStringByte(const int NbBuckets)
{
  myMap.ReSize(NbBuckets);
}

TDataStd_HDataMapOfStringByte::TDataStd_HDataMapOfStringByte(
  const NCollection_DataMap<TCollection_ExtendedString, uint8_t>& theOther)
{
  myMap.Assign(theOther);
}
