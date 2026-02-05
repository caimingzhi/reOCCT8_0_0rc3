#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>

//! Root class for all commands in BRepLib.
//!
//! Provides :
//!
//! * Managements of the notDone flag.
//!
//! * Catching of exceptions (not implemented).
//!
//! * Logging (not implemented).
class BRepLib_Command
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT virtual ~BRepLib_Command();

  Standard_EXPORT bool IsDone() const;

  //! Raises NotDone if done is false.
  Standard_EXPORT void Check() const;

protected:
  //! Set done to False.
  Standard_EXPORT BRepLib_Command();

  //! Set done to true.
  Standard_EXPORT void Done();

  //! Set done to false.
  Standard_EXPORT void NotDone();

private:
  bool myDone;
};
