#include <BOPAlgo_BuilderArea.hpp>

//=================================================================================================

BOPAlgo_BuilderArea::BOPAlgo_BuilderArea()
    : myShapes(myAllocator),
      myLoops(myAllocator),
      myLoopsInternal(myAllocator),
      myAreas(myAllocator),
      myShapesToAvoid(100, myAllocator),
      myAvoidInternalShapes(false)
{
}

//=================================================================================================

BOPAlgo_BuilderArea::BOPAlgo_BuilderArea(const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : BOPAlgo_Algo(theAllocator),
      myShapes(myAllocator),
      myLoops(myAllocator),
      myLoopsInternal(myAllocator),
      myAreas(myAllocator),
      myShapesToAvoid(100, myAllocator),
      myAvoidInternalShapes(false)
{
}

//=================================================================================================

BOPAlgo_BuilderArea::~BOPAlgo_BuilderArea() = default;
