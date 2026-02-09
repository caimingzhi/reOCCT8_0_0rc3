#include <Image_VideoRecorder.hpp>
#include "../Media/Media_FFmpegCompatibility.hpp"

#include <Message.hpp>
#include <Message_Messenger.hpp>

#ifdef HAVE_FFMPEG

  #if (defined(__GNUC__) && (__GNUC__ == 4 && __GNUC_MINOR__ >= 2))
_Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
  #else
Standard_DISABLE_DEPRECATION_WARNINGS
  #endif

  #ifdef PixelFormat
    #undef PixelFormat
  #endif

#endif

  IMPLEMENT_STANDARD_RTTIEXT(Image_VideoRecorder, Standard_Transient)

    Image_VideoRecorder::Image_VideoRecorder()
    : myAVContext(nullptr),
      myVideoStream(nullptr),
      myVideoCodec(nullptr),
      myCodecCtx(nullptr),
      myFrame(nullptr),
      myScaleCtx(nullptr),
      myFrameCount(0)
{
  myFrameRate.num = 1;
  myFrameRate.den = 30;

#ifdef HAVE_FFMPEG

  ffmpeg_register_all();
#endif
}

Image_VideoRecorder::~Image_VideoRecorder()
{
  Close();
}

TCollection_AsciiString Image_VideoRecorder::formatAvError(const int theError) const
{
#ifdef HAVE_FFMPEG
  char anErrBuf[AV_ERROR_MAX_STRING_SIZE] = {};
  av_strerror(theError, anErrBuf, AV_ERROR_MAX_STRING_SIZE);
  return anErrBuf;
#else
  return TCollection_AsciiString(theError);
#endif
}

AVCodecContext* Image_VideoRecorder::getCodecContext() const
{
#ifdef HAVE_FFMPEG
  #if FFMPEG_HAVE_AVCODEC_PARAMETERS
  return myCodecCtx;
  #else
  return myVideoStream != NULL ? myVideoStream->codec : NULL;
  #endif
#else
  return nullptr;
#endif
}

void Image_VideoRecorder::Close()
{
#ifdef HAVE_FFMPEG
  if (myScaleCtx != nullptr)
  {
    sws_freeContext(myScaleCtx);
    myScaleCtx = nullptr;
  }

  if (myAVContext == nullptr)
  {
    myFrameCount = 0;
    return;
  }

  if (myFrameCount != 0)
  {
    av_write_trailer(myAVContext);
    myFrameCount = 0;
  }

  if (myVideoStream != nullptr)
  {
  #if FFMPEG_HAVE_AVCODEC_PARAMETERS
    if (myCodecCtx != nullptr)
    {
      avcodec_free_context(&myCodecCtx);
      myCodecCtx = nullptr;
    }
  #else
    avcodec_close(myVideoStream->codec);
  #endif
    myVideoStream = nullptr;
  }
  if (myFrame != nullptr)
  {
    av_free(myFrame->data[0]);
    av_frame_free(&myFrame);
    myFrame = nullptr;
  }

  if (!(myAVContext->oformat->flags & AVFMT_NOFILE))
  {

    avio_close(myAVContext->pb);
  }

  avformat_free_context(myAVContext);
  myAVContext = nullptr;
#endif
}

bool Image_VideoRecorder::Open(const char* theFileName, const Image_VideoParams& theParams)
{
#ifdef HAVE_FFMPEG
  Close();
  if (theParams.Width <= 0 || theParams.Height <= 0)
  {
    return false;
  }

  avformat_alloc_output_context2(&myAVContext,
                                 nullptr,
                                 theParams.Format.IsEmpty() ? nullptr
                                                            : theParams.Format.ToCString(),
                                 theFileName);
  if (myAVContext == nullptr)
  {
    ::Message::SendFail(
      "ViewerTest_VideoRecorder, could not deduce output format from file extension");
    return false;
  }

  if (!addVideoStream(theParams, myAVContext->oformat->video_codec))
  {
    Close();
    return false;
  }

  if (!openVideoCodec(theParams))
  {
    Close();
    return false;
  }

  #ifdef OCCT_DEBUG
  av_dump_format(myAVContext, 0, theFileName, 1);
  #endif

  if ((myAVContext->oformat->flags & AVFMT_NOFILE) == 0)
  {
    const int aResAv = avio_open(&myAVContext->pb, theFileName, AVIO_FLAG_WRITE);
    if (aResAv < 0)
    {
      ::Message::SendFail(TCollection_AsciiString("Error: could not open '") + theFileName + "', "
                          + formatAvError(aResAv));
      Close();
      return false;
    }
  }

  const int aResAv = avformat_write_header(myAVContext, nullptr);
  if (aResAv < 0)
  {
    ::Message::SendFail(TCollection_AsciiString("Error: can not open output file '") + theFileName
                        + "', " + formatAvError(aResAv));
    Close();
    return false;
  }
#else
  (void)theFileName;
  (void)theParams;
#endif
  return true;
}

