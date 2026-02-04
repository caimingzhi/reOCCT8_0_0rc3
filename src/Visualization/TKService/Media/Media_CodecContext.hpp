#pragma once


#include <Media_Packet.hpp>

struct AVCodec;
struct AVCodecContext;
struct AVStream;
class Media_Frame;

//! AVCodecContext wrapper - the coder/decoder holder.
class Media_CodecContext : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Media_CodecContext, Standard_Transient)
public:
  //! Constructor.
  Standard_EXPORT Media_CodecContext();

  //! Destructor.
  Standard_EXPORT ~Media_CodecContext() override;

  //! Return context.
  AVCodecContext* Context() const { return myCodecCtx; }

  //! Open codec specified within the stream.
  //! @param theStream stream to open
  //! @param thePtsStartBase PTS start in seconds
  //! @param theNbThreads amount of threads to use for AVMEDIA_TYPE_VIDEO stream;
  //!                     -1 means OSD_Parallel::NbLogicalProcessors(),
  //!                      0 means auto by FFmpeg itself
  //!                     >0 means specified number of threads (decoder should support
  //!                     multi-threading to take effect)
  Standard_EXPORT bool Init(const AVStream& theStream,
                            double          thePtsStartBase,
                            int             theNbThreads = -1);

  //! Open codec.
  //! @param theStream stream to open
  //! @param thePtsStartBase PTS start in seconds
  //! @param theNbThreads amount of threads to use for AVMEDIA_TYPE_VIDEO stream;
  //!                     -1 means OSD_Parallel::NbLogicalProcessors(),
  //!                      0 means auto by FFmpeg itself
  //!                     >0 means specified number of threads (decoder should support
  //!                     multi-threading to take effect)
  //! @param theCodecId codec (AVCodecID) to open
  Standard_EXPORT bool Init(const AVStream& theStream,
                            double          thePtsStartBase,
                            int             theNbThreads,
                            int             theCodecId);

  //! Close input.
  Standard_EXPORT void Close();

  //! @return source frame width
  Standard_EXPORT int SizeX() const;

  //! @return source frame height
  Standard_EXPORT int SizeY() const;

  //! Return stream index.
  int StreamIndex() const { return myStreamIndex; }

  //! avcodec_flush_buffers() wrapper.
  Standard_EXPORT void Flush();

  //! Return true if packet belongs to this stream.
  Standard_EXPORT bool CanProcessPacket(const occ::handle<Media_Packet>& thePacket) const;

  //! avcodec_send_packet() wrapper.
  Standard_EXPORT bool SendPacket(const occ::handle<Media_Packet>& thePacket);

  //! avcodec_receive_frame() wrapper.
  Standard_EXPORT bool ReceiveFrame(const occ::handle<Media_Frame>& theFrame);

protected:
  AVCodecContext* myCodecCtx;         //!< codec context
  AVCodec*        myCodec;            //!< opened codec
  double          myPtsStartBase;     //!< starting PTS in context
  double          myPtsStartStream;   //!< starting PTS in the stream
  double          myTimeBase;         //!< stream timebase
  int             myStreamIndex;      //!< stream index
  float           myPixelAspectRatio; //!< pixel aspect ratio
};

