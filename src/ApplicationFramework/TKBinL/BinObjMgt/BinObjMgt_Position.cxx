

#include <BinObjMgt_Position.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinObjMgt_Position, Standard_Transient)

BinObjMgt_Position::BinObjMgt_Position(Standard_OStream& theStream)
    : myPosition(theStream.tellp()),
      mySize(0)
{
}

void BinObjMgt_Position::StoreSize(Standard_OStream& theStream)
{
  mySize = uint64_t(theStream.tellp() - myPosition);
}

void BinObjMgt_Position::WriteSize(Standard_OStream& theStream, const bool theDummy)
{
  if (!theDummy && theStream.tellp() != myPosition)
    theStream.seekp(myPosition);
  uint64_t aSize = theDummy ? 0 : mySize;
#if DO_INVERSE
  aSize = FSD_BinaryFile::InverseUint64(aSize);
#endif
  theStream.write((char*)&aSize, sizeof(uint64_t));
}
