#pragma once

#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

struct AVPacket;

class Media_Packet : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Media_Packet, Standard_Transient)
public:
  Standard_EXPORT Media_Packet();

  Standard_EXPORT ~Media_Packet() override;

  Standard_EXPORT void Unref();

  const AVPacket* Packet() const { return myPacket; }

  AVPacket* ChangePacket() { return myPacket; }

  Standard_EXPORT const uint8_t* Data() const;

  Standard_EXPORT uint8_t* ChangeData();

  Standard_EXPORT int Size() const;

  Standard_EXPORT int64_t Pts() const;

  Standard_EXPORT int64_t Dts() const;

  Standard_EXPORT int64_t Duration() const;

  double DurationSeconds() const { return myDurationSec; }

  void SetDurationSeconds(double theDurationSec) { myDurationSec = theDurationSec; }

  Standard_EXPORT int StreamIndex() const;

  Standard_EXPORT bool IsKeyFrame() const;

  Standard_EXPORT void SetKeyFrame();

protected:
  AVPacket* myPacket;
  double    myDurationSec;
};
