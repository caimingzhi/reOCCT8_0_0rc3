#pragma once


#include <Standard.hpp>

#include <TCollection_ExtendedString.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>

//! Extension of NCollection_DataMap<TCollection_ExtendedString, double> class
//! to be manipulated by handle.
class TDataStd_HDataMapOfStringReal : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(TDataStd_HDataMapOfStringReal, Standard_Transient)
public:
  Standard_EXPORT TDataStd_HDataMapOfStringReal(const int NbBuckets = 1);

  Standard_EXPORT TDataStd_HDataMapOfStringReal(
    const NCollection_DataMap<TCollection_ExtendedString, double>& theOther);

  const NCollection_DataMap<TCollection_ExtendedString, double>& Map() const { return myMap; }

  NCollection_DataMap<TCollection_ExtendedString, double>& ChangeMap() { return myMap; }

private:
  NCollection_DataMap<TCollection_ExtendedString, double> myMap;
};

