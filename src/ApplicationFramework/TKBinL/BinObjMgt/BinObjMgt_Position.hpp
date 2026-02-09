#pragma once

#include <Standard_Type.hpp>

class BinObjMgt_Position : public Standard_Transient
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BinObjMgt_Position(Standard_OStream& theStream);

  Standard_EXPORT void StoreSize(Standard_OStream& theStream);

  Standard_EXPORT void WriteSize(Standard_OStream& theStream, const bool theDummy = false);

  DEFINE_STANDARD_RTTIEXT(BinObjMgt_Position, Standard_Transient)

private:
  std::streampos myPosition;
  uint64_t       mySize;
};
