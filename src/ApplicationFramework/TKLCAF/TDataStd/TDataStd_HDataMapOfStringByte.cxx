#include <TDataStd_HDataMapOfStringByte.hpp>

#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataStd_HDataMapOfStringByte, Standard_Transient)

//=======================================================================
// function : TDataStd_HDataMapOfStringByte
// purpose  : Constructor of empty map
//=======================================================================
TDataStd_HDataMapOfStringByte::TDataStd_HDataMapOfStringByte(const int NbBuckets)
{
  myMap.ReSize(NbBuckets);
}

//=======================================================================
// function : TDataStd_HDataMapOfStringByte
// purpose  : Constructor from already existing map; performs copying
//=======================================================================
TDataStd_HDataMapOfStringByte::TDataStd_HDataMapOfStringByte(
  const NCollection_DataMap<TCollection_ExtendedString, uint8_t>& theOther)
{
  myMap.Assign(theOther);
}
