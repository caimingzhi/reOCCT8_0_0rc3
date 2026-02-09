

#include <StdObjMgt_WriteData.hpp>
#include <StdObjMgt_Persistent.hpp>

#include <Standard_GUID.hpp>

StdObjMgt_WriteData::StdObjMgt_WriteData(const occ::handle<Storage_BaseDriver>& theDriver)
    : myDriver(theDriver)
{
}

void StdObjMgt_WriteData::WritePersistentObject(
  const occ::handle<StdObjMgt_Persistent>& thePersistent)
{
  if (thePersistent)
  {
    myDriver->WritePersistentObjectHeader(thePersistent->RefNum(), thePersistent->TypeNum());
    myDriver->BeginWritePersistentObjectData();
    thePersistent->Write(*this);
    myDriver->EndWritePersistentObjectData();
  }
}

StdObjMgt_WriteData& StdObjMgt_WriteData::operator<<(
  const occ::handle<StdObjMgt_Persistent>& thePersistent)
{
  myDriver->PutReference(thePersistent ? thePersistent->RefNum() : 0);
  return *this;
}

StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const Standard_GUID& theGUID)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  const Standard_UUID anUUID = theGUID.ToUUID();

  int      a32b;
  char16_t a16b[3];
  char     a8b[6];

  a32b    = anUUID.Data1;
  a16b[0] = anUUID.Data2;
  a16b[1] = anUUID.Data3;
  a16b[2] = (anUUID.Data4[0] << 8) | (anUUID.Data4[1]);
  a8b[0]  = anUUID.Data4[2];
  a8b[1]  = anUUID.Data4[3];
  a8b[2]  = anUUID.Data4[4];
  a8b[3]  = anUUID.Data4[5];
  a8b[4]  = anUUID.Data4[6];
  a8b[5]  = anUUID.Data4[7];

  theWriteData << a32b << a16b[0] << a16b[1] << a16b[2];
  theWriteData << a8b[0] << a8b[1] << a8b[2] << a8b[3] << a8b[4] << a8b[5];

  return theWriteData;
}
