#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gce_ErrorType.hpp>

#ifdef Status
  #undef Status
#endif

class GCE2d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  bool IsDone() const;

  gce_ErrorType Status() const;

protected:
  gce_ErrorType TheError;
};

inline bool GCE2d_Root::IsDone() const
{
  return TheError == gce_Done;
}

inline gce_ErrorType GCE2d_Root::Status() const
{
  return TheError;
}
