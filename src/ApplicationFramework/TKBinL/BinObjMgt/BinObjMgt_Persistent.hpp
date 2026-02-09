#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <Standard_ShortReal.hpp>

#include <Standard_TypeDef.hpp>

typedef char* BinObjMgt_PChar;

#include <Standard_TypeDef.hpp>

typedef uint8_t* BinObjMgt_PByte;

#include <Standard_TypeDef.hpp>

typedef char16_t* BinObjMgt_PExtChar;

#include <Standard_TypeDef.hpp>

typedef int* BinObjMgt_PInteger;

#include <Standard_TypeDef.hpp>

typedef double* BinObjMgt_PReal;

#include <Standard_TypeDef.hpp>

typedef float* BinObjMgt_PShortReal;

#include <BinObjMgt_Position.hpp>
#include <Standard_OStream.hpp>
#include <Standard_IStream.hpp>
class TCollection_AsciiString;
class TCollection_ExtendedString;
class TDF_Label;
class Standard_GUID;
class TDF_Data;

class BinObjMgt_Persistent
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BinObjMgt_Persistent();

  Standard_EXPORT BinObjMgt_Persistent& PutCharacter(const char theValue);

  BinObjMgt_Persistent& operator<<(const char theValue) { return PutCharacter(theValue); }

  Standard_EXPORT BinObjMgt_Persistent& PutByte(const uint8_t theValue);

  BinObjMgt_Persistent& operator<<(const uint8_t theValue) { return PutByte(theValue); }

  Standard_EXPORT BinObjMgt_Persistent& PutExtCharacter(const char16_t theValue);

  BinObjMgt_Persistent& operator<<(const char16_t theValue) { return PutExtCharacter(theValue); }

  Standard_EXPORT BinObjMgt_Persistent& PutInteger(const int theValue);

  BinObjMgt_Persistent& operator<<(const int theValue) { return PutInteger(theValue); }

  BinObjMgt_Persistent& PutBoolean(const bool theValue);

  BinObjMgt_Persistent& operator<<(const bool theValue) { return PutBoolean(theValue); }

  Standard_EXPORT BinObjMgt_Persistent& PutReal(const double theValue);

  BinObjMgt_Persistent& operator<<(const double theValue) { return PutReal(theValue); }

  Standard_EXPORT BinObjMgt_Persistent& PutShortReal(const float theValue);

  BinObjMgt_Persistent& operator<<(const float theValue) { return PutShortReal(theValue); }

  Standard_EXPORT BinObjMgt_Persistent& PutCString(const char* theValue);

  BinObjMgt_Persistent& operator<<(const char* theValue) { return PutCString(theValue); }

  Standard_EXPORT BinObjMgt_Persistent& PutAsciiString(const TCollection_AsciiString& theValue);

  BinObjMgt_Persistent& operator<<(const TCollection_AsciiString& theValue)
  {
    return PutAsciiString(theValue);
  }

  Standard_EXPORT BinObjMgt_Persistent& PutExtendedString(
    const TCollection_ExtendedString& theValue);

  BinObjMgt_Persistent& operator<<(const TCollection_ExtendedString& theValue)
  {
    return PutExtendedString(theValue);
  }

  Standard_EXPORT BinObjMgt_Persistent& PutLabel(const TDF_Label& theValue);

  BinObjMgt_Persistent& operator<<(const TDF_Label& theValue) { return PutLabel(theValue); }

  Standard_EXPORT BinObjMgt_Persistent& PutGUID(const Standard_GUID& theValue);

  BinObjMgt_Persistent& operator<<(const Standard_GUID& theValue) { return PutGUID(theValue); }

  Standard_EXPORT BinObjMgt_Persistent& PutCharArray(const BinObjMgt_PChar theArray,
                                                     const int             theLength);

  Standard_EXPORT BinObjMgt_Persistent& PutByteArray(const BinObjMgt_PByte theArray,
                                                     const int             theLength);

  Standard_EXPORT BinObjMgt_Persistent& PutExtCharArray(const BinObjMgt_PExtChar theArray,
                                                        const int                theLength);

  Standard_EXPORT BinObjMgt_Persistent& PutIntArray(const BinObjMgt_PInteger theArray,
                                                    const int                theLength);

  Standard_EXPORT BinObjMgt_Persistent& PutRealArray(const BinObjMgt_PReal theArray,
                                                     const int             theLength);

  Standard_EXPORT BinObjMgt_Persistent& PutShortRealArray(const BinObjMgt_PShortReal theArray,
                                                          const int                  theLength);

  Standard_EXPORT const BinObjMgt_Persistent& GetCharacter(char& theValue) const;

  const BinObjMgt_Persistent& operator>>(char& theValue) const { return GetCharacter(theValue); }

  Standard_EXPORT const BinObjMgt_Persistent& GetByte(uint8_t& theValue) const;

  const BinObjMgt_Persistent& operator>>(uint8_t& theValue) const { return GetByte(theValue); }

  Standard_EXPORT const BinObjMgt_Persistent& GetExtCharacter(char16_t& theValue) const;

  const BinObjMgt_Persistent& operator>>(char16_t& theValue) const
  {
    return GetExtCharacter(theValue);
  }

  Standard_EXPORT const BinObjMgt_Persistent& GetInteger(int& theValue) const;

  const BinObjMgt_Persistent& operator>>(int& theValue) const { return GetInteger(theValue); }

  const BinObjMgt_Persistent& GetBoolean(bool& theValue) const;

  const BinObjMgt_Persistent& operator>>(bool& theValue) const { return GetBoolean(theValue); }

  Standard_EXPORT const BinObjMgt_Persistent& GetReal(double& theValue) const;

  const BinObjMgt_Persistent& operator>>(double& theValue) const { return GetReal(theValue); }

  Standard_EXPORT const BinObjMgt_Persistent& GetShortReal(float& theValue) const;

  const BinObjMgt_Persistent& operator>>(float& theValue) const { return GetShortReal(theValue); }

  Standard_EXPORT const BinObjMgt_Persistent& GetAsciiString(
    TCollection_AsciiString& theValue) const;

  const BinObjMgt_Persistent& operator>>(TCollection_AsciiString& theValue) const
  {
    return GetAsciiString(theValue);
  }

  Standard_EXPORT const BinObjMgt_Persistent& GetExtendedString(
    TCollection_ExtendedString& theValue) const;

  const BinObjMgt_Persistent& operator>>(TCollection_ExtendedString& theValue) const
  {
    return GetExtendedString(theValue);
  }

  Standard_EXPORT const BinObjMgt_Persistent& GetLabel(const occ::handle<TDF_Data>& theDS,
                                                       TDF_Label&                   theValue) const;

  Standard_EXPORT const BinObjMgt_Persistent& GetGUID(Standard_GUID& theValue) const;

  const BinObjMgt_Persistent& operator>>(Standard_GUID& theValue) const
  {
    return GetGUID(theValue);
  }

  Standard_EXPORT const BinObjMgt_Persistent& GetCharArray(const BinObjMgt_PChar theArray,
                                                           const int             theLength) const;

  Standard_EXPORT const BinObjMgt_Persistent& GetByteArray(const BinObjMgt_PByte theArray,
                                                           const int             theLength) const;

  Standard_EXPORT const BinObjMgt_Persistent& GetExtCharArray(const BinObjMgt_PExtChar theArray,
                                                              const int theLength) const;

  Standard_EXPORT const BinObjMgt_Persistent& GetIntArray(const BinObjMgt_PInteger theArray,
                                                          const int                theLength) const;

  Standard_EXPORT const BinObjMgt_Persistent& GetRealArray(const BinObjMgt_PReal theArray,
                                                           const int             theLength) const;

  Standard_EXPORT const BinObjMgt_Persistent& GetShortRealArray(const BinObjMgt_PShortReal theArray,
                                                                const int theLength) const;

  int Position() const;

  bool SetPosition(const int thePos) const;

  void Truncate();

  bool IsError() const;

  bool operator!() const { return IsError(); }

  bool IsOK() const;

  operator bool() const { return IsOK(); }

  Standard_EXPORT void Init();

  void SetId(const int theId);

  void SetTypeId(const int theId);

  int Id() const;

  int TypeId() const;

  int Length() const;

  Standard_EXPORT Standard_OStream& Write(Standard_OStream& theOS,
                                          const bool        theDirectStream = false);

  Standard_EXPORT Standard_IStream& Read(Standard_IStream& theIS);

  Standard_EXPORT void Destroy();

  ~BinObjMgt_Persistent() { Destroy(); }

  Standard_EXPORT void SetOStream(Standard_OStream& theStream) { myOStream = &theStream; }

  Standard_EXPORT void SetIStream(Standard_IStream& theStream) { myIStream = &theStream; }

  Standard_EXPORT Standard_OStream* GetOStream();

  Standard_EXPORT Standard_IStream* GetIStream();

  Standard_EXPORT bool IsDirect() { return myDirectWritingIsEnabled; }

  Standard_EXPORT occ::handle<BinObjMgt_Position> StreamStart() { return myStreamStart; }

