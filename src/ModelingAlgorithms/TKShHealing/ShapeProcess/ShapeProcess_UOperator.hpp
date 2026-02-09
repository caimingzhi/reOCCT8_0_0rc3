#pragma once

#include <Standard.hpp>

#include <ShapeProcess_Context.hpp>

class Message_ProgressRange;

typedef bool (*ShapeProcess_OperFunc)(const occ::handle<ShapeProcess_Context>& context,
                                      const Message_ProgressRange&             theProgress);

#include <ShapeProcess_Operator.hpp>
class ShapeProcess_Context;

class ShapeProcess_UOperator : public ShapeProcess_Operator
{

public:
  Standard_EXPORT ShapeProcess_UOperator(const ShapeProcess_OperFunc func);

  Standard_EXPORT bool Perform(
    const occ::handle<ShapeProcess_Context>& context,
    const Message_ProgressRange&             theProgress = Message_ProgressRange()) override;

  DEFINE_STANDARD_RTTIEXT(ShapeProcess_UOperator, ShapeProcess_Operator)

private:
  ShapeProcess_OperFunc myFunc;
};
