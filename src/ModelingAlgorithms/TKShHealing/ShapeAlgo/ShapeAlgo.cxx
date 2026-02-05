#include <ShapeAlgo.hpp>
#include <ShapeAlgo_AlgoContainer.hpp>
#include <ShapeExtend.hpp>

static occ::handle<ShapeAlgo_AlgoContainer> theContainer;

//=================================================================================================

void ShapeAlgo::Init()
{
  static bool init = false;
  if (init)
    return;
  init         = true;
  theContainer = new ShapeAlgo_AlgoContainer;

  // initialization of Standard Shape Healing
  ShapeExtend::Init();
}

//=================================================================================================

void ShapeAlgo::SetAlgoContainer(const occ::handle<ShapeAlgo_AlgoContainer>& aContainer)
{
  theContainer = aContainer;
}

//=================================================================================================

occ::handle<ShapeAlgo_AlgoContainer> ShapeAlgo::AlgoContainer()
{
  return theContainer;
}
