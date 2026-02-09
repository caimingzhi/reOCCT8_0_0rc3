#pragma once

#include <Standard_Dump.hpp>
#include <Standard_Transient.hpp>

class NCollection_Buffer : public Standard_Transient
{

public:
  NCollection_Buffer(const occ::handle<NCollection_BaseAllocator>& theAlloc,
                     const size_t                                  theSize = 0,
                     uint8_t*                                      theData = nullptr)
      : myData(nullptr),
        mySize(0),
        myAllocator(theAlloc)
  {
    if (theData != nullptr)
    {
      myData = theData;
      mySize = theSize;
    }
    else
    {
      Allocate(theSize);
    }
  }

  ~NCollection_Buffer() override { Free(); }

  const uint8_t* Data() const noexcept { return myData; }

  uint8_t* ChangeData() noexcept { return myData; }

  bool IsEmpty() const noexcept { return myData == nullptr; }

  size_t Size() const noexcept { return mySize; }

  const occ::handle<NCollection_BaseAllocator>& Allocator() const noexcept { return myAllocator; }

  void SetAllocator(const occ::handle<NCollection_BaseAllocator>& theAlloc)
  {
    Free();
    myAllocator = theAlloc;
  }

  bool Allocate(const size_t theSize)
  {
    Free();
    mySize = theSize;
    if (theSize != 0 || !myAllocator.IsNull())
    {
      myData = (uint8_t*)myAllocator->Allocate(theSize);
    }

    if (myData == nullptr)
    {
      mySize = 0;
      return false;
    }
    return true;
  }

  void Free()
  {
    if (!myAllocator.IsNull())
    {
      myAllocator->Free(myData);
    }
    myData = nullptr;
    mySize = 0;
  }

  virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const
  {
    (void)theDepth;
    OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, myData)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, mySize)
    OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, myAllocator.get())
  }

protected:
  uint8_t*                               myData;
  size_t                                 mySize;
  occ::handle<NCollection_BaseAllocator> myAllocator;

public:
  DEFINE_STANDARD_RTTI_INLINE(NCollection_Buffer, Standard_Transient)
};
