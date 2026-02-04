#pragma once


#include <Standard_Type.hpp>

//! Stores and manipulates position in the stream.
class BinObjMgt_Position : public Standard_Transient
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates position using the current stream position.
  Standard_EXPORT BinObjMgt_Position(Standard_OStream& theStream);

  //! Stores the difference between the current position and the stored one.
  Standard_EXPORT void StoreSize(Standard_OStream& theStream);
  //! Writes stored size at the stored position. Changes the current stream position.
  //! If theDummy is true, is writes to the current position zero size.
  Standard_EXPORT void WriteSize(Standard_OStream& theStream, const bool theDummy = false);

  DEFINE_STANDARD_RTTIEXT(BinObjMgt_Position, Standard_Transient)

private:
  std::streampos myPosition;
  uint64_t       mySize;
};

