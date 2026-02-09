#pragma once

#include <StdObjMgt_Attribute.hpp>
#include <StdLPersistent_HArray1.hpp>
#include <StdLPersistent_HArray2.hpp>

#include <TDataStd_NamedData.hpp>
#include <TCollection_HExtendedString.hpp>

class StdLPersistent_NamedData : public StdObjMgt_Attribute<TDataStd_NamedData>
{
  template <class HValuesArray>
  class pMapData
  {
  public:
    typedef typename HValuesArray::ValueType ValueType;

    inline void Read(StdObjMgt_ReadData& theReadData) { theReadData >> myKeys >> myValues; }

    inline void Write(StdObjMgt_WriteData& theWriteData) const
    {
      theWriteData << myKeys << myValues;
    }

    inline operator bool() const { return !myKeys.IsNull(); }

    const TCollection_ExtendedString& Key(int theIndex) const
    {
      return myKeys->Array()->Value(theIndex)->ExtString()->String();
    }

    ValueType Value(int theIndex) const
    {
      return myValues ? myValues->Array()->Value(theIndex) : ValueType{};
    }

  private:
    Handle(StdLPersistent_HArray1::Persistent) myKeys;
    occ::handle<HValuesArray>                  myValues;
  };

public:
  inline void Read(StdObjMgt_ReadData& theReadData)
  {
    theReadData >> myDimensions;
    myInts.Read(theReadData);
    myReals.Read(theReadData);
    myStrings.Read(theReadData);
    myBytes.Read(theReadData);
    myIntArrays.Read(theReadData);
    myRealArrays.Read(theReadData);
  }

  inline void Write(StdObjMgt_WriteData& theWriteData) const
  {
    theWriteData << myDimensions;
    myInts.Write(theWriteData);
    myReals.Write(theWriteData);
    myStrings.Write(theWriteData);
    myBytes.Write(theWriteData);
    myIntArrays.Write(theWriteData);
    myRealArrays.Write(theWriteData);
  }

  void PChildren(StdObjMgt_Persistent::SequenceOfPersistent&) const {}

  const char* PName() const { return "PDataStd_NamedData"; }

  void Import(const occ::handle<TDataStd_NamedData>& theAttribute) const;

private:
  inline int lower(int theIndex) const;
  inline int upper(int theIndex) const;

private:
  Handle(StdLPersistent_HArray2::Integer)      myDimensions;
  pMapData<StdLPersistent_HArray1::Integer>    myInts;
  pMapData<StdLPersistent_HArray1::Real>       myReals;
  pMapData<StdLPersistent_HArray1::Persistent> myStrings;
  pMapData<StdLPersistent_HArray1::Byte>       myBytes;
  pMapData<StdLPersistent_HArray1::Persistent> myIntArrays;
  pMapData<StdLPersistent_HArray1::Persistent> myRealArrays;
};
