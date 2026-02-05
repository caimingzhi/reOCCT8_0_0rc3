#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class StepData_Protocol;

//! Gives basic data definition for Step Interface.
//! Any class of a data model described in EXPRESS Language
//! is candidate to be managed by a Step Interface
class StepData
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns the recorded HeaderProtocol, which can be :
  //! - a Null Handle if no Header Protocol was yet defined
  //! - a simple Protocol if only one was defined
  //! - a FileProtocol if more than one Protocol was yet defined
  Standard_EXPORT static occ::handle<StepData_Protocol> HeaderProtocol();

  //! Adds a new Header Protocol to the Header Definition
  Standard_EXPORT static void AddHeaderProtocol(const occ::handle<StepData_Protocol>& headerproto);

  //! Prepares General Data required to work with this package,
  //! which are the Protocol and Modules to be loaded into Libraries
  Standard_EXPORT static void Init();

  //! Returns a Protocol from StepData (avoids to create it)
  Standard_EXPORT static occ::handle<StepData_Protocol> Protocol();
};