bool Image_VideoRecorder::addVideoStream(const Image_VideoParams& theParams,
                                         const int                theDefCodecId)
{
  myFrameRate.num = theParams.FpsNum;
  myFrameRate.den = theParams.FpsDen;

#ifdef HAVE_FFMPEG

  TCollection_AsciiString aCodecName;
  if (!theParams.VideoCodec.IsEmpty())
  {
    myVideoCodec = ffmpeg_find_encoder_by_name(theParams.VideoCodec.ToCString());
    aCodecName   = theParams.VideoCodec;
  }
  else
  {
    myVideoCodec = ffmpeg_find_encoder((AVCodecID)theDefCodecId);
    aCodecName   = avcodec_get_name((AVCodecID)theDefCodecId);
  }
  if (myVideoCodec == nullptr)
  {
    ::Message::SendFail(TCollection_AsciiString("Error: can not find encoder for ") + aCodecName);
    return false;
  }

  const AVCodecID aCodecId = myVideoCodec->id;
  myVideoStream            = avformat_new_stream(myAVContext, myVideoCodec);
  if (myVideoStream == nullptr)
  {
    ::Message::SendFail("Error: can not allocate stream");
    return false;
  }
  myVideoStream->id = myAVContext->nb_streams - 1;

  #if FFMPEG_HAVE_AVCODEC_PARAMETERS

  myCodecCtx = avcodec_alloc_context3(myVideoCodec);
  if (myCodecCtx == nullptr)
  {
    ::Message::SendFail("Error: can not allocate codec context");
    return false;
  }
  AVCodecContext* aCodecCtx = myCodecCtx;
  #else

  AVCodecContext* aCodecCtx = myVideoStream->codec;
  #endif

  aCodecCtx->codec_id = aCodecId;

  aCodecCtx->width  = theParams.Width;
  aCodecCtx->height = theParams.Height;

  aCodecCtx->time_base.den = myFrameRate.num;
  aCodecCtx->time_base.num = myFrameRate.den;
  aCodecCtx->gop_size      = 12;

  if (myAVContext->oformat->flags & AVFMT_GLOBALHEADER)
  {
    aCodecCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
  }

  #if FFMPEG_HAVE_AVCODEC_PARAMETERS

  if (avcodec_parameters_from_context(myVideoStream->codecpar, aCodecCtx) < 0)
  {
    ::Message::SendFail("Error: can not copy codec parameters to stream");
    return false;
  }
  #endif
  return true;
#else
  (void)theParams;
  (void)theDefCodecId;
  return false;
#endif
}

