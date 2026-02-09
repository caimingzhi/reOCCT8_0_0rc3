#pragma once

struct Aspect_XRHapticActionData
{
  float Delay;
  float Duration;
  float Frequency;
  float Amplitude;

  bool IsValid() const
  {
    return Duration > 0.0f && Amplitude > 0.0f && Frequency > 0.0f && Delay >= 0.0f;
  }

  Aspect_XRHapticActionData()
      : Delay(0.0f),
        Duration(0.0f),
        Frequency(0.0f),
        Amplitude(0.0f)
  {
  }
};
