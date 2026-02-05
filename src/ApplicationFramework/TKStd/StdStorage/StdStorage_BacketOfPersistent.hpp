#pragma once

#include <Standard.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Integer.hpp>

class StdObjMgt_Persistent;

class StdStorage_Bucket
{
  friend class StdStorage_BucketIterator;
  friend class StdStorage_BucketOfPersistent;

  StdObjMgt_Persistent** mySpace;
  int                    mySpaceSize;
  int                    myCurrentSpace;

  void Append(StdObjMgt_Persistent*);

  StdObjMgt_Persistent* Value(const int theIndex) const;

public:
  StdStorage_Bucket()
      : mySpace(nullptr),
        mySpaceSize(200000),
        myCurrentSpace(-1)
  {
    mySpace =
      (StdObjMgt_Persistent**)Standard::Allocate(sizeof(StdObjMgt_Persistent*) * mySpaceSize);
  }

  StdStorage_Bucket(const int theSpaceSize)
      : mySpace(nullptr),
        mySpaceSize(theSpaceSize),
        myCurrentSpace(-1)
  {
    mySpace =
      (StdObjMgt_Persistent**)Standard::Allocate(sizeof(StdObjMgt_Persistent*) * mySpaceSize);
  }

  void Clear();

  ~StdStorage_Bucket();
};

class StdStorage_BucketOfPersistent
{
  friend class StdStorage_BucketIterator;
  StdStorage_Bucket** myBuckets;
  int                 myNumberOfBucket;
  int                 myNumberOfBucketAllocated;
  StdStorage_Bucket*  myCurrentBucket;
  int                 myCurrentBucketNumber;
  int                 myLength;
  int                 myBucketSize;

public:
  StdStorage_BucketOfPersistent(const int theBucketSize = 300000, const int theBucketNumber = 100);

  int Length() const { return myLength; }

  void Append(const occ::handle<StdObjMgt_Persistent>& sp);

  StdObjMgt_Persistent* Value(const int theIndex);

  void Clear();

  ~StdStorage_BucketOfPersistent();
};

class StdStorage_BucketIterator
{
  StdStorage_BucketOfPersistent* myBucket;
  StdStorage_Bucket*             myCurrentBucket;
  int                            myCurrentBucketIndex;
  int                            myCurrentIndex;
  int                            myBucketNumber;
  bool                           myMoreObject;

public:
  StdStorage_BucketIterator(StdStorage_BucketOfPersistent*);

  void Init(StdStorage_BucketOfPersistent*);
  void Reset();

  StdObjMgt_Persistent* Value() const
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