private:
  void alignOffset(const int theSize, const bool toClear = false) const;

  int prepareForPut(const int theSize);

  Standard_EXPORT void incrementData(const int theNbPieces);

  bool noMoreData(const int theSize) const;

  Standard_EXPORT void putArray(void* const theArray, const int theSize);

  Standard_EXPORT void getArray(void* const theArray, const int theSize) const;

  Standard_EXPORT void inverseExtCharData(const int theIndex,
                                          const int theOffset,
                                          const int theSize);

  Standard_EXPORT void inverseIntData(const int theIndex, const int theOffset, const int theSize);

  Standard_EXPORT void inverseRealData(const int theIndex, const int theOffset, const int theSize);

  Standard_EXPORT void inverseShortRealData(const int theIndex,
                                            const int theOffset,
                                            const int theSize);

  NCollection_Sequence<void*> myData;
  int                         myIndex;
  int                         myOffset;
  int                         mySize;
  bool                        myIsError;
  Standard_OStream*           myOStream;
  Standard_IStream*           myIStream;
  bool                        myDirectWritingIsEnabled;

  occ::handle<BinObjMgt_Position> myStreamStart;
};

#define BP_HEADSIZE ((int)(3 * sizeof(int)))
#define BP_PIECESIZE 102400

inline void BinObjMgt_Persistent::SetId(const int theId)
{
  ((int*)myData(1))[1] = theId;
}