bool Image_VideoRecorder::openVideoCodec(const Image_VideoParams& theParams)
{
#ifdef HAVE_FFMPEG
  AVDictionary*   anOptions = nullptr;
  AVCodecContext* aCodecCtx = getCodecContext();

  if (aCodecCtx == nullptr)
  {
    ::Message::SendFail("Error: codec context is not available");
    return false;
  }

  aCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;

  if (myVideoCodec == ffmpeg_find_encoder_by_name("mpeg2video"))
  {

    aCodecCtx->max_b_frames = 2;
    aCodecCtx->bit_rate     = 6000000;
  }
  else if (myVideoCodec == ffmpeg_find_encoder_by_name("mpeg4"))
  {
  }
  else if (myVideoCodec == ffmpeg_find_encoder_by_name("mjpeg"))
  {
    aCodecCtx->pix_fmt = AV_PIX_FMT_YUVJ420P;
    aCodecCtx->qmin = aCodecCtx->qmax = 5;
  }
  else if (myVideoCodec == ffmpeg_find_encoder_by_name("huffyuv"))
  {
    aCodecCtx->pix_fmt = AV_PIX_FMT_RGB24;
  }
  else if (myVideoCodec == ffmpeg_find_encoder_by_name("png"))
  {
    aCodecCtx->pix_fmt           = AV_PIX_FMT_RGB24;
    aCodecCtx->compression_level = 9;
  }
  else if (myVideoCodec == ffmpeg_find_encoder_by_name("h264")
           || myVideoCodec == ffmpeg_find_encoder_by_name("libx264"))
  {

    av_dict_set(&anOptions, "crf", "20", 0);
    av_dict_set(&anOptions, "preset", "slow", 0);
  }
  else if (myVideoCodec == ffmpeg_find_encoder_by_name("vp8")
           || myVideoCodec == ffmpeg_find_encoder_by_name("vp9"))
  {
    av_dict_set(&anOptions, "crf", "20", 0);
  }

  if (!theParams.PixelFormat.IsEmpty())
  {
    const AVPixelFormat aPixFormat = av_get_pix_fmt(theParams.PixelFormat.ToCString());
    if (aPixFormat == AV_PIX_FMT_NONE)
    {
      ::Message::SendFail(
        TCollection_AsciiString("Error: unknown pixel format has been specified '")
        + theParams.PixelFormat + "'");
      return false;
    }

    aCodecCtx->pix_fmt = aPixFormat;
    for (NCollection_DataMap<TCollection_AsciiString, TCollection_AsciiString>::Iterator aParamIter(
           theParams.VideoCodecParams);
         aParamIter.More();
         aParamIter.Next())
    {
      av_dict_set(&anOptions, aParamIter.Key().ToCString(), aParamIter.Value().ToCString(), 0);
    }
  }

  int aResAv = avcodec_open2(aCodecCtx, myVideoCodec, &anOptions);
  if (anOptions != nullptr)
  {
    av_dict_free(&anOptions);
  }
  if (aResAv < 0)
  {
    ::Message::SendFail(TCollection_AsciiString("Error: can not open video codec, ")
                        + formatAvError(aResAv));
    return false;
  }

  myFrame = av_frame_alloc();
  if (myFrame == nullptr)
  {
    ::Message::SendFail("Error: can not allocate video frame");
    return false;
  }

  aResAv = av_image_alloc(myFrame->data,
                          myFrame->linesize,
                          aCodecCtx->width,
                          aCodecCtx->height,
                          aCodecCtx->pix_fmt,
                          1);
  if (aResAv < 0)
  {
    memset(myFrame->data, 0, sizeof(myFrame->data));
    memset(myFrame->linesize, 0, sizeof(myFrame->linesize));
    ::Message::SendFail(TCollection_AsciiString("Error: can not allocate picture ")
                        + aCodecCtx->width + "x" + aCodecCtx->height + ", "
                        + formatAvError(aResAv));
    return false;
  }

  myFrame->format = aCodecCtx->pix_fmt;
  myFrame->width  = aCodecCtx->width;
  myFrame->height = aCodecCtx->height;

  const size_t aStride = aCodecCtx->width + 16 - (aCodecCtx->width % 16);
  if (!myImgSrcRgba.InitZero(Image_Format_RGBA, aCodecCtx->width, aCodecCtx->height, aStride))
  {
    ::Message::SendFail(TCollection_AsciiString("Error: can not allocate RGBA32 picture ")
                        + aCodecCtx->width + "x" + aCodecCtx->height);
    return false;
  }

  myScaleCtx = sws_getContext(aCodecCtx->width,
                              aCodecCtx->height,
                              AV_PIX_FMT_RGBA,
                              aCodecCtx->width,
                              aCodecCtx->height,
                              aCodecCtx->pix_fmt,
                              SWS_BICUBIC,
                              nullptr,
                              nullptr,
                              nullptr);
  if (myScaleCtx == nullptr)
  {
    ::Message::SendFail("Error: can not initialize the conversion context");
    return false;
  }
  return true;
#else
  (void)theParams;
  return false;
#endif
}

