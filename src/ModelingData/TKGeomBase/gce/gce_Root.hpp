#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gce_ErrorType.hpp>
#include <Standard_Boolean.hpp>

#ifdef Status
  #undef Status
#endif

class gce_Root
{
public:
  DEFINE_STANDARD_ALLOC

  bool IsDone() const;

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
