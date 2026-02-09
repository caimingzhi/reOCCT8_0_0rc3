

#include <StdObjMgt_ReadData.hpp>
#include <StdObjMgt_Persistent.hpp>

#include <Standard_GUID.hpp>

StdObjMgt_ReadData::StdObjMgt_ReadData(const occ::handle<Storage_BaseDriver>& theDriver,
                                       const int                              theNumberOfObjects)
    : myDriver(theDriver),
      myPersistentObjects(1, theNumberOfObjects)
{
}

void StdObjMgt_ReadData::ReadPersistentObject(const int theRef)
{
  occ::handle<StdObjMgt_Persistent> aPersistent = myPersistentObjects(theRef);
  if (aPersistent)
  {
    int aRef, aType;
    myDriver->ReadPersistentObjectHeader(aRef, aType);
    myDriver->BeginReadPersistentObjectData();
    aPersistent->Read(*this);
    myDriver->EndReadPersistentObjectData();
  }
}

occ::handle<StdObjMgt_Persistent> StdObjMgt_ReadData::ReadReference()
{
  int aRef;
  myDriver->GetReference(aRef);
  return aRef ? PersistentObject(aRef) : nullptr;
}

StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, Standard_GUID& theGUID)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);

  int      a32b;
  char16_t a16b[3];
  char     a8b[6];

  theReadData >> a32b >> a16b[0] >> a16b[1] >> a16b[2];
  theReadData >> a8b[0] >> a8b[1] >> a8b[2] >> a8b[3] >> a8b[4] >> a8b[5];

  theGUID =
    Standard_GUID(a32b, a16b[0], a16b[1], a16b[2], a8b[0], a8b[1], a8b[2], a8b[3], a8b[4], a8b[5]);

  return theReadData;
}
