#pragma once

//! Haptic output XR action data.
struct Aspect_XRHapticActionData
{
  float Delay;     //!< delay in seconds before start
  float Duration;  //!< duration in seconds
  float Frequency; //!< vibration frequency
  float Amplitude; //!< vibration amplitude

  //! Return TRUE if data is not empty.
  bool IsValid() const
  {
    return Duration > 0.0f && Amplitude > 0.0f && Frequency > 0.0f && Delay >= 0.0f;
  }

  //! Empty constructor.
  Aspect_XRHapticActionData()
      : Delay(0.0f),
        Duration(0.0f),
        Frequency(0.0f),
        Amplitude(0.0f)
  {
  }
};
