#pragma once

#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

struct AVBufferPool;
struct AVBufferRef;

//! AVBufferPool wrapper.
class Media_BufferPool : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Media_BufferPool, Standard_Transient)
public:
  //! Empty constructor
  Standard_EXPORT Media_BufferPool();

  //! Destructor
  Standard_EXPORT ~Media_BufferPool() override;

  //! Release the pool (reference-counted buffer will be released when needed).
  Standard_EXPORT void Release();

  //! (Re-)initialize the pool.
  Standard_EXPORT bool Init(int theBufferSize);

  //! Return buffer size within the pool.
  int BufferSize() const { return myBufferSize; }

  //! Get new buffer from the pool.
  Standard_EXPORT AVBufferRef* GetBuffer();

private:
  // prevent copies
  Media_BufferPool(const Media_BufferPool& theCopy)            = delete;
  Media_BufferPool& operator=(const Media_BufferPool& theCopy) = delete;

protected:
  AVBufferPool* myPool;
  int           myBufferSize;
};
