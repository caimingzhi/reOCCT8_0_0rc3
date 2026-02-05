#pragma once

#include <Standard.hpp>

#include <Standard_Type.hpp>
#include <TColStd_PackedMapOfInteger.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>

//! Extension of TColStd_PackedMapOfInteger class to be manipulated by handle.
class TColStd_HPackedMapOfInteger : public Standard_Transient
{

public:
  Standard_EXPORT TColStd_HPackedMapOfInteger(const int NbBuckets = 1);

  Standard_EXPORT TColStd_HPackedMapOfInteger(const TColStd_PackedMapOfInteger& theOther);

  const TColStd_PackedMapOfInteger& Map() const;

  TColStd_PackedMapOfInteger& ChangeMap();

  DEFINE_STANDARD_RTTIEXT(TColStd_HPackedMapOfInteger, Standard_Transient)

private:
  TColStd_PackedMapOfInteger myMap;
};

inline const TColStd_PackedMapOfInteger& TColStd_HPackedMapOfInteger::Map() const
{
  return myMap;
}

//! Access to the map for modification
inline TColStd_PackedMapOfInteger& TColStd_HPackedMapOfInteger::ChangeMap()
{
  return myMap;
}
