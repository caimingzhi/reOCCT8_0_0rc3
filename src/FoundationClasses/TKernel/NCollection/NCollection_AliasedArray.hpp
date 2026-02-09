#pragma once

#include <Standard_DimensionMismatch.hpp>
#include <Standard_OutOfMemory.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_TypeMismatch.hpp>
#include <Standard_Macro.hpp>

#include <cstring>

template <int MyAlignSize = 16>
class NCollection_AliasedArray
{
public:
  DEFINE_STANDARD_ALLOC
public:
  NCollection_AliasedArray(int theStride)
      : myData(nullptr),
        myStride(theStride),
        mySize(0),
        myDeletable(false)
  {
    if (theStride <= 0)
    {
      throw Standard_RangeError("NCollection_AliasedArray, stride should be positive");
    }
  }

  NCollection_AliasedArray(int theStride, int theLength)
      : myData(nullptr),
        myStride(theStride),
        mySize(theLength),
        myDeletable(true)
  {
    if (theLength <= 0 || myStride <= 0)
    {
      throw Standard_RangeError("NCollection_AliasedArray, stride and length should be positive");
    }
    myData = (uint8_t*)Standard::AllocateAligned(SizeBytes(), MyAlignSize);
    if (myData == nullptr)
    {
      throw Standard_OutOfMemory("NCollection_AliasedArray, allocation failed");
    }
  }

  NCollection_AliasedArray(const NCollection_AliasedArray& theOther)
      : myData(nullptr),
        myStride(theOther.myStride),
        mySize(theOther.mySize),
        myDeletable(false)
  {
    if (mySize != 0)
    {
      myDeletable = true;
      myData      = (uint8_t*)Standard::AllocateAligned(SizeBytes(), MyAlignSize);
      if (myData == nullptr)
      {
        throw Standard_OutOfMemory("NCollection_AliasedArray, allocation failed");
      }
      Assign(theOther);
    }
  }

  NCollection_AliasedArray(NCollection_AliasedArray&& theOther) noexcept
      : myData(theOther.myData),
        myStride(theOther.myStride),
        mySize(theOther.mySize),
        myDeletable(theOther.myDeletable)
  {
    theOther.myDeletable = false;
  }

  template <typename Type_t>
  NCollection_AliasedArray(const Type_t& theBegin, int theLength)
      : myData((uint8_t*)&theBegin),
        myStride((int)sizeof(Type_t)),
        mySize(theLength),
        myDeletable(false)
  {
    if (theLength <= 0)
    {
      throw Standard_RangeError("NCollection_AliasedArray, length should be positive");
    }
  }

  int Stride() const { return myStride; }

  int Size() const { return mySize; }

  int Length() const { return mySize; }

  bool IsEmpty() const { return mySize == 0; }

  int Lower() const { return 0; }

  int Upper() const { return mySize - 1; }

  bool IsDeletable() const { return myDeletable; }

  bool IsAllocated() const { return myDeletable; }

  size_t SizeBytes() const { return size_t(myStride) * size_t(mySize); }

  NCollection_AliasedArray& Assign(const NCollection_AliasedArray& theOther)
  {
    if (&theOther != this)
    {
      if (myStride != theOther.myStride || mySize != theOther.mySize)
      {
        throw Standard_DimensionMismatch(
          "NCollection_AliasedArray::Assign(), arrays have different size");
      }
      if (myData != nullptr)
      {
        memcpy(myData, theOther.myData, SizeBytes());
      }
    }
    return *this;
  }

  NCollection_AliasedArray& Move(NCollection_AliasedArray& theOther)
  {
    if (&theOther != this)
    {
      if (myDeletable)
      {
        Standard::FreeAligned(myData);
      }
      myStride             = theOther.myStride;
      mySize               = theOther.mySize;
      myDeletable          = theOther.myDeletable;
      myData               = theOther.myData;
      theOther.myDeletable = false;
    }
    return *this;
  }

  NCollection_AliasedArray& operator=(const NCollection_AliasedArray& theOther)
  {
    return Assign(theOther);
  }

  NCollection_AliasedArray& operator=(NCollection_AliasedArray&& theOther)
  {
    return Move(theOther);
  }

