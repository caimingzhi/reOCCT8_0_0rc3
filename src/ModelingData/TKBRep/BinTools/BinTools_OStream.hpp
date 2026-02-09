#pragma once

#include <BinTools.hpp>
#include <BinTools_ObjectType.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopAbs_Orientation.hpp>
#include <gp_Pnt.hpp>
#include <Poly_Triangle.hpp>
#include <NCollection_Vec3.hpp>

class BinTools_OStream
{
public:
  Standard_EXPORT BinTools_OStream(Standard_OStream& theStream);

  Standard_EXPORT const uint64_t& Position() { return myPosition; }

  Standard_EXPORT void WriteReference(const uint64_t& thePosition);

  Standard_EXPORT void WriteShape(const TopAbs_ShapeEnum&   theType,
                                  const TopAbs_Orientation& theOrientation);

  Standard_EXPORT BinTools_OStream& operator<<(const BinTools_ObjectType& theType);

  Standard_EXPORT BinTools_OStream& operator<<(const uint8_t& theValue);

  Standard_EXPORT BinTools_OStream& operator<<(const double& theValue);

  Standard_EXPORT BinTools_OStream& operator<<(const bool& theValue);

  Standard_EXPORT BinTools_OStream& operator<<(const int& theValue);

  Standard_EXPORT BinTools_OStream& operator<<(const char16_t& theValue);

  Standard_EXPORT BinTools_OStream& operator<<(const gp_Pnt& theValue);

  Standard_EXPORT BinTools_OStream& operator<<(const gp_Dir& theValue);

  Standard_EXPORT BinTools_OStream& operator<<(const gp_Pnt2d& theValue);

  Standard_EXPORT BinTools_OStream& operator<<(const gp_Dir2d& theValue);

  Standard_EXPORT BinTools_OStream& operator<<(const gp_Trsf& theValue);

  Standard_EXPORT BinTools_OStream& operator<<(const Poly_Triangle& theValue);

  Standard_EXPORT BinTools_OStream& operator<<(const NCollection_Vec3<float>& theValue);

  Standard_EXPORT void PutBools(const bool theValue1, const bool theValue2, const bool theValue3);

  Standard_EXPORT void PutBools(const bool theValue1,
                                const bool theValue2,
                                const bool theValue3,
                                const bool theValue4,
                                const bool theValue5,
                                const bool theValue6,
                                const bool theValue7);

private:
  Standard_OStream* myStream;

  uint64_t myPosition;

  double myRealBuf[12];
  int    myIntBuf[3];
  float  myFloatBuf[3];
};
