#ifndef __STDC_CONSTANT_MACROS
  #define __STDC_CONSTANT_MACROS
#endif

#include <Media_Packet.hpp>

#ifdef HAVE_FFMPEG
  #include <Standard_WarningsDisable.hpp>
extern "C"
{
  #include <libavcodec/avcodec.h>
};
  #include <Standard_WarningsRestore.hpp>
#endif

IMPLEMENT_STANDARD_RTTIEXT(Media_Packet, Standard_Transient)

//=================================================================================================

Media_Packet::Media_Packet()
    : myPacket(nullptr)
{
#ifdef HAVE_FFMPEG
  myPacket = av_packet_alloc();
#endif
}

//=================================================================================================

Media_Packet::~Media_Packet()
{
#ifdef HAVE_FFMPEG
  av_packet_free(&myPacket);
#endif
}

//=================================================================================================

void Media_Packet::Unref()
{
#ifdef HAVE_FFMPEG
  av_packet_unref(myPacket);
#endif
}

//=================================================================================================

const uint8_t* Media_Packet::Data() const
{
#ifdef HAVE_FFMPEG
  return myPacket->data;
#else
  return nullptr;
#endif
}

//=================================================================================================

uint8_t* Media_Packet::ChangeData()
{
#ifdef HAVE_FFMPEG
  return myPacket->data;
#else
  return nullptr;
#endif
}

//=================================================================================================

int Media_Packet::Size() const
{
#ifdef HAVE_FFMPEG
  return myPacket->size;
#else
  return 0;
#endif
}

//=================================================================================================

int64_t Media_Packet::Pts() const
{
#ifdef HAVE_FFMPEG
  return myPacket->pts;
#else
  return 0;
#endif
}

//=================================================================================================

int64_t Media_Packet::Dts() const
{
#ifdef HAVE_FFMPEG
  return myPacket->dts;
#else
  return 0;
#endif
}

//=================================================================================================

int64_t Media_Packet::Duration() const
{
#ifdef HAVE_FFMPEG
  return myPacket->duration;
#else
  return 0;
#endif
}

//=================================================================================================

int Media_Packet::StreamIndex() const
{
#ifdef HAVE_FFMPEG
  return myPacket->stream_index;
#else
  return 0;
#endif
}

//=================================================================================================

bool Media_Packet::IsKeyFrame() const
{
#ifdef HAVE_FFMPEG
  return (myPacket->flags & AV_PKT_FLAG_KEY) != 0;
#else
  return false;
#endif
}

//=================================================================================================

void Media_Packet::SetKeyFrame()
{
#ifdef HAVE_FFMPEG
  myPacket->flags |= AV_PKT_FLAG_KEY;
#endif
}
