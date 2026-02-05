#pragma once

#include <Standard.hpp>

#include <ShapeProcess_Context.hpp>

class Message_ProgressRange;

typedef bool (*ShapeProcess_OperFunc)(const occ::handle<ShapeProcess_Context>& context,
                                      const Message_ProgressRange&             theProgress);

#include <ShapeProcess_Operator.hpp>
class ShapeProcess_Context;

//! Defines operator as container for static function
//! OperFunc. This allows user to create new operators
//! without creation of new classes
class ShapeProcess_UOperator : public ShapeProcess_Operator
{

public:
  //! Creates operator with implementation defined as
  //! OperFunc (static function)
  Standard_EXPORT ShapeProcess_UOperator(const ShapeProcess_OperFunc func);

  //! Performs operation and records changes in the context
  Standard_EXPORT bool Perform(
    const occ::handle<ShapeProcess_Context>& context,
    const Message_ProgressRange&             theProgress = Message_ProgressRange()) override;

  DEFINE_STANDARD_RTTIEXT(ShapeProcess_UOperator, ShapeProcess_Operator)

private:
  ShapeProcess_OperFunc myFunc;
};
