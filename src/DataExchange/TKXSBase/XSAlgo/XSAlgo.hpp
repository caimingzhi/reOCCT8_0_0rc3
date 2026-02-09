#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class XSAlgo_AlgoContainer;

class XSAlgo
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Init();

  Standard_EXPORT static void SetAlgoContainer(const occ::handle<XSAlgo_AlgoContainer>& aContainer);

  Standard_EXPORT static occ::handle<XSAlgo_AlgoContainer> AlgoContainer();
};
