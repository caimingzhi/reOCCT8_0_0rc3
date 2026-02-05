#include <TColStd_HPackedMapOfInteger.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TColStd_HPackedMapOfInteger, Standard_Transient)

//! Constructor of empty map
TColStd_HPackedMapOfInteger::TColStd_HPackedMapOfInteger(const int NbBuckets)
{
  myMap.ReSize(NbBuckets);
}

//! Constructor from already existing map; performs copying
TColStd_HPackedMapOfInteger::TColStd_HPackedMapOfInteger(const TColStd_PackedMapOfInteger& theOther)
{
  myMap.Assign(theOther);
}
