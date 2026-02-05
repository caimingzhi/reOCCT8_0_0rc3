#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class ShapeAlgo_AlgoContainer;

class ShapeAlgo
{
public:
  DEFINE_STANDARD_ALLOC

  //! Provides initerface to the algorithms from Shape Healing.
  //! Creates and initializes default AlgoContainer.
  Standard_EXPORT static void Init();

  //! Sets default AlgoContainer
  Standard_EXPORT static void SetAlgoContainer(
    const occ::handle<ShapeAlgo_AlgoContainer>& aContainer);

  //! Returns default AlgoContainer
  Standard_EXPORT static occ::handle<ShapeAlgo_AlgoContainer> AlgoContainer();
};
