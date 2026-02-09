#pragma once

#include <NCollection_DataMap.hpp>

class SelectMgr_ToleranceMap
{
public:
  Standard_EXPORT SelectMgr_ToleranceMap();

  Standard_EXPORT ~SelectMgr_ToleranceMap();

  Standard_EXPORT void Add(const int& theTolerance);

  Standard_EXPORT void Decrement(const int& theTolerance);

  int Tolerance() const
  {
    if (myLargestKey < 0)
    {
      return 2;
    }
    return myCustomTolerance < 0 ? myLargestKey : myLargestKey + myCustomTolerance;
  }

  void SetCustomTolerance(const int theTolerance) { myCustomTolerance = theTolerance; }

  void ResetDefaults() { myCustomTolerance = -1; }

  int CustomTolerance() const { return myCustomTolerance; }

  bool IsCustomTolSet() const { return myCustomTolerance > 0; }

private:
  NCollection_DataMap<int, int> myTolerances;
  int                           myLargestKey;
  int                           myCustomTolerance;
};
