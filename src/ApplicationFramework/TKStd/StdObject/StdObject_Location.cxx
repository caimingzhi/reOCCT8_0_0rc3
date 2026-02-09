

#include <StdObject_Location.hpp>
#include <StdPersistent_TopLoc.hpp>

StdObject_Location StdObject_Location::Translate(
  const TopLoc_Location&                                                                   theLoc,
  NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>& theMap)
{
  StdObject_Location aLoc;
  if (!theLoc.IsIdentity())
    aLoc.myData = StdPersistent_TopLoc::Translate(theLoc, theMap);
  return aLoc;
}

void StdObject_Location::PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
{
  theChildren.Append(myData);
}

TopLoc_Location StdObject_Location::Import() const
{
  Handle(StdPersistent_TopLoc::ItemLocation) anItemLocation =
    Handle(StdPersistent_TopLoc::ItemLocation)::DownCast(myData);
  return anItemLocation ? anItemLocation->Import() : TopLoc_Location();
}
