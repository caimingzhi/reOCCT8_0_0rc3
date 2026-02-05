#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <StepData_Protocol.hpp>
#include <Standard_Integer.hpp>
class Interface_Protocol;
class Interface_Graph;
class Interface_Check;

//! A FileProtocol is defined as the addition of several already
//! existing Protocols. It corresponds to the definition of a
//! SchemaName with several Names, each one being attached to a
//! specific Protocol. Thus, a File defined with a compound Schema
//! is processed as any other one, once built the equivalent
//! compound Protocol, a FileProtocol
class StepData_FileProtocol : public StepData_Protocol
{

public:
  //! Creates an empty FileProtocol
  Standard_EXPORT StepData_FileProtocol();

  //! Adds a Protocol to the definition list of the FileProtocol
  //! But ensures that each class of Protocol is present only once
  //! in this list
  Standard_EXPORT void Add(const occ::handle<StepData_Protocol>& protocol);

  //! Gives the count of Protocols used as Resource (can be zero)
  //! i.e. the count of Protocol recorded by calling the method Add
  Standard_EXPORT int NbResources() const override;

  //! Returns a Resource, given a rank. Here, rank of calling Add
  Standard_EXPORT occ::handle<Interface_Protocol> Resource(const int num) const override;

  //! Returns a Case Number, specific of each recognized Type
  //! Here, NO Type at all is recognized properly : all Types are
  //! recognized by the resources
  Standard_EXPORT int TypeNumber(const occ::handle<Standard_Type>& atype) const override;

  //! Calls GlobalCheck for each of its recorded resources
  Standard_EXPORT bool GlobalCheck(const Interface_Graph&        G,
                                   occ::handle<Interface_Check>& ach) const override;

  //! Returns the Schema Name attached to each class of Protocol
  //! To be redefined by each sub-class
  //! Here, SchemaName returns "" (empty String)
  //! was C++ : return const
  Standard_EXPORT const char* SchemaName(
    const occ::handle<Interface_InterfaceModel>& theModel) const override;

  DEFINE_STANDARD_RTTIEXT(StepData_FileProtocol, StepData_Protocol)

private:
  NCollection_Sequence<occ::handle<Standard_Transient>> thecomps;
};
