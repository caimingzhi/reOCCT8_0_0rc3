#include <BRepAlgoAPI_Algo.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <TopoDS_Shape.hpp>

//=================================================================================================

BRepAlgoAPI_Algo::BRepAlgoAPI_Algo()
    : BOPAlgo_Options(NCollection_BaseAllocator::CommonBaseAllocator())
{
}

//=================================================================================================

BRepAlgoAPI_Algo::BRepAlgoAPI_Algo(const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : BOPAlgo_Options(theAllocator)
{
}

//=================================================================================================

BRepAlgoAPI_Algo::~BRepAlgoAPI_Algo() = default;

//=================================================================================================

const TopoDS_Shape& BRepAlgoAPI_Algo::Shape()
{
  return myShape;
}
