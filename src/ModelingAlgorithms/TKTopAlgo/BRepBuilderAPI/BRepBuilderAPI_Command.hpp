#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>

class BRepBuilderAPI_Command
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT virtual ~BRepBuilderAPI_Command();

  Standard_EXPORT virtual bool IsDone() const;

  Standard_EXPORT void Check() const;

protected:
  Standard_EXPORT BRepBuilderAPI_Command();

  Standard_EXPORT void Done();

  Standard_EXPORT void NotDone();

private:
  bool myDone;
};
