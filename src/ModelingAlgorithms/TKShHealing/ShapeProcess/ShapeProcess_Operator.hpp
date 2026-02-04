#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Message_ProgressRange.hpp>

class ShapeProcess_Context;

//! Abstract Operator class providing a tool to
//! perform an operation on Context
class ShapeProcess_Operator : public Standard_Transient
{

public:
  //! Performs operation and eventually records
  //! changes in the context
  Standard_EXPORT virtual bool Perform(
    const occ::handle<ShapeProcess_Context>& context,
    const Message_ProgressRange&             theProgress = Message_ProgressRange()) = 0;

  DEFINE_STANDARD_RTTIEXT(ShapeProcess_Operator, Standard_Transient)
};

