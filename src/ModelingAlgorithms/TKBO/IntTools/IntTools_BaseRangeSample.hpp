#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class IntTools_BaseRangeSample
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntTools_BaseRangeSample();

  Standard_EXPORT IntTools_BaseRangeSample(const int theDepth);

  void SetDepth(const int theDepth) { myDepth = theDepth; }

  int GetDepth() const { return myDepth; }

private:
  int myDepth;
};