  void Resize(int theLength, bool theToCopyData)
  {
    if (theLength <= 0)
    {
      throw Standard_RangeError("NCollection_AliasedArray::Resize, length should be positive");
    }
    if (mySize == theLength)
    {
      return;
    }

    const int      anOldLen  = mySize;
    const uint8_t* anOldData = myData;
    mySize                   = theLength;
    if (!theToCopyData && myDeletable)
    {
      Standard::FreeAligned(myData);
    }
    myData = (uint8_t*)Standard::AllocateAligned(SizeBytes(), MyAlignSize);
    if (myData == nullptr)
    {
      throw Standard_OutOfMemory("NCollection_AliasedArray, allocation failed");
    }
    if (!theToCopyData)
    {
      myDeletable = true;
      return;
    }

    const size_t aLenCopy = size_t((std::min)(anOldLen, theLength)) * size_t(myStride);
    memcpy(myData, anOldData, aLenCopy);
    if (myDeletable)
    {
      Standard::FreeAligned(anOldData);
    }
    myDeletable = true;
  }

  ~NCollection_AliasedArray()
  {
    if (myDeletable)
    {
      Standard::FreeAligned(myData);
    }
  }

public:
  const uint8_t* value(int theIndex) const
  {
    Standard_OutOfRange_Raise_if(theIndex < 0 || theIndex >= mySize,
                                 "NCollection_AliasedArray::value(), out of range index");
    return myData + size_t(myStride) * size_t(theIndex);
  }

  uint8_t* changeValue(int theIndex)
  {
    Standard_OutOfRange_Raise_if(theIndex < 0 || theIndex >= mySize,
                                 "NCollection_AliasedArray::changeValue(), out of range index");
    return myData + size_t(myStride) * size_t(theIndex);
  }

  template <typename Type_t>
  void Init(const Type_t& theValue)
  {
    for (int anIter = 0; anIter < mySize; ++anIter)
    {
      ChangeValue<Type_t>(anIter) = theValue;
    }
  }

  template <typename Type_t>
  const Type_t& Value(int theIndex) const
  {
    Standard_TypeMismatch_Raise_if(size_t(myStride) != sizeof(Type_t),
                                   "NCollection_AliasedArray::Value(), wrong type");
    return *reinterpret_cast<const Type_t*>(value(theIndex));
  }

  template <typename Type_t>
  void Value(int theIndex, Type_t& theValue) const
  {
    Standard_TypeMismatch_Raise_if(size_t(myStride) != sizeof(Type_t),
                                   "NCollection_AliasedArray::Value(), wrong type");
    theValue = *reinterpret_cast<const Type_t*>(value(theIndex));
  }

  template <typename Type_t>
  Type_t& ChangeValue(int theIndex)
  {
    Standard_TypeMismatch_Raise_if(size_t(myStride) != sizeof(Type_t),
                                   "NCollection_AliasedArray::ChangeValue(), wrong type");
    return *reinterpret_cast<Type_t*>(changeValue(theIndex));
  }

  template <typename Type_t>
  const Type_t& Value2(int theIndex) const
  {
    Standard_TypeMismatch_Raise_if(size_t(myStride) < sizeof(Type_t),
                                   "NCollection_AliasedArray::Value2(), wrong type");
    return *reinterpret_cast<const Type_t*>(value(theIndex));
  }

  template <typename Type_t>
  void Value2(int theIndex, Type_t& theValue) const
  {
    Standard_TypeMismatch_Raise_if(size_t(myStride) < sizeof(Type_t),
                                   "NCollection_AliasedArray::Value2(), wrong type");
    theValue = *reinterpret_cast<const Type_t*>(value(theIndex));
  }

  template <typename Type_t>
  Type_t& ChangeValue2(int theIndex)
  {
    Standard_TypeMismatch_Raise_if(size_t(myStride) < sizeof(Type_t),
                                   "NCollection_AliasedArray::ChangeValue2(), wrong type");
    return *reinterpret_cast<Type_t*>(changeValue(theIndex));
  }

  template <typename Type_t>
  const Type_t& First() const
  {
    return Value<Type_t>(0);
  }

  template <typename Type_t>
  Type_t& ChangeFirst()
  {
    return ChangeValue<Type_t>(0);
  }

  template <typename Type_t>
  const Type_t& Last() const
  {
    return Value<Type_t>(mySize - 1);
  }

  template <typename Type_t>
  Type_t& ChangeLast()
  {
    return Value<Type_t>(mySize - 1);
  }

protected:
  uint8_t* myData;
  int      myStride;
  int      mySize;
  bool     myDeletable;
};
