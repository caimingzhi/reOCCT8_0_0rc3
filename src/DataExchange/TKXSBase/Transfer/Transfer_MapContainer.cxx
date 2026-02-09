

#include <Standard_Type.hpp>
#include <Transfer_MapContainer.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Transfer_MapContainer, Standard_Transient)

Transfer_MapContainer::Transfer_MapContainer() = default;

void Transfer_MapContainer::SetMapObjects(
  NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>&
    theMapObjects)
{
  myMapObj = theMapObjects;
}

NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>&
  Transfer_MapContainer::GetMapObjects()
{
  return myMapObj;
}
