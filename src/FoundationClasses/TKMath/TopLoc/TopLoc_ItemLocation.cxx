#include <TopLoc_Datum3D.hpp>
#include <Standard_Dump.hpp>
#include <TopLoc_ItemLocation.hpp>
#include <TopLoc_Location.hpp>

//=================================================================================================

TopLoc_ItemLocation::TopLoc_ItemLocation(const occ::handle<TopLoc_Datum3D>& D, const int P)
    : myDatum(D),
      myPower(P),
      myTrsf(D->Transformation().Powered(P))
{
}

//=================================================================================================

void TopLoc_ItemLocation::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_CLASS_BEGIN(theOStream, TopLoc_ItemLocation)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myTrsf)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myDatum.get())

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myPower)
}
