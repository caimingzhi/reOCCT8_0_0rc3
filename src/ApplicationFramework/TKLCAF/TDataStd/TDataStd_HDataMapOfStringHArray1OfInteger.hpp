#pragma once


#include <Standard.hpp>

#include <TCollection_ExtendedString.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>

//! Extension of NCollection_DataMap<TCollection_ExtendedString,
//! occ::handle<NCollection_HArray1<int>>> class to be manipulated by handle.
class TDataStd_HDataMapOfStringHArray1OfInteger : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(TDataStd_HDataMapOfStringHArray1OfInteger, Standard_Transient)
public:
  Standard_EXPORT TDataStd_HDataMapOfStringHArray1OfInteger(const int NbBuckets = 1);

  Standard_EXPORT TDataStd_HDataMapOfStringHArray1OfInteger(
    const NCollection_DataMap<TCollection_ExtendedString, occ::handle<NCollection_HArray1<int>>>&
      theOther);

  const NCollection_DataMap<TCollection_ExtendedString, occ::handle<NCollection_HArray1<int>>>&
    Map() const
  {
    return myMap;
  }

  NCollection_DataMap<TCollection_ExtendedString, occ::handle<NCollection_HArray1<int>>>&
    ChangeMap()
  {
    return myMap;
  }

private:
  NCollection_DataMap<TCollection_ExtendedString, occ::handle<NCollection_HArray1<int>>> myMap;
};

