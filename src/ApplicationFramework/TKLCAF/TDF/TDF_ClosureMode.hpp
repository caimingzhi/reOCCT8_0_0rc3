#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>

class TDF_ClosureMode
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TDF_ClosureMode(const bool aMode = true);

  void Descendants(const bool aStatus);

  bool Descendants() const;

  void References(const bool aStatus);

  bool References() const;

private:
  int myFlags;
};

#define DescendantsFlag 1
#define ReferencesFlag 2

inline void TDF_ClosureMode::Descendants(const bool aStatus)
{
  myFlags = (aStatus) ? (myFlags | DescendantsFlag) : (myFlags & ~DescendantsFlag);
}

inline bool TDF_ClosureMode::Descendants() const
{
  return (myFlags & DescendantsFlag) != 0;
}

inline void TDF_ClosureMode::References(const bool aStatus)
{
  myFlags = (aStatus) ? (myFlags | ReferencesFlag) : (myFlags & ~ReferencesFlag);
}

inline bool TDF_ClosureMode::References() const
{
  return (myFlags & ReferencesFlag) != 0;
}
