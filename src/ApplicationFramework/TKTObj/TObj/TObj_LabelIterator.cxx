#include <TObj_LabelIterator.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TObj_LabelIterator, TObj_ObjectIterator)

TObj_LabelIterator::TObj_LabelIterator() = default;

TObj_LabelIterator::TObj_LabelIterator(const TDF_Label& theLabel, const bool isRecursive)
{
  Init(theLabel, isRecursive);
}

void TObj_LabelIterator::Next()
{
  myObject.Nullify();
  myNode.Nullify();
  MakeStep();
}
