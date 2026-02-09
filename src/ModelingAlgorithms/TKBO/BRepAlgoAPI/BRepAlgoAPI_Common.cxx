#include <BOPAlgo_PaveFiller.hpp>
#include <BRepAlgoAPI_Common.hpp>
#include <TopoDS_Shape.hpp>

BRepAlgoAPI_Common::BRepAlgoAPI_Common()

{
  myOperation = BOPAlgo_COMMON;
}

BRepAlgoAPI_Common::BRepAlgoAPI_Common(const BOPAlgo_PaveFiller& aPF)
    : BRepAlgoAPI_BooleanOperation(aPF)
{
  myOperation = BOPAlgo_COMMON;
}

BRepAlgoAPI_Common::~BRepAlgoAPI_Common() = default;

BRepAlgoAPI_Common::BRepAlgoAPI_Common(const TopoDS_Shape&          S1,
                                       const TopoDS_Shape&          S2,
                                       const Message_ProgressRange& theRange)
    : BRepAlgoAPI_BooleanOperation(S1, S2, BOPAlgo_COMMON)
{
  Build(theRange);
}

BRepAlgoAPI_Common::BRepAlgoAPI_Common(const TopoDS_Shape&          S1,
                                       const TopoDS_Shape&          S2,
                                       const BOPAlgo_PaveFiller&    aDSF,
                                       const Message_ProgressRange& theRange)
    : BRepAlgoAPI_BooleanOperation(S1, S2, aDSF, BOPAlgo_COMMON)
{
  Build(theRange);
}
