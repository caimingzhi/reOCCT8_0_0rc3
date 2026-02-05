#pragma once

#include <Standard_NotImplemented.hpp>
#include <Standard_NullValue.hpp>

#include <StdObjMgt_Persistent.hpp>
#include <StdObjMgt_ReadData.hpp>
#include <StdObjMgt_WriteData.hpp>

#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>

class StdLPersistent_HArray1
{
  class base : public StdObjMgt_Persistent
  {
  public:
    //! Read persistent data from a file.
    Standard_EXPORT void Read(StdObjMgt_ReadData& theReadData) override;
    //! Write persistent data to a file.
    Standard_EXPORT void Write(StdObjMgt_WriteData& theWriteData) const override;

  protected:
    virtual int  lowerBound() const                                            = 0;
    virtual int  upperBound() const                                            = 0;
    virtual void createArray(const int theLowerBound, const int theUpperBound) = 0;

    virtual void readValue(StdObjMgt_ReadData& theReadData, const int theIndex)          = 0;
    virtual void writeValue(StdObjMgt_WriteData& theWriteData, const int theIndex) const = 0;
  };

protected:
  template <class ArrayClass>
  class instance : public base
  {
    friend class StdLPersistent_HArray1;

  public:
    typedef occ::handle<ArrayClass>         ArrayHandle;
    typedef typename ArrayClass::value_type ValueType;
    typedef typename ArrayClass::Iterator   Iterator;

  public:
    //! Get the array.
    const occ::handle<ArrayClass>& Array() const { return myArray; }

  protected:
    int lowerBound() const override { return myArray->Lower(); }

    int upperBound() const override { return myArray->Upper(); }

    void createArray(const int theLowerBound, const int theUpperBound) override
    {
      myArray = new ArrayClass(theLowerBound, theUpperBound);
    }

    void readValue(StdObjMgt_ReadData& theReadData, const int theIndex) override
    {
      theReadData >> myArray->ChangeValue(theIndex);
    }

    void writeValue(StdObjMgt_WriteData& theWriteData, const int theIndex) const override
    {
      theWriteData << myArray->Value(theIndex);
    }

    void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const override
    {
      return PChildrenT(theChildren);
    }

    const char* PName() const override { return PNameT(); }

    const char* PNameT() const
    {
      throw Standard_NotImplemented("StdLPersistent_HArray1::instance::PName - not implemented");
    }

    void PChildrenT(StdObjMgt_Persistent::SequenceOfPersistent&) const {}

  protected:
    occ::handle<ArrayClass> myArray;
  };

  template <class ArrayClass>
  class named_instance : public instance<ArrayClass>
  {
    friend class StdLPersistent_HArray1;

  public:
    const char* PName() const override
    {
      Standard_NullValue_Raise_if(!myPName,
                                  "StdLPersistent_HArray1::named_instance::PName - name not set");
      return myPName;
    }

  protected:
    named_instance(const char* thePName)
        : myPName(thePName)
    {
    }

    const char* myPName;
  };

public:
  typedef instance<NCollection_HArray1<int>>                               Integer;
  typedef instance<NCollection_HArray1<double>>                            Real;
  typedef instance<NCollection_HArray1<uint8_t>>                           Byte;
  typedef instance<NCollection_HArray1<occ::handle<StdObjMgt_Persistent>>> Persistent;

public:
  template <class ArrayClass>
  static Handle(instance<ArrayClass>) Translate(const ArrayClass& theArray)
  {
    Handle(instance<ArrayClass>) aPArray = new instance<ArrayClass>;
    aPArray->myArray                     = new ArrayClass(theArray.Lower(), theArray.Upper());
    for (int i = theArray.Lower(); i <= theArray.Upper(); ++i)
      aPArray->myArray->ChangeValue(i) = theArray.Value(i);
    return aPArray;
  }

  template <class ArrayClass>
  static Handle(instance<ArrayClass>) Translate(const char* thePName, const ArrayClass& theArray)
  {
    Handle(named_instance<ArrayClass>) aPArray = new named_instance<ArrayClass>(thePName);
    aPArray->myArray                           = new ArrayClass(theArray.Lower(), theArray.Upper());
    for (int i = theArray.Lower(); i <= theArray.Upper(); ++i)
      aPArray->myArray->ChangeValue(i) = theArray.Value(i);
    return aPArray;
  }
};

template <>
inline const char* StdLPersistent_HArray1::instance<NCollection_HArray1<int>>::PNameT() const
{
  return "PColStd_HArray1OfInteger";
}

template <>
inline const char* StdLPersistent_HArray1::instance<NCollection_HArray1<double>>::PNameT() const
{
  return "PColStd_HArray1OfReal";
}

template <>
inline const char* StdLPersistent_HArray1::instance<NCollection_HArray1<uint8_t>>::PNameT() const
{
  return "PColStd_HArray1OfByte";
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, uint8_t& theByte)
{
  return theReadData >> reinterpret_cast<char&>(theByte);
}

inline StdObjMgt_WriteData& operator>>(StdObjMgt_WriteData& theWriteData, const uint8_t& theByte)
{
  return theWriteData << reinterpret_cast<const char&>(theByte);
}

template <>
inline void StdLPersistent_HArray1::
  instance<NCollection_HArray1<occ::handle<StdObjMgt_Persistent>>>::PChildrenT(
    StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
{
  for (int i = myArray->Lower(); i <= myArray->Upper(); ++i)
    theChildren.Append(myArray->Value(i));
}
