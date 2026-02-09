#include <ShapeProcess_UOperator.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeProcess_UOperator, ShapeProcess_Operator)

ShapeProcess_UOperator::ShapeProcess_UOperator(const ShapeProcess_OperFunc func)
    : myFunc(func)
{
}

bool ShapeProcess_UOperator::Perform(const occ::handle<ShapeProcess_Context>& context,
                                     const Message_ProgressRange&             theProgress)
{
  return myFunc(context, theProgress);
}
