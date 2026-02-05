#pragma once

#include <Standard_Dump.hpp>
#include <Standard_Transient.hpp>

//! Low-level buffer object.
class NCollection_Buffer : public Standard_Transient
{

public:
  //! Default constructor.
  //! When theData is NULL but theSize is not 0 than buffer of specified size will be allocated.
  //! @param theAlloc memory allocator
  //! @param theSize  buffer size
  //! @param theData  buffer data allocated by theAlloc
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

  //! Destructor.
  ~NCollection_Buffer() override { Free(); }

  //! @return buffer data
  const uint8_t* Data() const noexcept { return myData; }

  //! @return buffer data
  uint8_t* ChangeData() noexcept { return myData; }

  //! @return true if buffer is not allocated
  bool IsEmpty() const noexcept { return myData == nullptr; }

  //! Return buffer length in bytes.
  size_t Size() const noexcept { return mySize; }

  //! @return buffer allocator
  const occ::handle<NCollection_BaseAllocator>& Allocator() const noexcept { return myAllocator; }

  //! Assign new buffer allocator with de-allocation of buffer.
  void SetAllocator(const occ::handle<NCollection_BaseAllocator>& theAlloc)
  {
    Free();
    myAllocator = theAlloc;
  }

  //! Allocate the buffer.
  //! @param theSize buffer length in bytes
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

  //! De-allocate buffer.
  void Free()
  {
    if (!myAllocator.IsNull())
    {
      myAllocator->Free(myData);
    }
    myData = nullptr;
    mySize = 0;
  }

  //! Dumps the content of me into the stream
  virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const
  {
    (void)theDepth;
    OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, myData)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, mySize)
    OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, myAllocator.get())
  }

protected:
  uint8_t*                               myData;      //!< data pointer
  size_t                                 mySize;      //!< buffer length in bytes
  occ::handle<NCollection_BaseAllocator> myAllocator; //!< buffer allocator

public:
  DEFINE_STANDARD_RTTI_INLINE(NCollection_Buffer, Standard_Transient) // Type definition
};
