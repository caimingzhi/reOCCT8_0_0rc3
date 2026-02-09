#pragma once

#include <TCollection_AsciiString.hpp>

class OSD_MemInfo
{

public:
  enum Counter
  {
    MemPrivate = 0,
    MemVirtual,
    MemWorkingSet,
    MemWorkingSetPeak,
    MemSwapUsage,
    MemSwapUsagePeak,
    MemHeapUsage,
    MemCounter_NB
  };

public:
  Standard_EXPORT OSD_MemInfo(const bool theImmediateUpdate = true);

  bool IsActive(const OSD_MemInfo::Counter theCounter) const
  {
    return myActiveCounters[theCounter];
  }

  Standard_EXPORT void SetActive(const bool theActive);

  void SetActive(const OSD_MemInfo::Counter theCounter, const bool theActive)
  {
    myActiveCounters[theCounter] = theActive;
  }

  Standard_EXPORT void Clear();

  Standard_EXPORT void Update();

  Standard_EXPORT TCollection_AsciiString ToString() const;

  Standard_EXPORT size_t Value(const OSD_MemInfo::Counter theCounter) const;

  Standard_EXPORT size_t ValueMiB(const OSD_MemInfo::Counter theCounter) const;

  Standard_EXPORT double ValuePreciseMiB(const OSD_MemInfo::Counter theCounter) const;

public:
  Standard_EXPORT static TCollection_AsciiString PrintInfo();

protected:
  bool hasValue(const OSD_MemInfo::Counter theCounter) const
  {
    return IsActive(theCounter) && myCounters[theCounter] != size_t(-1);
  }

private:
  size_t myCounters[MemCounter_NB];
  bool   myActiveCounters[MemCounter_NB];
};
