#pragma once


#include <Standard_Type.hpp>

#include <fstream>

// Suppress VC9 warning on xsputn() function
#ifdef _MSC_VER
  #pragma warning(push)
  #pragma warning(disable : 4996)
#endif

//! Custom buffer object implementing STL interface std::streambuf for streamed reading from
//! allocated memory block. Implements minimal sub-set of methods for passing buffer to
//! std::istream, including seek support.
//!
//! This class can be used for creating a seekable input stream in cases,
//! when the source data does not satisfies Reader requirements (non-seekable stream, compressed
//! data) or represents an in-memory resource.
//!
//! The memory itself is NOT managed by this class - it is up to the caller to ensure that passed
//! memory pointer is not released during Standard_ArrayStreamBuffer lifetime.
//!
//! Usage example:
//! @code
//!   const char*  theBuffer;
//!   const size_t theBufferLength;
//!   Standard_ArrayStreamBuffer aStreamBuffer (theBuffer, theBufferLength);
//!   std::istream aStream (&aStreamBuffer);
//!   TopoDS_Shape aShape;
//!   BRep_Builder aBuilder;
//!   BRepTools::Read (aShape, aStream, aBuilder);
//! @endcode
class Standard_ArrayStreamBuffer : public std::streambuf
{
public:
  //! Main constructor.
  //! Passed pointer is stored as is (memory is NOT copied nor released with destructor).
  //! @param theBegin pointer to the beginning of pre-allocated buffer
  //! @param theSize  length of pre-allocated buffer
  Standard_EXPORT Standard_ArrayStreamBuffer(const char* theBegin, const size_t theSize);

  //! Destructor.
  Standard_EXPORT ~Standard_ArrayStreamBuffer() override;

  //! (Re)-initialize the stream.
  //! Passed pointer is stored as is (memory is NOT copied nor released with destructor).
  //! @param theBegin pointer to the beginning of pre-allocated buffer
  //! @param theSize  length of pre-allocated buffer
  Standard_EXPORT virtual void Init(const char* theBegin, const size_t theSize);

protected:
  //! Get character on underflow.
  //! Virtual function called by other member functions to get the current character
  //! in the controlled input sequence without changing the current position.
  Standard_EXPORT int_type underflow() override;

  //! Get character on underflow and advance position.
  //! Virtual function called by other member functions to get the current character
  //! in the controlled input sequence and then advance the position indicator to the next
  //! character.
  Standard_EXPORT int_type uflow() override;

  //! Put character back in the case of backup underflow.
  //! Virtual function called by other member functions to put a character back
  //! into the controlled input sequence and decrease the position indicator.
  Standard_EXPORT int_type pbackfail(int_type ch) override;

  //! Get number of characters available.
  //! Virtual function (to be read s-how-many-c) called by other member functions
  //! to get an estimate on the number of characters available in the associated input sequence.
  Standard_EXPORT std::streamsize showmanyc() override;

  //! Seek to specified position.
  Standard_EXPORT pos_type seekoff(off_type                theOff,
                                   std::ios_base::seekdir  theWay,
                                   std::ios_base::openmode theWhich) override;

  //! Change to specified position, according to mode.
  Standard_EXPORT pos_type seekpos(pos_type thePosition, std::ios_base::openmode theWhich) override;

public:
  //! Read a bunch of bytes at once.
  Standard_EXPORT std::streamsize xsgetn(char* thePtr, std::streamsize theCount) override;

private:
  // copying is not allowed
  Standard_ArrayStreamBuffer(const Standard_ArrayStreamBuffer&)            = delete;
  Standard_ArrayStreamBuffer& operator=(const Standard_ArrayStreamBuffer&) = delete;

protected:
  const char* myBegin;
  const char* myEnd;
  const char* myCurrent;
};

#ifdef _MSC_VER
  #pragma warning(pop)
#endif

