#pragma once

#ifdef HAVE_FFMPEG

  #ifndef __STDC_CONSTANT_MACROS
    #define __STDC_CONSTANT_MACROS
  #endif

  #include <stdint.h>

  #include <Standard_WarningsDisable.hpp>
extern "C"
{
  #include <libavcodec/avcodec.h>
  #include <libavformat/avformat.h>
  #include <libavutil/imgutils.h>
  #include <libswscale/swscale.h>
};
  #include <Standard_WarningsRestore.hpp>

  #define FFMPEG_VERSION_4_4 AV_VERSION_INT(58, 0, 0)
  #define FFMPEG_VERSION_5_0 AV_VERSION_INT(59, 0, 0)
  #define FFMPEG_VERSION_6_0 AV_VERSION_INT(60, 0, 0)
  #define FFMPEG_VERSION_7_0 AV_VERSION_INT(61, 0, 0)

  #if LIBAVCODEC_VERSION_INT >= FFMPEG_VERSION_5_0
    #define FFMPEG_NEW_API 1
  #else
    #define FFMPEG_NEW_API 0
  #endif

  #if LIBAVCODEC_VERSION_INT >= AV_VERSION_INT(57, 37, 100)
    #define FFMPEG_HAVE_NEW_DECODE_API 1
  #else
    #define FFMPEG_HAVE_NEW_DECODE_API 0
  #endif

  #if LIBAVFORMAT_VERSION_INT >= AV_VERSION_INT(58, 0, 0)
    #define FFMPEG_HAVE_AVCODEC_PARAMETERS 1
  #else
    #define FFMPEG_HAVE_AVCODEC_PARAMETERS 0
  #endif

  #ifndef AV_ERROR_MAX_STRING_SIZE
    #define AV_ERROR_MAX_STRING_SIZE 64
  #endif

  #ifndef AV_CODEC_FLAG_GLOBAL_HEADER
    #define AV_CODEC_FLAG_GLOBAL_HEADER CODEC_FLAG_GLOBAL_HEADER
  #endif

  #ifndef AV_PIX_FMT_YUV420P
    #define AV_PIX_FMT_YUV420P PIX_FMT_YUV420P
  #endif
  #ifndef AV_PIX_FMT_RGBA
    #define AV_PIX_FMT_RGBA PIX_FMT_RGBA
  #endif
  #ifndef AV_PIX_FMT_RGB24
    #define AV_PIX_FMT_RGB24 PIX_FMT_RGB24
  #endif
  #ifndef AV_PIX_FMT_NONE
    #define AV_PIX_FMT_NONE PIX_FMT_NONE
  #endif
  #ifndef AV_PIX_FMT_YUVJ420P
    #define AV_PIX_FMT_YUVJ420P PIX_FMT_YUVJ420P
  #endif

  #ifndef PIX_FMT_YUV420P
    #define PIX_FMT_YUV420P AV_PIX_FMT_YUV420P
  #endif
  #ifndef PIX_FMT_RGBA
    #define PIX_FMT_RGBA AV_PIX_FMT_RGBA
  #endif
  #ifndef PIX_FMT_RGB24
    #define PIX_FMT_RGB24 AV_PIX_FMT_RGB24
  #endif
  #ifndef PIX_FMT_NONE
    #define PIX_FMT_NONE AV_PIX_FMT_NONE
  #endif
  #ifndef PIX_FMT_YUVJ420P
    #define PIX_FMT_YUVJ420P AV_PIX_FMT_YUVJ420P
  #endif

  #ifndef AV_ROUND_NEAR_INF
    #ifdef AVROUND_NEAR_INF
      #define AV_ROUND_NEAR_INF AVROUND_NEAR_INF
    #else
      #define AV_ROUND_NEAR_INF 5
    #endif
  #endif
  #ifndef AV_ROUND_PASS_MINMAX
    #ifdef AVROUND_PASS_MINMAX
      #define AV_ROUND_PASS_MINMAX AVROUND_PASS_MINMAX
    #else
      #define AV_ROUND_PASS_MINMAX 8192
    #endif
  #endif

  #ifndef AVROUND_NEAR_INF
    #define AVROUND_NEAR_INF AV_ROUND_NEAR_INF
  #endif
  #ifndef AVROUND_PASS_MINMAX
    #define AVROUND_PASS_MINMAX AV_ROUND_PASS_MINMAX
  #endif

inline void ffmpeg_register_all()
{
  #if !FFMPEG_NEW_API
  av_register_all();
  #endif
}

inline AVCodec* ffmpeg_find_encoder(enum AVCodecID id)
{
  #if FFMPEG_NEW_API
  return const_cast<AVCodec*>(avcodec_find_encoder(id));
  #else
  return avcodec_find_encoder(id);
  #endif
}

inline AVCodec* ffmpeg_find_encoder_by_name(const char* name)
{
  #if FFMPEG_NEW_API
  return const_cast<AVCodec*>(avcodec_find_encoder_by_name(name));
  #else
  return avcodec_find_encoder_by_name(name);
  #endif
}

inline AVCodec* ffmpeg_find_decoder(enum AVCodecID id)
{
  #if FFMPEG_NEW_API
  return const_cast<AVCodec*>(avcodec_find_decoder(id));
  #else
  return avcodec_find_decoder(id);
  #endif
}

#endif
