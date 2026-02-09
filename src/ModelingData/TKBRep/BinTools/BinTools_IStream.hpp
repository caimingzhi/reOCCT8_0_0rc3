#pragma once

#include <BinTools.hpp>
#include <BinTools_ObjectType.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopAbs_Orientation.hpp>
#include <gp_Pnt.hpp>

class BinTools_IStream
{
public:
  Standard_EXPORT BinTools_IStream(Standard_IStream& theStream);

  Standard_EXPORT BinTools_ObjectType ReadType();

  Standard_EXPORT const BinTools_ObjectType& LastType() { return myLastType; }

  Standard_EXPORT TopAbs_ShapeEnum ShapeType();

  Standard_EXPORT TopAbs_Orientation ShapeOrientation();

  Standard_EXPORT uint64_t Position() { return myPosition; }

  Standard_EXPORT void GoTo(const uint64_t& thePosition);

  Standard_EXPORT bool IsReference();

  Standard_EXPORT uint64_t ReadReference();

  Standard_EXPORT Standard_IStream& Stream() { return *myStream; }

  Standard_EXPORT void UpdatePosition() { myPosition = uint64_t(myStream->tellg()); }

  Standard_EXPORT operator bool() const;

  Standard_EXPORT double ReadReal()
  {
    double aValue;
    *this >> aValue;
    return aValue;
  }

  Standard_EXPORT BinTools_IStream& operator>>(double& theValue);

  Standard_EXPORT int ReadInteger()
  {
    int aValue;
    *this >> aValue;
    return aValue;
  }

  Standard_EXPORT BinTools_IStream& operator>>(int& theValue);

  Standard_EXPORT gp_Pnt ReadPnt()
  {
    gp_Pnt aValue;
    *this >> aValue;
    return aValue;
  }

  Standard_EXPORT BinTools_IStream& operator>>(gp_Pnt& theValue);

  Standard_EXPORT uint8_t ReadByte()
  {
    uint8_t aValue;
    *this >> aValue;
    return aValue;
  }

  Standard_EXPORT BinTools_IStream& operator>>(uint8_t& theValue);

  Standard_EXPORT bool ReadBool() { return ReadByte() != 0; }

  Standard_EXPORT BinTools_IStream& operator>>(bool& theValue)
  {
    theValue = ReadByte() != 0;
    return *this;
  }

  Standard_EXPORT float ReadShortReal()
  {
    float aValue;
    *this >> aValue;
    return aValue;
  }

  Standard_EXPORT BinTools_IStream& operator>>(float& theValue);

  Standard_EXPORT BinTools_IStream& operator>>(gp_Trsf& theValue);

  Standard_EXPORT void ReadBools(bool& theBool1, bool& theBool2, bool& theBool3);

  Standard_EXPORT void ReadBools(bool& theBool1,
                                 bool& theBool2,
                                 bool& theBool3,
                                 bool& theBool4,
                                 bool& theBool5,
                                 bool& theBool6,
                                 bool& theBool7);

private:
  Standard_IStream*   myStream;
  uint64_t            myPosition;
  BinTools_ObjectType myLastType;
};
