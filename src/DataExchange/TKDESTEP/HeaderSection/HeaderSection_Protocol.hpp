#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepData_Protocol.hpp>
#include <Standard_Integer.hpp>

//! Protocol for HeaderSection Entities
//! It requires HeaderSection as a Resource
class HeaderSection_Protocol : public StepData_Protocol
{

public:
  Standard_EXPORT HeaderSection_Protocol();

  //! Returns a Case Number for each of the HeaderSection Entities
  Standard_EXPORT int TypeNumber(const occ::handle<Standard_Type>& atype) const override;

  Standard_EXPORT const char* SchemaName(
    const occ::handle<Interface_InterfaceModel>&) const override;

  DEFINE_STANDARD_RTTIEXT(HeaderSection_Protocol, StepData_Protocol)
};