inline void BinObjMgt_Persistent::SetTypeId(const int theTypeId)
{
  ((int*)myData(1))[0] = theTypeId;
  myStreamStart.Nullify();
}

inline int BinObjMgt_Persistent::Id() const
{
  return ((int*)myData(1))[1];
}

inline int BinObjMgt_Persistent::TypeId() const
{
  return ((int*)myData(1))[0];
}

inline int BinObjMgt_Persistent::Length() const
{
  return mySize - BP_HEADSIZE;
}

inline Standard_OStream& operator<<(Standard_OStream& theOS, BinObjMgt_Persistent& theObj)
{
  return theObj.Write(theOS);
}

inline Standard_IStream& operator>>(Standard_IStream& theIS, BinObjMgt_Persistent& theObj)
{
  return theObj.Read(theIS);
}

inline int BinObjMgt_Persistent::Position() const
{
  return (myIndex - 1) * BP_PIECESIZE + myOffset;
}

inline bool BinObjMgt_Persistent::SetPosition(const int thePos) const
{
  ((BinObjMgt_Persistent*)this)->myIndex   = thePos / BP_PIECESIZE + 1;
  ((BinObjMgt_Persistent*)this)->myOffset  = thePos % BP_PIECESIZE;
  ((BinObjMgt_Persistent*)this)->myIsError = thePos > mySize || thePos < BP_HEADSIZE;
  return !myIsError;
}

inline void BinObjMgt_Persistent::Truncate()
{
  mySize = Position();
}

inline bool BinObjMgt_Persistent::IsError() const
{
  return myIsError;
}

inline bool BinObjMgt_Persistent::IsOK() const
{
  return !myIsError;
}

inline void BinObjMgt_Persistent::alignOffset(const int theSize, const bool toClear) const
{
  unsigned alignMask = theSize - 1;
  int      anOffset  = (myOffset + alignMask) & ~alignMask;

  if (anOffset > myOffset)
  {
    if (toClear && anOffset <= BP_PIECESIZE)
      memset(((char*)myData(myIndex)) + myOffset, 0, anOffset - myOffset);
    ((BinObjMgt_Persistent*)this)->myOffset = anOffset;
  }

  if (myOffset >= BP_PIECESIZE)
  {
    ((BinObjMgt_Persistent*)this)->myIndex++;
    ((BinObjMgt_Persistent*)this)->myOffset = 0;
  }
}

inline int BinObjMgt_Persistent::prepareForPut(const int theSize)
{
  int nbPieces = (myOffset + theSize - 1) / BP_PIECESIZE;
  int nbToAdd  = myIndex + nbPieces - myData.Length();
  if (nbToAdd > 0)

    incrementData(nbToAdd);
  int aNewPosition = Position() + theSize;
  if (aNewPosition > mySize)
    mySize = aNewPosition;
  return nbPieces;
}

inline bool BinObjMgt_Persistent::noMoreData(const int theSize) const
{
  ((BinObjMgt_Persistent*)this)->myIsError = Position() + theSize > mySize;
  return myIsError;
}

inline BinObjMgt_Persistent& BinObjMgt_Persistent::PutBoolean(const bool theValue)
{
  return PutInteger((int)theValue);
}

inline const BinObjMgt_Persistent& BinObjMgt_Persistent::GetBoolean(bool& theValue) const
{

  int anIntVal;
  GetInteger(anIntVal);
  theValue = anIntVal != 0;
  return *this;
}
