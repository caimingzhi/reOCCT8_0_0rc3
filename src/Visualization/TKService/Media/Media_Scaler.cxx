#ifndef __STDC_CONSTANT_MACROS
  #define __STDC_CONSTANT_MACROS
#endif

#include <Media_Scaler.hpp>

#ifdef HAVE_FFMPEG
  #include <Standard_WarningsDisable.hpp>
extern "C"
{
  #include <libavcodec/avcodec.h>
  #include <libavutil/imgutils.h>
  #include <libswscale/swscale.h>
};
  #include <Standard_WarningsRestore.hpp>
#endif

IMPLEMENT_STANDARD_RTTIEXT(Media_Scaler, Standard_Transient)

Media_Scaler::Media_Scaler()
    : mySwsContext(nullptr),
      mySrcFormat(0),
      myResFormat(0)
{
#ifdef HAVE_FFMPEG
  mySrcFormat = AV_PIX_FMT_NONE;
  myResFormat = AV_PIX_FMT_NONE;
#endif
}

Media_Scaler::~Media_Scaler()
{
  Release();
}

void Media_Scaler::Release()
{
  if (mySwsContext != nullptr)
  {
#ifdef HAVE_FFMPEG
    sws_freeContext(mySwsContext);
#endif
    mySwsContext = nullptr;
  }
}

bool Media_Scaler::Init(const NCollection_Vec2<int>& theSrcDims,
                        int                          theSrcFormat,
                        const NCollection_Vec2<int>& theResDims,
                        int                          theResFormat)
{
#ifdef HAVE_FFMPEG
  if (theSrcDims.x() < 1 || theSrcDims.y() < 1 || theResDims.x() < 1 || theResDims.y() < 1
      || theSrcFormat == AV_PIX_FMT_NONE || theResFormat == AV_PIX_FMT_NONE)
  {
    Release();
    return false;
  }
  else if (mySrcDims == theSrcDims && myResDims == theResDims && mySrcFormat == theSrcFormat
           && myResFormat == theResFormat)
  {
    return mySwsContext != nullptr;
  }

  Release();
  mySrcDims    = theSrcDims;
  myResDims    = theResDims;
  mySrcFormat  = theSrcFormat;
  myResFormat  = theResFormat;
  mySwsContext = sws_getContext(theSrcDims.x(),
                                theSrcDims.y(),
                                (AVPixelFormat)theSrcFormat,
                                theResDims.x(),
                                theResDims.y(),
                                (AVPixelFormat)theResFormat,
                                SWS_BICUBIC,
                                nullptr,
                                nullptr,
                                nullptr);
  return mySwsContext != nullptr;
#else
  (void)theSrcDims;
  (void)theSrcFormat;
  (void)theResDims;
  (void)theResFormat;
  return false;
#endif
}

bool Media_Scaler::Convert(const occ::handle<Media_Frame>& theSrc,
                           const occ::handle<Media_Frame>& theRes)
{
  if (theSrc.IsNull() || theSrc->IsEmpty() || theRes.IsNull() || theRes->IsEmpty()
      || theSrc == theRes)
  {
    return false;
  }

  if (!Init(theSrc->Size(), theSrc->Format(), theRes->Size(), theRes->Format()))
  {
    return false;
  }

#ifdef HAVE_FFMPEG
  sws_scale(mySwsContext,
            theSrc->Frame()->data,
            theSrc->Frame()->linesize,
            0,
            theSrc->SizeY(),
            theRes->ChangeFrame()->data,
            theRes->Frame()->linesize);
  return true;
#else
  return false;
#endif
}
