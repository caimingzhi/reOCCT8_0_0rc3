#pragma once

#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

struct AVBufferPool;
struct AVBufferRef;

class Media_BufferPool : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Media_BufferPool, Standard_Transient)
public:
  Standard_EXPORT Media_BufferPool();

  Standard_EXPORT ~Media_BufferPool() override;

  Standard_EXPORT void Release();

  Standard_EXPORT bool Init(int theBufferSize);

  int BufferSize() const { return myBufferSize; }

  Standard_EXPORT AVBufferRef* GetBuffer();

private:
  Media_BufferPool(const Media_BufferPool& theCopy)            = delete;
  Media_BufferPool& operator=(const Media_BufferPool& theCopy) = delete;

protected:
  AVBufferPool* myPool;
  int           myBufferSize;
};
