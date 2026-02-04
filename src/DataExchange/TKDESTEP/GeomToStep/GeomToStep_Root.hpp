#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <StepData_Factors.hpp>

#include <Standard_Boolean.hpp>

//! This class implements the common services for
//! all classes of GeomToStep which report error.
class GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT bool IsDone() const;

protected:
  bool done;
};

