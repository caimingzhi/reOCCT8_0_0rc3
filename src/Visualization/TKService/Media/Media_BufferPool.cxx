#ifndef __STDC_CONSTANT_MACROS
  #define __STDC_CONSTANT_MACROS
#endif

#include <Media_BufferPool.hpp>

#include <Media_Frame.hpp>

#ifdef HAVE_FFMPEG
  #include <Standard_WarningsDisable.hpp>
extern "C"
{
  #include <libavcodec/avcodec.h>
  #include <libavutil/imgutils.h>
};
  #include <Standard_WarningsRestore.hpp>
#endif

IMPLEMENT_STANDARD_RTTIEXT(Media_BufferPool, Standard_Transient)

Media_BufferPool::Media_BufferPool()
    : myPool(nullptr),
      myBufferSize(0)
{
}

Media_BufferPool::~Media_BufferPool()
{
  Release();
}

void Media_BufferPool::Release()
{
  if (myPool != nullptr)
  {
#ifdef HAVE_FFMPEG
    av_buffer_pool_uninit(&myPool);
#endif
    myPool       = nullptr;
    myBufferSize = 0;
  }
}

bool Media_BufferPool::Init(int theBufferSize)
{
  if (myBufferSize == theBufferSize)
  {
    return true;
  }

  Release();
  if (theBufferSize == 0)
  {
    return true;
  }

#ifdef HAVE_FFMPEG
  myPool = av_buffer_pool_init(theBufferSize, nullptr);
#endif
  myBufferSize = theBufferSize;
  return myPool != nullptr;
}

AVBufferRef* Media_BufferPool::GetBuffer()
{
#ifdef HAVE_FFMPEG
  return av_buffer_pool_get(myPool);
#else
  return nullptr;
#endif
}
