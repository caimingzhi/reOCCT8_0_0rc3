#include <TColStd_HPackedMapOfInteger.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TColStd_HPackedMapOfInteger, Standard_Transient)

TColStd_HPackedMapOfInteger::TColStd_HPackedMapOfInteger(const int NbBuckets)
{
  myMap.ReSize(NbBuckets);
}

TColStd_HPackedMapOfInteger::TColStd_HPackedMapOfInteger(const TColStd_PackedMapOfInteger& theOther)
{
  myMap.Assign(theOther);
}
