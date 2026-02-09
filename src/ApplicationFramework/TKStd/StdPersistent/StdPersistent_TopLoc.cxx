

#include <StdPersistent_TopLoc.hpp>
#include <StdObjMgt_ReadData.hpp>
#include <StdObjMgt_WriteData.hpp>
#include <StdObject_gp_Trsfs.hpp>

void StdPersistent_TopLoc::Datum3D::Read(StdObjMgt_ReadData& theReadData)
{
  gp_Trsf aTrsf;
  theReadData >> aTrsf;
  myTransient = new TopLoc_Datum3D(aTrsf);
}

void StdPersistent_TopLoc::Datum3D::Write(StdObjMgt_WriteData& theWriteData) const
{
  theWriteData << myTransient->Transformation();
}

void StdPersistent_TopLoc::ItemLocation::Read(StdObjMgt_ReadData& theReadData)
{
  theReadData >> myDatum >> myPower >> myNext;
}

void StdPersistent_TopLoc::ItemLocation::Write(StdObjMgt_WriteData& theWriteData) const
{
  theWriteData << myDatum << myPower << myNext;
}

void StdPersistent_TopLoc::ItemLocation::PChildren(
  StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
{
  theChildren.Append(myDatum);
  myNext.PChildren(theChildren);
}

TopLoc_Location StdPersistent_TopLoc::ItemLocation::Import() const
{
  TopLoc_Location aNext = myNext.Import();
  if (myDatum)
    return aNext * TopLoc_Location(myDatum->Import()).Powered(myPower);
  else
    return aNext;
}

Handle(StdPersistent_TopLoc::ItemLocation) StdPersistent_TopLoc::Translate(
  const TopLoc_Location&                                                                   theLoc,
  NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>& theMap)
{
  occ::handle<ItemLocation> aPLoc = new ItemLocation;
  aPLoc->myDatum                  = Translate(theLoc.FirstDatum(), theMap);
  aPLoc->myPower                  = theLoc.FirstPower();
  aPLoc->myNext                   = StdObject_Location::Translate(theLoc.NextLocation(), theMap);
  return aPLoc;
}

Handle(StdPersistent_TopLoc::Datum3D) StdPersistent_TopLoc::Translate(
  const occ::handle<TopLoc_Datum3D>&                                                       theDatum,
  NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>& theMap)
{
  occ::handle<Datum3D> aPDatum;
  if (theMap.IsBound(theDatum))
  {
    aPDatum = occ::down_cast<Datum3D>(theMap.Find(theDatum));
  }
  else
  {
    aPDatum = new Datum3D;
    aPDatum->Transient(theDatum);
    theMap.Bind(theDatum, aPDatum);
  }
  return aPDatum;
}
