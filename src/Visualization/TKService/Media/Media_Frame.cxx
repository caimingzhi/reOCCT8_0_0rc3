#ifndef __STDC_CONSTANT_MACROS
  #define __STDC_CONSTANT_MACROS
#endif

#include <Media_Frame.hpp>

#include <Media_Scaler.hpp>

#ifdef HAVE_FFMPEG
  #include <Standard_WarningsDisable.hpp>
extern "C"
{
  #include <libavcodec/avcodec.h>
  #include <libavutil/imgutils.h>
};
  #include <Standard_WarningsRestore.hpp>
#endif

IMPLEMENT_STANDARD_RTTIEXT(Media_Frame, Standard_Transient)

Image_Format Media_Frame::FormatFFmpeg2Occt(int theFormat)
{
#ifdef HAVE_FFMPEG
  switch (theFormat)
  {
    case AV_PIX_FMT_RGBA:
      return Image_Format_RGBA;
    case AV_PIX_FMT_BGRA:
      return Image_Format_BGRA;
    case AV_PIX_FMT_RGB0:
      return Image_Format_RGB32;
    case AV_PIX_FMT_BGR0:
      return Image_Format_BGR32;
    case AV_PIX_FMT_RGB24:
      return Image_Format_RGB;
    case AV_PIX_FMT_BGR24:
      return Image_Format_BGR;
    case AV_PIX_FMT_GRAY8:
      return Image_Format_Gray;
    case AV_PIX_FMT_GRAY16:
      return Image_Format_Gray16;
    default:
      return Image_Format_UNKNOWN;
  }
#else
  (void)theFormat;
  return Image_Format_UNKNOWN;
#endif
}

int Media_Frame::FormatOcct2FFmpeg(Image_Format theFormat)
{
#ifdef HAVE_FFMPEG
  switch (theFormat)
  {
    case Image_Format_RGBA:
      return AV_PIX_FMT_RGBA;
    case Image_Format_BGRA:
      return AV_PIX_FMT_BGRA;
    case Image_Format_RGB32:
      return AV_PIX_FMT_RGB0;
    case Image_Format_BGR32:
      return AV_PIX_FMT_BGR0;
    case Image_Format_RGB:
      return AV_PIX_FMT_RGB24;
    case Image_Format_BGR:
      return AV_PIX_FMT_BGR24;
    case Image_Format_Gray:
      return AV_PIX_FMT_GRAY8;
    case Image_Format_Alpha:
      return AV_PIX_FMT_GRAY8;
    case Image_Format_Gray16:
      return AV_PIX_FMT_GRAY16;
    case Image_Format_GrayF:
    case Image_Format_AlphaF:
    case Image_Format_RGF:
    case Image_Format_RGBAF:
    case Image_Format_RGBF:
    case Image_Format_BGRAF:
    case Image_Format_BGRF:
    case Image_Format_GrayF_half:
    case Image_Format_RGF_half:
    case Image_Format_RGBAF_half:
    case Image_Format_UNKNOWN:
      return AV_PIX_FMT_NONE;
  }
  return AV_PIX_FMT_NONE;
#else
  (void)theFormat;
  return 0;
#endif
}

Media_Frame::Media_Frame()
    : myFrame(nullptr),
      myFramePts(0.0),
      myPixelRatio(1.0f),
      myIsLocked(false)
{
#ifdef HAVE_FFMPEG
  myFrame = av_frame_alloc();
#endif
  Unref();
}

Media_Frame::~Media_Frame()
{
#ifdef HAVE_FFMPEG
  av_frame_free(&myFrame);
#endif
}

void Media_Frame::Unref()
{
#ifdef HAVE_FFMPEG
  av_frame_unref(myFrame);
#endif
}

bool Media_Frame::IsFullRangeYUV() const
{
#ifdef HAVE_FFMPEG
  return Format() == AV_PIX_FMT_YUVJ420P || myFrame->color_range == AVCOL_RANGE_JPEG;
#else
  return true;
#endif
}

void Media_Frame::Swap(const occ::handle<Media_Frame>& theFrame1,
                       const occ::handle<Media_Frame>& theFrame2)
{
  std::swap(theFrame1->myFrame, theFrame2->myFrame);
}

bool Media_Frame::IsEmpty() const
{
#ifdef HAVE_FFMPEG
  return myFrame->format == -1;
#else
  return true;
#endif
}

int Media_Frame::SizeX() const
{
#ifdef HAVE_FFMPEG
  return myFrame->width;
#else
  return 0;
#endif
}

int Media_Frame::SizeY() const
{
#ifdef HAVE_FFMPEG
  return myFrame->height;
#else
  return 0;
#endif
}

int Media_Frame::Format() const
{
#ifdef HAVE_FFMPEG
  return myFrame->format;
#else
  return 0;
#endif
}

uint8_t* Media_Frame::Plane(int thePlaneId) const
{
#ifdef HAVE_FFMPEG
  return myFrame->data[thePlaneId];
#else
  (void)thePlaneId;
  return nullptr;
#endif
}

int Media_Frame::LineSize(int thePlaneId) const
{
#ifdef HAVE_FFMPEG
  return myFrame->linesize[thePlaneId];
#else
  (void)thePlaneId;
  return 0;
#endif
}

int64_t Media_Frame::BestEffortTimestamp() const
{
#ifdef HAVE_FFMPEG
  return myFrame->best_effort_timestamp;
#else
  return 0;
#endif
}

bool Media_Frame::InitWrapper(const occ::handle<Image_PixMap>& thePixMap)
{
  Unref();
  if (thePixMap.IsNull())
  {
    return false;
  }

#ifdef HAVE_FFMPEG
  myFrame->format = FormatOcct2FFmpeg(thePixMap->Format());
  if (myFrame->format == AV_PIX_FMT_NONE)
  {
    return false;
  }

  myFrame->width       = (int)thePixMap->SizeX();
  myFrame->height      = (int)thePixMap->SizeY();
  myFrame->data[0]     = (uint8_t*)thePixMap->ChangeData();
  myFrame->linesize[0] = (int)thePixMap->SizeRowBytes();
  for (int aPlaneIter = 1; aPlaneIter < AV_NUM_DATA_POINTERS; ++aPlaneIter)
  {
    myFrame->data[aPlaneIter]     = nullptr;
    myFrame->linesize[aPlaneIter] = 0;
  }
  return true;
#else
  return false;
#endif
}
