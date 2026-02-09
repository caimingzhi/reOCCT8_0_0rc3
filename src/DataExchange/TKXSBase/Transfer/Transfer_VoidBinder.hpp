#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Transfer_Binder.hpp>

class Transfer_VoidBinder : public Transfer_Binder
{

public:
  Standard_EXPORT Transfer_VoidBinder();

  Standard_EXPORT occ::handle<Standard_Type> ResultType() const override;

  Standard_EXPORT const char* ResultTypeName() const override;

  DEFINE_STANDARD_RTTIEXT(Transfer_VoidBinder, Transfer_Binder)
};
