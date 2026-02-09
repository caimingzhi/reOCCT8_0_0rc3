#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class ShapeAlgo_AlgoContainer;

class ShapeAlgo
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Init();

  Standard_EXPORT static void SetAlgoContainer(
    const occ::handle<ShapeAlgo_AlgoContainer>& aContainer);

  Standard_EXPORT static occ::handle<ShapeAlgo_AlgoContainer> AlgoContainer();
};
