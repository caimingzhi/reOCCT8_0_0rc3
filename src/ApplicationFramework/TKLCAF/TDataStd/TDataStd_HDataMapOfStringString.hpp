#pragma once

#include <Standard.hpp>

#include <TCollection_ExtendedString.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>

class TDataStd_HDataMapOfStringString : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(TDataStd_HDataMapOfStringString, Standard_Transient)
public:
  Standard_EXPORT TDataStd_HDataMapOfStringString(const int NbBuckets = 1);

  Standard_EXPORT TDataStd_HDataMapOfStringString(
    const NCollection_DataMap<TCollection_ExtendedString, TCollection_ExtendedString>& theOther);

  const NCollection_DataMap<TCollection_ExtendedString, TCollection_ExtendedString>& Map() const
  {
    return myMap;
  }

  NCollection_DataMap<TCollection_ExtendedString, TCollection_ExtendedString>& ChangeMap()
  {
    return myMap;
  }

private:
  NCollection_DataMap<TCollection_ExtendedString, TCollection_ExtendedString> myMap;
};
