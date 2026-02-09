#include <TDataStd_HDataMapOfStringReal.hpp>

#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataStd_HDataMapOfStringReal, Standard_Transient)

TDataStd_HDataMapOfStringReal::TDataStd_HDataMapOfStringReal(const int NbBuckets)
{
  myMap.ReSize(NbBuckets);
}

TDataStd_HDataMapOfStringReal::TDataStd_HDataMapOfStringReal(
  const NCollection_DataMap<TCollection_ExtendedString, double>& theOther)
{
  myMap.Assign(theOther);
}
