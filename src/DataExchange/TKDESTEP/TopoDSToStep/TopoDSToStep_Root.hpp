#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>

//! This class implements the common services for
//! all classes of TopoDSToStep which report error.
class TopoDSToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns (modifiable) the tolerance to be used for writing
  //! If not set, starts at 0.0001
  Standard_EXPORT double& Tolerance();

  Standard_EXPORT bool IsDone() const;

protected:
  Standard_EXPORT TopoDSToStep_Root();

  double toler;
  bool   done;
};

