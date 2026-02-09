#include <TDataStd_HDataMapOfStringHArray1OfReal.hpp>

#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataStd_HDataMapOfStringHArray1OfReal, Standard_Transient)

TDataStd_HDataMapOfStringHArray1OfReal::TDataStd_HDataMapOfStringHArray1OfReal(const int NbBuckets)
{
  myMap.ReSize(NbBuckets);
}

TDataStd_HDataMapOfStringHArray1OfReal::TDataStd_HDataMapOfStringHArray1OfReal(
  const NCollection_DataMap<TCollection_ExtendedString, occ::handle<NCollection_HArray1<double>>>&
    theOther)
{
  myMap.Assign(theOther);
}
