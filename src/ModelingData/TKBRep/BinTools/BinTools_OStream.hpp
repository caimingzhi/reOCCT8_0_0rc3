#pragma once


#include <BinTools.hpp>
#include <BinTools_ObjectType.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopAbs_Orientation.hpp>
#include <gp_Pnt.hpp>
#include <Poly_Triangle.hpp>
#include <NCollection_Vec3.hpp>

//! Substitution of OStream for shape writer for fast management of position in the file
//! and operation on all writing types.
class BinTools_OStream
{
public:
  //! Creates OStream using the current stream OStream.
  Standard_EXPORT BinTools_OStream(Standard_OStream& theStream);

  //! Returns the current position of the stream
  Standard_EXPORT const uint64_t& Position() { return myPosition; }

  //! Writes the reference to the given position (an offset between the current and the given one).
  Standard_EXPORT void WriteReference(const uint64_t& thePosition);
  //! Writes an identifier of shape type and orientation into the stream.
  Standard_EXPORT void WriteShape(const TopAbs_ShapeEnum&   theType,
                                  const TopAbs_Orientation& theOrientation);

  //! Writes an object type to the stream.
  Standard_EXPORT BinTools_OStream& operator<<(const BinTools_ObjectType& theType);
  //! Writes a byte to the stream.
  Standard_EXPORT BinTools_OStream& operator<<(const uint8_t& theValue);
  //! Writes a real to the stream.
  Standard_EXPORT BinTools_OStream& operator<<(const double& theValue);
  //! Writes a boolean to the stream.
  Standard_EXPORT BinTools_OStream& operator<<(const bool& theValue);
  //! Writes a integer to the stream.
  Standard_EXPORT BinTools_OStream& operator<<(const int& theValue);
  //! Writes a extended character to the stream.
  Standard_EXPORT BinTools_OStream& operator<<(const char16_t& theValue);
  //! Writes a 3D point to the stream.
  Standard_EXPORT BinTools_OStream& operator<<(const gp_Pnt& theValue);
  //! Writes a 3D direction to the stream.
  Standard_EXPORT BinTools_OStream& operator<<(const gp_Dir& theValue);
  //! Writes a 2D point to the stream.
  Standard_EXPORT BinTools_OStream& operator<<(const gp_Pnt2d& theValue);
  //! Writes a 2D direction to the stream.
  Standard_EXPORT BinTools_OStream& operator<<(const gp_Dir2d& theValue);
  //! Writes a transformation matrix to the stream.
  Standard_EXPORT BinTools_OStream& operator<<(const gp_Trsf& theValue);
  //! Writes triangle nodes indices to the stream.
  Standard_EXPORT BinTools_OStream& operator<<(const Poly_Triangle& theValue);
  //! Writes a vector to the stream.
  Standard_EXPORT BinTools_OStream& operator<<(const NCollection_Vec3<float>& theValue);

  //! Writes 3 booleans as one byte to the stream.
  Standard_EXPORT void PutBools(const bool theValue1, const bool theValue2, const bool theValue3);

  //! Writes 7 booleans as one byte to the stream.
  Standard_EXPORT void PutBools(const bool theValue1,
                                const bool theValue2,
                                const bool theValue3,
                                const bool theValue4,
                                const bool theValue5,
                                const bool theValue6,
                                const bool theValue7);

private:
  Standard_OStream* myStream; ///< pointer to the stream
                              // clang-format off
  uint64_t myPosition; ///< the current position relatively to the OStream position at the moment of creation of this class instance
                              // clang-format on
  double myRealBuf[12];       ///< buffer for 12 reals storage
  int    myIntBuf[3];         ///< buffer for 3 integers storage
  float  myFloatBuf[3];       ///< buffer for 3 floats storage
};

