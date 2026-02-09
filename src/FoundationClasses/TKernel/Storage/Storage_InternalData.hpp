#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Persistent.hpp>

class Storage_Schema;
class Storage_BucketOfPersistent;
class Storage_BucketIterator;

class Storage_Bucket
{
  friend class Storage_BucketIterator;
  friend class Storage_Schema;
  friend class Storage_BucketOfPersistent;

  Standard_Persistent** mySpace;
  int                   mySpaceSize;
  int                   myCurrentSpace;

  void Append(Standard_Persistent*);

  Standard_Persistent* Value(const int theIndex) const;

public:
  Storage_Bucket()
      : mySpace(nullptr),
        mySpaceSize(200000),
        myCurrentSpace(-1)
  {
    mySpace = (Standard_Persistent**)Standard::Allocate(sizeof(Standard_Persistent*) * mySpaceSize);
  }

  Storage_Bucket(const int theSpaceSize)
      : mySpace(nullptr),
        mySpaceSize(theSpaceSize),
        myCurrentSpace(-1)
  {
    mySpace = (Standard_Persistent**)Standard::Allocate(sizeof(Standard_Persistent*) * mySpaceSize);
  }

  void Clear();

  ~Storage_Bucket();
};

class Storage_BucketOfPersistent
{
  friend class Storage_BucketIterator;
  Storage_Bucket** myBuckets;
  int              myNumberOfBucket;
  int              myNumberOfBucketAllocated;
  Storage_Bucket*  myCurrentBucket;
  int              myCurrentBucketNumber;
  int              myLength;
  int              myBucketSize;

public:
  Storage_BucketOfPersistent(const int theBucketSize = 300000, const int theBucketNumber = 100);

  int Length() const { return myLength; }

  void Append(const occ::handle<Standard_Persistent>& sp);

  Standard_Persistent* Value(const int theIndex);

  void Clear();

  ~Storage_BucketOfPersistent();
};

class Storage_BucketIterator
{
  Storage_BucketOfPersistent* myBucket;
  Storage_Bucket*             myCurrentBucket;
  int                         myCurrentBucketIndex;
  int                         myCurrentIndex;
  int                         myBucketNumber;
  bool                        myMoreObject;

public:
  Storage_BucketIterator(Storage_BucketOfPersistent*);
  void Init(Storage_BucketOfPersistent*);
  void Reset();

  Standard_Persistent* Value() const
  {
    if (myCurrentBucket)
    {
      return myCurrentBucket->mySpace[myCurrentIndex];
    }
    else
      return nullptr;
  }

  bool More() const { return myMoreObject; }

  void Next();
};

#include <Standard_Integer.hpp>
#include <Standard_Persistent.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TCollection_AsciiString.hpp>
#include <Storage_TypedCallBack.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>

class Storage_InternalData : public Standard_Transient
{

public:
  occ::handle<NCollection_HArray1<occ::handle<Standard_Persistent>>>& ReadArray()
  {
    return myReadArray;
  }

  Standard_EXPORT Storage_InternalData();

  Standard_EXPORT void Clear();

  friend class Storage_Schema;

  DEFINE_STANDARD_RTTIEXT(Storage_InternalData, Standard_Transient)

private:
  Storage_BucketOfPersistent                                                       myPtoA;
  int                                                                              myObjId;
  int                                                                              myTypeId;
  occ::handle<NCollection_HArray1<occ::handle<Standard_Persistent>>>               myReadArray;
  NCollection_DataMap<TCollection_AsciiString, occ::handle<Storage_TypedCallBack>> myTypeBinding;
};
