#pragma once


#include <Standard.hpp>

#include <StepData_Protocol.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Type.hpp>
#include <Standard_CString.hpp>
class Interface_Protocol;

//! Protocol for StepAP214 Entities
//! It requires StepAP214 as a Resource
class StepAP214_Protocol : public StepData_Protocol
{

public:
  Standard_EXPORT StepAP214_Protocol();

  //! Returns a Case Number for each of the StepAP214 Entities
  Standard_EXPORT int TypeNumber(const occ::handle<Standard_Type>& atype) const override;

  Standard_EXPORT const char* SchemaName(
    const occ::handle<Interface_InterfaceModel>& theModel) const override;

  //! Returns count of Protocol used as Resources (level one)
  Standard_EXPORT int NbResources() const override;

  //! Returns a Resource, given its rank (between 1 and NbResources)
  Standard_EXPORT occ::handle<Interface_Protocol> Resource(const int num) const override;

  DEFINE_STANDARD_RTTIEXT(StepAP214_Protocol, StepData_Protocol)
};

