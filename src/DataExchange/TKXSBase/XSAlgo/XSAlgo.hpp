#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class XSAlgo_AlgoContainer;

class XSAlgo
{
public:
  DEFINE_STANDARD_ALLOC

  //! Provides initerface to the algorithms from Shape Healing
  //! and others for XSTEP processors.
  //! Creates and initializes default AlgoContainer.
  Standard_EXPORT static void Init();

  //! Sets default AlgoContainer
  Standard_EXPORT static void SetAlgoContainer(const occ::handle<XSAlgo_AlgoContainer>& aContainer);

  //! Returns default AlgoContainer
  Standard_EXPORT static occ::handle<XSAlgo_AlgoContainer> AlgoContainer();
};

