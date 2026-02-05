#ifndef __STDC_CONSTANT_MACROS
  #define __STDC_CONSTANT_MACROS
#endif

#include <Graphic3d_MediaTexture.hpp>

#include <Graphic3d_TextureParams.hpp>
#include <Media_Frame.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>

#ifdef HAVE_FFMPEG
  #include <Standard_WarningsDisable.hpp>
extern "C"
{
  #include <libavcodec/avcodec.h>
  #include <libavutil/imgutils.h>
};
  #include <Standard_WarningsRestore.hpp>
#endif

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_MediaTexture, Graphic3d_Texture2D)

//=================================================================================================

Graphic3d_MediaTexture::Graphic3d_MediaTexture(std::mutex& theMutex, int thePlane)
    : Graphic3d_Texture2D("", Graphic3d_TypeOfTexture_2D),
      myMutex(theMutex),
      myPlane(thePlane)
{
  myParams->SetModulate(false);
  myParams->SetRepeat(false);
  myParams->SetFilter(Graphic3d_TOTF_BILINEAR);
  myParams->SetTextureUnit(Graphic3d_TextureUnit(int(Graphic3d_TextureUnit_0) + thePlane));
}

//=================================================================================================

occ::handle<Image_PixMap> Graphic3d_MediaTexture::GetImage(
  const occ::handle<Image_SupportedFormats>&)
{
  std::lock_guard<std::mutex> aLock(myMutex);

  if (myFrame.IsNull() || myFrame->IsLocked() || myFrame->IsEmpty() || myFrame->SizeX() < 1
      || myFrame->SizeY() < 1)
  {
    return occ::handle<Image_PixMap>();
  }

  if (myPixMapWrapper.IsNull())
  {
    myPixMapWrapper = new Image_PixMap();
  }

#ifdef HAVE_FFMPEG
  const AVFrame*     aFrame    = myFrame->Frame();
  const Image_Format anOcctFmt = Media_Frame::FormatFFmpeg2Occt(myFrame->Format());
  if (anOcctFmt != Image_Format_UNKNOWN)
  {
    if (myPlane != 0
        || !myPixMapWrapper->InitWrapper(anOcctFmt,
                                         aFrame->data[0],
                                         aFrame->width,
                                         aFrame->height,
                                         aFrame->linesize[0]))
    {
      return occ::handle<Image_PixMap>();
    }
    return myPixMapWrapper;
  }
  else if (myFrame->Format() == AV_PIX_FMT_YUV420P || myFrame->Format() == AV_PIX_FMT_YUVJ420P)
  {
    const NCollection_Vec2<int> aSize = myPlane == 0 ? myFrame->Size() : myFrame->Size() / 2;
    if (myPlane > 3
        || !myPixMapWrapper->InitWrapper(Image_Format_Gray,
                                         aFrame->data[myPlane],
                                         aSize.x(),
                                         aSize.y(),
                                         aFrame->linesize[myPlane]))
    {
      return occ::handle<Image_PixMap>();
    }
    return myPixMapWrapper;
  }
#endif

  return occ::handle<Image_PixMap>();
}
