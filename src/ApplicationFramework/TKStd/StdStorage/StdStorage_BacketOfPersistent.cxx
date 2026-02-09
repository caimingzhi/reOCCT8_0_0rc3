

#include <StdStorage_BacketOfPersistent.hpp>
#include <StdObjMgt_Persistent.hpp>

StdStorage_Bucket::~StdStorage_Bucket()
{
  Standard::Free(mySpace);
  mySpace     = nullptr;
  mySpaceSize = 0;
  Clear();
}

void StdStorage_Bucket::Clear()
{
  myCurrentSpace = -1;
}

void StdStorage_Bucket::Append(StdObjMgt_Persistent* sp)
{
  ++myCurrentSpace;
  mySpace[myCurrentSpace] = sp;
}

StdObjMgt_Persistent* StdStorage_Bucket::Value(const int theIndex) const
{
  return mySpace[theIndex];
}

StdStorage_BucketOfPersistent::StdStorage_BucketOfPersistent(const int theBucketSize,
                                                             const int theBucketNumber)
    : myNumberOfBucket(1),
      myNumberOfBucketAllocated(theBucketNumber),
      myBucketSize(theBucketSize)
{
  myBuckets = (StdStorage_Bucket**)Standard::Allocate(sizeof(StdStorage_Bucket*) * theBucketNumber);
  myBuckets[0]          = new StdStorage_Bucket(myBucketSize);
  myCurrentBucket       = myBuckets[0];
  myLength              = 0;
  myCurrentBucketNumber = 0;
}

void StdStorage_BucketOfPersistent::Clear()
{
  if (myBuckets)
  {
    int i;

    for (i = 1; i < myNumberOfBucket; i++)
      delete myBuckets[i];
    myNumberOfBucket = 1;
    myCurrentBucket  = myBuckets[0];
    myCurrentBucket->Clear();
    myCurrentBucketNumber = 0;
    myLength              = 0;
  }
}

StdStorage_BucketOfPersistent::~StdStorage_BucketOfPersistent()
{
  Clear();
  delete myBuckets[0];
  Standard::Free(myBuckets);
  myBuckets = nullptr;
}

StdObjMgt_Persistent* StdStorage_BucketOfPersistent::Value(const int theIndex)
{
  int theInd, theCurrentBucketNumber, tecurrentind = theIndex - 1;
  theCurrentBucketNumber = tecurrentind / myBucketSize;
  theInd                 = tecurrentind - (myBucketSize * theCurrentBucketNumber);

  return myBuckets[theCurrentBucketNumber]->mySpace[theInd];
}

void StdStorage_BucketOfPersistent::Append(const occ::handle<StdObjMgt_Persistent>& sp)
{
  myCurrentBucket->myCurrentSpace++;

  if (myCurrentBucket->myCurrentSpace != myBucketSize)
  {
    myLength++;
    myCurrentBucket->mySpace[myCurrentBucket->myCurrentSpace] = sp.operator->();
    return;
  }

  myCurrentBucket->myCurrentSpace--;
  myNumberOfBucket++;
  myCurrentBucketNumber++;

  if (myNumberOfBucket > myNumberOfBucketAllocated)
  {
    size_t e  = sizeof(StdStorage_Bucket*) * myNumberOfBucketAllocated;
    myBuckets = (StdStorage_Bucket**)Standard::Reallocate(myBuckets, e * 2);
    myNumberOfBucketAllocated *= 2;
  }

  myBuckets[myCurrentBucketNumber] = new StdStorage_Bucket(myBucketSize);
  myCurrentBucket                  = myBuckets[myCurrentBucketNumber];
  myCurrentBucket->myCurrentSpace++;
  myLength++;
  myCurrentBucket->mySpace[myCurrentBucket->myCurrentSpace] = sp.operator->();
}

StdStorage_BucketIterator::StdStorage_BucketIterator(StdStorage_BucketOfPersistent* aBucketManager)
{
  if (aBucketManager)
  {
    myBucket             = aBucketManager;
    myCurrentBucket      = myBucket->myBuckets[0];
    myBucketNumber       = aBucketManager->myNumberOfBucket;
    myCurrentBucketIndex = 0;
    myCurrentIndex       = 0;
    myMoreObject         = true;
  }
  else
    myMoreObject = false;
}

void StdStorage_BucketIterator::Reset()
{
  if (myBucket)
  {
    myCurrentBucket      = myBucket->myBuckets[0];
    myBucketNumber       = myBucket->myNumberOfBucket;
    myCurrentIndex       = 0;
    myCurrentBucketIndex = 0;
    myMoreObject         = true;
  }
  else
    myMoreObject = false;
}

void StdStorage_BucketIterator::Init(StdStorage_BucketOfPersistent* aBucketManager)
{
  if (aBucketManager)
  {
    myBucket             = aBucketManager;
    myCurrentBucket      = myBucket->myBuckets[0];
    myBucketNumber       = aBucketManager->myNumberOfBucket;
    myCurrentIndex       = 0;
    myCurrentBucketIndex = 0;
    myMoreObject         = true;
  }
  else
    myMoreObject = false;
}

void StdStorage_BucketIterator::Next()
{
  if (!myMoreObject)
    return;

  if (myCurrentIndex < myCurrentBucket->myCurrentSpace)
  {
    myCurrentIndex++;
  }
  else
  {
    myCurrentIndex = 0;
    myCurrentBucketIndex++;
    if (myCurrentBucketIndex < myBucketNumber)
    {
      myCurrentBucket = myBucket->myBuckets[myCurrentBucketIndex];
    }
    else
    {
      myMoreObject = false;
    }
  }
}