bool Image_VideoRecorder::writeVideoFrame(const bool theToFlush)
{
#ifdef HAVE_FFMPEG
  if (myImgSrcRgba.Format() != Image_Format_RGBA)
  {
    throw Standard_ProgramError("Image_VideoRecorder, unsupported image format");
  }

  int             aResAv    = 0;
  AVCodecContext* aCodecCtx = getCodecContext();
  if (!theToFlush)
  {
    uint8_t* aSrcData[4]     = {(uint8_t*)myImgSrcRgba.ChangeData(), nullptr, nullptr, nullptr};
    int      aSrcLinesize[4] = {(int)myImgSrcRgba.SizeRowBytes(), 0, 0, 0};
    sws_scale(myScaleCtx,
              aSrcData,
              aSrcLinesize,
              0,
              aCodecCtx->height,
              myFrame->data,
              myFrame->linesize);
  }

  #if FFMPEG_HAVE_NEW_DECODE_API

  if (!theToFlush)
  {
    myFrame->pts = myFrameCount;
    aResAv       = avcodec_send_frame(aCodecCtx, myFrame);
  }
  else
  {
    aResAv = avcodec_send_frame(aCodecCtx, nullptr);
  }

  if (aResAv < 0)
  {
    ::Message::SendFail(TCollection_AsciiString("Error: can not send frame to encoder, ")
                        + formatAvError(aResAv));
    return false;
  }

  while (aResAv >= 0)
  {
    AVPacket* aPacket = av_packet_alloc();
    aResAv            = avcodec_receive_packet(aCodecCtx, aPacket);
    if (aResAv == AVERROR(EAGAIN) || aResAv == AVERROR_EOF)
    {
      av_packet_free(&aPacket);
      break;
    }
    else if (aResAv < 0)
    {
      av_packet_free(&aPacket);
      ::Message::SendFail(TCollection_AsciiString("Error: can not encode video frame, ")
                          + formatAvError(aResAv));
      return false;
    }

    aPacket->pts = av_rescale_q_rnd(aPacket->pts,
                                    aCodecCtx->time_base,
                                    myVideoStream->time_base,
                                    AVRounding(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
    aPacket->dts = av_rescale_q_rnd(aPacket->dts,
                                    aCodecCtx->time_base,
                                    myVideoStream->time_base,
                                    AVRounding(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
    aPacket->duration =
      av_rescale_q(aPacket->duration, aCodecCtx->time_base, myVideoStream->time_base);
    aPacket->stream_index = myVideoStream->index;

    aResAv = av_interleaved_write_frame(myAVContext, aPacket);
    av_packet_free(&aPacket);

    if (aResAv < 0)
    {
      ::Message::SendFail(TCollection_AsciiString("Error: can not write video frame, ")
                          + formatAvError(aResAv));
      return false;
    }
  }
  #else

  AVPacket aPacket;
  memset(&aPacket, 0, sizeof(aPacket));
  av_init_packet(&aPacket);
  {

    if (!theToFlush)
    {
      myFrame->pts = myFrameCount;
    }
    int isGotPacket = 0;
    aResAv = avcodec_encode_video2(aCodecCtx, &aPacket, theToFlush ? NULL : myFrame, &isGotPacket);
    if (aResAv < 0)
    {
      ::Message::SendFail(TCollection_AsciiString("Error: can not encode video frame, ")
                          + formatAvError(aResAv));
      return false;
    }

    if (isGotPacket)
    {
      const AVRational& aTimeBase = aCodecCtx->time_base;

      aPacket.pts          = av_rescale_q_rnd(aPacket.pts,
                                     aTimeBase,
                                     myVideoStream->time_base,
                                     AVRounding(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
      aPacket.dts          = av_rescale_q_rnd(aPacket.dts,
                                     aTimeBase,
                                     myVideoStream->time_base,
                                     AVRounding(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
      aPacket.duration     = av_rescale_q(aPacket.duration, aTimeBase, myVideoStream->time_base);
      aPacket.stream_index = myVideoStream->index;

      aResAv = av_interleaved_write_frame(myAVContext, &aPacket);
    }
    else
    {
      aResAv = 0;
    }
  }

  if (aResAv < 0)
  {
    ::Message::SendFail(TCollection_AsciiString("Error: can not write video frame, ")
                        + formatAvError(aResAv));
    return false;
  }
  #endif

  ++myFrameCount;
  return true;
#else
  (void)theToFlush;
  return false;
#endif
}
