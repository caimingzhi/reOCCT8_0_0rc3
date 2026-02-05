#pragma once

#include <Standard.hpp>

#include <TCollection_ExtendedString.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>

//! Extension of NCollection_DataMap<TCollection_ExtendedString, uint8_t> class
//! to be manipulated by handle.
class TDataStd_HDataMapOfStringByte : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(TDataStd_HDataMapOfStringByte, Standard_Transient)
public:
  Standard_EXPORT TDataStd_HDataMapOfStringByte(const int NbBuckets = 1);

  Standard_EXPORT TDataStd_HDataMapOfStringByte(
    const NCollection_DataMap<TCollection_ExtendedString, uint8_t>& theOther);

  const NCollection_DataMap<TCollection_ExtendedString, uint8_t>& Map() const { return myMap; }

  NCollection_DataMap<TCollection_ExtendedString, uint8_t>& ChangeMap() { return myMap; }

private:
  NCollection_DataMap<TCollection_ExtendedString, uint8_t> myMap;
};
