#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Transfer_Binder.hpp>

//! a VoidBinder is used to bind a starting item with a status,
//! error or warning messages, but no result
//! It is interpreted by TransferProcess, which admits a
//! VoidBinder to be over-written, and copies its check to the
//! new Binder
class Transfer_VoidBinder : public Transfer_Binder
{

public:
  //! a VoidBinder is not Multiple (Remark : it is not Simple too)
  //! But it can bring next results ...
  Standard_EXPORT Transfer_VoidBinder();

  //! while a VoidBinder admits no Result, its ResultType returns
  //! the type of <me>
  Standard_EXPORT occ::handle<Standard_Type> ResultType() const override;

  //! Returns "(void)"
  Standard_EXPORT const char* ResultTypeName() const override;

  DEFINE_STANDARD_RTTIEXT(Transfer_VoidBinder, Transfer_Binder)
};
