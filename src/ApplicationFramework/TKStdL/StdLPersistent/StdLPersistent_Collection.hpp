#pragma once


#include <StdObjMgt_Attribute.hpp>
#include <StdLPersistent_HArray1.hpp>

#include <TDataStd_IntegerArray.hpp>
#include <TDataStd_RealArray.hpp>
#include <TDataStd_ByteArray.hpp>
#include <TDataStd_ExtStringArray.hpp>
#include <TDataStd_BooleanArray.hpp>
#include <TDataStd_ReferenceArray.hpp>
#include <TDataStd_IntegerList.hpp>
#include <TDataStd_RealList.hpp>
#include <TDataStd_ExtStringList.hpp>
#include <TDataStd_BooleanList.hpp>
#include <TDataStd_ReferenceList.hpp>
#include <TDataStd_IntPackedMap.hpp>

class StdLPersistent_Collection
{
  // Converters
  struct noConversion;
  struct byteConverter;
  struct boolConverter;
  struct stringConverter;
  struct referenceConverter;

  // Base templates
  template <class Base>
  class booleanArrayBase : public Base
  {
  public:
    //! Empty constructor.
    booleanArrayBase()
        : myLower(0),
          myUpper(0)
    {
    }

    //! Read persistent data from a file.
    void Read(StdObjMgt_ReadData& theReadData) override
    {
      Base::Read(theReadData);
      theReadData >> myLower >> myUpper;
    }

  protected:
    template <class ArrayHandle, class Converter>
    inline void import(const ArrayHandle& theArray, Converter theConverter) const;

  protected:
    int myLower;
    int myUpper;
  };

  template <class Base>
  class directArrayBase : public Base
  {
  protected:
    template <class ArrayHandle, class Converter>
    inline void import(const ArrayHandle& theArray, Converter theConverter) const;
  };

  template <class Base>
  class arrayBase : public Base
  {
  protected:
    template <class ArrayHandle, class Converter>
    inline void import(const ArrayHandle& theArray, Converter theConverter) const;
  };

  template <class Base>
  class listBase : public Base
  {
  protected:
    template <class ArrayHandle, class Converter>
    inline void import(const ArrayHandle& theArray, Converter theConverter) const;
  };

  template <class Base>
  class mapBase : public Base
  {
  protected:
    template <class ArrayHandle, class Converter>
    inline void import(const ArrayHandle& theArray, Converter theConverter) const;
  };

  // Instance templates
  template <template <class> class BaseT, class HArrayClass, class AttribClass, class Converter>
  class instance : public BaseT<typename StdObjMgt_Attribute<AttribClass>::SingleRef>
  {
  public:
    //! Import transient attribute from the persistent data.
    Standard_EXPORT void ImportAttribute() override;
  };

  template <class Instance>
  class instance_1 : public Instance
  {
  public:
    //! Empty constructor.
    instance_1()
        : myDelta(false)
    {
    }

    //! Read persistent data from a file.
    Standard_EXPORT void Read(StdObjMgt_ReadData& theReadData) override;

    //! Import transient attribute from the persistent data.
    Standard_EXPORT void ImportAttribute() override;

  private:
    bool myDelta;
  };

  // Collection type specialization
  template <class HArrayClass, class AttribClass, class Converter = noConversion>
  struct booleanArrayT : instance<booleanArrayBase, HArrayClass, AttribClass, Converter>
  {
  };

  template <class HArrayClass, class AttribClass, class Converter = noConversion>
  struct directArrayT : instance<directArrayBase, HArrayClass, AttribClass, Converter>
  {
  };

  template <class HArrayClass, class AttribClass, class Converter = noConversion>
  struct arrayT : instance<arrayBase, HArrayClass, AttribClass, Converter>
  {
  };

  template <class HArrayClass, class AttribClass, class Converter = noConversion>
  struct listT : instance<listBase, HArrayClass, AttribClass, Converter>
  {
  };

  template <class HArrayClass, class AttribClass, class Converter = noConversion>
  struct mapT : instance<mapBase, HArrayClass, AttribClass, Converter>
  {
  };

  // Internal array types
  typedef StdLPersistent_HArray1::Integer    integer;
  typedef StdLPersistent_HArray1::Real       real;
  typedef StdLPersistent_HArray1::Persistent persistent;

public:
  // Final specialization
  typedef booleanArrayT<integer, TDataStd_BooleanArray, byteConverter> BooleanArray;

  typedef directArrayT<integer, TDataStd_IntegerArray> IntegerArray;

  typedef directArrayT<real, TDataStd_RealArray> RealArray;

  typedef arrayT<integer, TDataStd_ByteArray, byteConverter> ByteArray;

  typedef arrayT<persistent, TDataStd_ExtStringArray, stringConverter> ExtStringArray;

  typedef arrayT<persistent, TDataStd_ReferenceArray, referenceConverter> ReferenceArray;

  typedef listT<integer, TDataStd_IntegerList> IntegerList;

  typedef listT<real, TDataStd_RealList> RealList;

  typedef listT<integer, TDataStd_BooleanList, boolConverter> BooleanList;

  typedef listT<persistent, TDataStd_ExtStringList, stringConverter> ExtStringList;

  typedef listT<persistent, TDataStd_ReferenceList, referenceConverter> ReferenceList;

  typedef mapT<integer, TDataStd_IntPackedMap> IntPackedMap;

  typedef instance_1<IntegerArray>   IntegerArray_1;
  typedef instance_1<RealArray>      RealArray_1;
  typedef instance_1<ByteArray>      ByteArray_1;
  typedef instance_1<ExtStringArray> ExtStringArray_1;
  typedef instance_1<IntPackedMap>   IntPackedMap_1;
};

