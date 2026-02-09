#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>

class BRepLib_Command
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT virtual ~BRepLib_Command();

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT void Check() const;

protected:
  Standard_EXPORT BRepLib_Command();

  Standard_EXPORT void Done();

  Standard_EXPORT void NotDone();

private:
  bool myDone;
};
