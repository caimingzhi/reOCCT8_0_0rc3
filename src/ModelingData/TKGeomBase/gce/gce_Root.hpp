#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gce_ErrorType.hpp>
#include <Standard_Boolean.hpp>

// resolve name collisions with X11 headers
#ifdef Status
  #undef Status
#endif

//! This class implements the common services for
//! all classes of gce which report error.
class gce_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns true if the construction is successful.
  bool IsDone() const;

  //! Returns the status of the construction:
  //! -   gce_Done, if the construction is successful, or
  //! -   another value of the gce_ErrorType enumeration
  //! indicating why the construction failed.
  gce_ErrorType Status() const;

protected:
  gce_ErrorType TheError;
};

inline bool gce_Root::IsDone() const
{
  return TheError == gce_Done;
}

inline gce_ErrorType gce_Root::Status() const
{
  return TheError;
}
