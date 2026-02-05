#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>

//! This class provides options closure management.
class TDF_ClosureMode
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an object with all modes set to <aMode>.
  Standard_EXPORT TDF_ClosureMode(const bool aMode = true);

  //! Sets the mode "Descendants" to <aStatus>.
  //!
  //! "Descendants" mode means we add to the data set
  //! the children labels of each USER GIVEN label. We
  //! do not do that with the labels found applying
  //! UpToFirstLevel option.
  void Descendants(const bool aStatus);

  //! Returns true if the mode "Descendants" is set.
  bool Descendants() const;

  //! Sets the mode "References" to <aStatus>.
  //!
  //! "References" mode means we add to the data set
  //! the descendants of an attribute, by calling the
  //! attribute method Descendants().
  void References(const bool aStatus);

  //! Returns true if the mode "References" is set.
  bool References() const;

private:
  int myFlags;
};

#define DescendantsFlag 1
#define ReferencesFlag 2

// #define DummyFlag      4

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
