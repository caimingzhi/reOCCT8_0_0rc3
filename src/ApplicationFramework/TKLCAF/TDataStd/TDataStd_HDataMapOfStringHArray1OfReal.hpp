#pragma once


#include <Standard.hpp>

#include <TCollection_ExtendedString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>

//! Extension of NCollection_DataMap<TCollection_ExtendedString,
//! occ::handle<NCollection_HArray1<double>>> class to be manipulated by handle.
class TDataStd_HDataMapOfStringHArray1OfReal : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(TDataStd_HDataMapOfStringHArray1OfReal, Standard_Transient)
public:
  Standard_EXPORT TDataStd_HDataMapOfStringHArray1OfReal(const int NbBuckets = 1);

  Standard_EXPORT TDataStd_HDataMapOfStringHArray1OfReal(
    const NCollection_DataMap<TCollection_ExtendedString, occ::handle<NCollection_HArray1<double>>>&
      theOther);

  const NCollection_DataMap<TCollection_ExtendedString, occ::handle<NCollection_HArray1<double>>>&
    Map() const
  {
    return myMap;
  }

  NCollection_DataMap<TCollection_ExtendedString, occ::handle<NCollection_HArray1<double>>>&
    ChangeMap()
  {
    return myMap;
  }

private:
  NCollection_DataMap<TCollection_ExtendedString, occ::handle<NCollection_HArray1<double>>> myMap;
};

