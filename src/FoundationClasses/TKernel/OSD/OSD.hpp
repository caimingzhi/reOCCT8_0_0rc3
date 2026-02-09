#pragma once

#include <Standard.hpp>
#include <Standard_PCharacter.hpp>

enum OSD_SignalMode
{
  OSD_SignalMode_AsIs,
  OSD_SignalMode_Set,
  OSD_SignalMode_SetUnhandled,

  OSD_SignalMode_Unset
};

class OSD
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void SetSignal(OSD_SignalMode theSignalMode, bool theFloatingSignal);

  static void SetSignal(const bool theFloatingSignal = true)
  {
    SetSignal(OSD_SignalMode_Set, theFloatingSignal);
  }

  Standard_EXPORT static void SetThreadLocalSignal(OSD_SignalMode theSignalMode,
                                                   bool           theFloatingSignal);

  Standard_EXPORT static void SetFloatingSignal(bool theFloatingSignal);

  Standard_EXPORT static OSD_SignalMode SignalMode();

  Standard_EXPORT static bool ToCatchFloatingSignals();

  Standard_EXPORT static void SecSleep(const int theSeconds);

  Standard_EXPORT static void MilliSecSleep(const int theMilliseconds);

  Standard_EXPORT static bool RealToCString(const double aReal, Standard_PCharacter& aString);

  Standard_EXPORT static bool CStringToReal(const char* aString, double& aReal);

  Standard_EXPORT static void ControlBreak();

  Standard_EXPORT static int SignalStackTraceLength();

  Standard_EXPORT static void SetSignalStackTraceLength(int theLength);
};
