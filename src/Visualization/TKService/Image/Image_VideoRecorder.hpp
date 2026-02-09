#pragma once

#include <Image_PixMap.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>

struct AVFormatContext;
struct AVCodecContext;
struct AVStream;
struct AVCodec;
struct AVFrame;
struct SwsContext;

#ifdef PixelFormat
  #undef PixelFormat
#endif

struct Image_VideoParams
{

  TCollection_AsciiString Format;
  TCollection_AsciiString VideoCodec;
  TCollection_AsciiString PixelFormat;

  int                                                                   Width;
  int                                                                   Height;
  int                                                                   FpsNum;
  int                                                                   FpsDen;
  NCollection_DataMap<TCollection_AsciiString, TCollection_AsciiString> VideoCodecParams;

  Image_VideoParams()
      : Width(0),
        Height(0),
        FpsNum(0),
        FpsDen(1)
  {
  }

  void SetFramerate(const int theNumerator, const int theDenominator)
  {
    FpsNum = theNumerator;
    FpsDen = theDenominator;
  }

  void SetFramerate(const int theValue)
  {
    FpsNum = theValue;
    FpsDen = 1;
  }
};

class Image_VideoRecorder : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Image_VideoRecorder, Standard_Transient)
public:
  Standard_EXPORT Image_VideoRecorder();

  Standard_EXPORT ~Image_VideoRecorder() override;

  Standard_EXPORT void Close();

  Standard_EXPORT bool Open(const char* theFileName, const Image_VideoParams& theParams);

  Image_PixMap& ChangeFrame() { return myImgSrcRgba; }

  int64_t FrameCount() const { return myFrameCount; }

  bool PushFrame() { return writeVideoFrame(false); }

protected:
  Standard_EXPORT TCollection_AsciiString formatAvError(const int theError) const;

  Standard_EXPORT AVCodecContext* getCodecContext() const;

  Standard_EXPORT bool addVideoStream(const Image_VideoParams& theParams, const int theDefCodecId);

  Standard_EXPORT bool openVideoCodec(const Image_VideoParams& theParams);

  Standard_EXPORT bool writeVideoFrame(const bool theToFlush);

protected:
  struct VideoRational
  {
    int num;
    int den;
  };

protected:
  AVFormatContext* myAVContext;
  AVStream*        myVideoStream;
  AVCodec*         myVideoCodec;
  AVCodecContext*  myCodecCtx;
  AVFrame*         myFrame;
  SwsContext*      myScaleCtx;

  Image_PixMap  myImgSrcRgba;
  VideoRational myFrameRate;
  int64_t       myFrameCount;
};
