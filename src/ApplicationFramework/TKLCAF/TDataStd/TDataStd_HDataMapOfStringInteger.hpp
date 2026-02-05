#pragma once

#include <Standard.hpp>

#include <TCollection_ExtendedString.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>

//! Extension of NCollection_DataMap<TCollection_ExtendedString, int> class
//! to be manipulated by handle.
class TDataStd_HDataMapOfStringInteger : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(TDataStd_HDataMapOfStringInteger, Standard_Transient)
public:
  Standard_EXPORT TDataStd_HDataMapOfStringInteger(const int NbBuckets = 1);

  Standard_EXPORT TDataStd_HDataMapOfStringInteger(
    const NCollection_DataMap<TCollection_ExtendedString, int>& theOther);

  const NCollection_DataMap<TCollection_ExtendedString, int>& Map() const { return myMap; }

  NCollection_DataMap<TCollection_ExtendedString, int>& ChangeMap() { return myMap; }

private:
  NCollection_DataMap<TCollection_ExtendedString, int> myMap;
};
