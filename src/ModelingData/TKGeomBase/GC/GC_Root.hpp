#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gce_ErrorType.hpp>

#ifdef Status
  #undef Status
#endif

class GC_Root
{
public:
  DEFINE_STANDARD_ALLOC

  bool IsDone() const;

  gce_ErrorType Status() const;

protected:
  gce_ErrorType TheError;
};

inline bool GC_Root::IsDone() const
{
  return TheError == gce_Done;
}

inline gce_ErrorType GC_Root::Status() const
{
  return TheError;
}
