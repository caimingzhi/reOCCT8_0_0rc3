#pragma once


#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

struct AVPacket;

//! AVPacket wrapper - the packet (data chunk for decoding/encoding) holder.
class Media_Packet : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Media_Packet, Standard_Transient)
public:
  //! Empty constructor
  Standard_EXPORT Media_Packet();

  //! Destructor.
  Standard_EXPORT ~Media_Packet() override;

  //! av_packet_unref() wrapper.
  Standard_EXPORT void Unref();

  //! Return packet.
  const AVPacket* Packet() const { return myPacket; }

  //! Return packet.
  AVPacket* ChangePacket() { return myPacket; }

  //! Return data.
  Standard_EXPORT const uint8_t* Data() const;

  //! Return data.
  Standard_EXPORT uint8_t* ChangeData();

  //! Return data size.
  Standard_EXPORT int Size() const;

  //! Return presentation timestamp (PTS).
  Standard_EXPORT int64_t Pts() const;

  //! Return decoding timestamp (DTS).
  Standard_EXPORT int64_t Dts() const;

  //! Return Duration.
  Standard_EXPORT int64_t Duration() const;

  //! Return Duration in seconds.
  double DurationSeconds() const { return myDurationSec; }

  //! Set Duration in seconds.
  void SetDurationSeconds(double theDurationSec) { myDurationSec = theDurationSec; }

  //! Return stream index.
  Standard_EXPORT int StreamIndex() const;

  //! Return TRUE for a key frame.
  Standard_EXPORT bool IsKeyFrame() const;

  //! Mark as key frame.
  Standard_EXPORT void SetKeyFrame();

protected:
  AVPacket* myPacket;      //!< packet
  double    myDurationSec; //!< packet duration in seconds
};

