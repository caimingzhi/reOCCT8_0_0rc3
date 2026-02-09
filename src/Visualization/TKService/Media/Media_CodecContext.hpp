#pragma once

#include <Media_Packet.hpp>

struct AVCodec;
struct AVCodecContext;
struct AVStream;
class Media_Frame;

class Media_CodecContext : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Media_CodecContext, Standard_Transient)
public:
  Standard_EXPORT Media_CodecContext();

  Standard_EXPORT ~Media_CodecContext() override;

  AVCodecContext* Context() const { return myCodecCtx; }

  Standard_EXPORT bool Init(const AVStream& theStream,
                            double          thePtsStartBase,
                            int             theNbThreads = -1);

  Standard_EXPORT bool Init(const AVStream& theStream,
                            double          thePtsStartBase,
                            int             theNbThreads,
                            int             theCodecId);

  Standard_EXPORT void Close();

  Standard_EXPORT int SizeX() const;

  Standard_EXPORT int SizeY() const;

  int StreamIndex() const { return myStreamIndex; }

  Standard_EXPORT void Flush();

  Standard_EXPORT bool CanProcessPacket(const occ::handle<Media_Packet>& thePacket) const;

  Standard_EXPORT bool SendPacket(const occ::handle<Media_Packet>& thePacket);

  Standard_EXPORT bool ReceiveFrame(const occ::handle<Media_Frame>& theFrame);

protected:
  AVCodecContext* myCodecCtx;
  AVCodec*        myCodec;
  double          myPtsStartBase;
  double          myPtsStartStream;
  double          myTimeBase;
  int             myStreamIndex;
  float           myPixelAspectRatio;
};
