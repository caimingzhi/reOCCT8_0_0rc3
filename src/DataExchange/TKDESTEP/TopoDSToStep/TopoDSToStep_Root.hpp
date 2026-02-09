#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>

class TopoDSToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT double& Tolerance();

  Standard_EXPORT bool IsDone() const;

protected:
  Standard_EXPORT TopoDSToStep_Root();

  double toler;
  bool   done;
};
