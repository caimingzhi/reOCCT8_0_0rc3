#include <TDataStd_HDataMapOfStringReal.hpp>

#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataStd_HDataMapOfStringReal, Standard_Transient)

//=======================================================================
// function : TDataStd_HDataMapOfStringReal
// purpose  : Constructor of empty map
//=======================================================================
TDataStd_HDataMapOfStringReal::TDataStd_HDataMapOfStringReal(const int NbBuckets)
{
  myMap.ReSize(NbBuckets);
}

//=======================================================================
// function : TDataStd_HDataMapOfStringReal
// purpose  : Constructor from already existing map; performs copying
//=======================================================================
TDataStd_HDataMapOfStringReal::TDataStd_HDataMapOfStringReal(
  const NCollection_DataMap<TCollection_ExtendedString, double>& theOther)
{
  myMap.Assign(theOther);
}
