#pragma once

#include <Standard_Macro.hpp>
#include <TCollection_AsciiString.hpp>

class OSD_PerfMeter
{
public:
  Standard_EXPORT OSD_PerfMeter() = default;

  Standard_EXPORT OSD_PerfMeter(const TCollection_AsciiString& theMeterName,
                                const bool                     theToAutoStart = true);

  Standard_EXPORT ~OSD_PerfMeter();

  Standard_EXPORT void Init(const TCollection_AsciiString& theMeterName);

  Standard_EXPORT void Start() const;

  Standard_EXPORT void Stop() const;

  Standard_EXPORT double Elapsed() const;

  Standard_EXPORT void Kill() const;

  Standard_EXPORT TCollection_AsciiString Print() const;

  Standard_EXPORT static TCollection_AsciiString PrintALL();

  Standard_EXPORT static void ResetALL();

private:
  TCollection_AsciiString myMeterName;
};
