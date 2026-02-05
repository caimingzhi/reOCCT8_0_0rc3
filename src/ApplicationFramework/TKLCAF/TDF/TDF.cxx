#include <TDF.hpp>

#include <Standard_GUID.hpp>
#include <TCollection_ExtendedString.hpp>
#include <NCollection_DoubleMap.hpp>

static NCollection_DoubleMap<Standard_GUID, TCollection_ExtendedString> guidprogidmap;

//=================================================================================================

const Standard_GUID& TDF::LowestID()
{
  static Standard_GUID lowestID("00000000-0000-0000-0000-000000000000");
  return lowestID;
}

//=================================================================================================

const Standard_GUID& TDF::UppestID()
{
  static Standard_GUID uppestID("ffffffff-ffff-ffff-ffff-ffffffffffff");
  return uppestID;
}

//=================================================================================================

void TDF::AddLinkGUIDToProgID(const Standard_GUID& ID, const TCollection_ExtendedString& ProgID)
{
  guidprogidmap.UnBind1(ID);
  guidprogidmap.UnBind2(ProgID);

  guidprogidmap.Bind(ID, ProgID);
}

//=================================================================================================

bool TDF::GUIDFromProgID(const TCollection_ExtendedString& ProgID, Standard_GUID& ID)
{
  if (guidprogidmap.IsBound2(ProgID))
  {
    ID = guidprogidmap.Find2(ProgID);
    return true;
  }
  return false;
}

//=================================================================================================

bool TDF::ProgIDFromGUID(const Standard_GUID& ID, TCollection_ExtendedString& ProgID)
{
  if (guidprogidmap.IsBound1(ID))
  {
    ProgID = guidprogidmap.Find1(ID);
    return true;
  }
  return false;
}
