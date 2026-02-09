#include <BOPAlgo_PaveFiller.hpp>
#include <BRepAlgoAPI_Fuse.hpp>
#include <TopoDS_Shape.hpp>

BRepAlgoAPI_Fuse::BRepAlgoAPI_Fuse()

{
  myOperation = BOPAlgo_FUSE;
}

BRepAlgoAPI_Fuse::BRepAlgoAPI_Fuse(const BOPAlgo_PaveFiller& aPF)
    : BRepAlgoAPI_BooleanOperation(aPF)
{
  myOperation = BOPAlgo_FUSE;
}

BRepAlgoAPI_Fuse::~BRepAlgoAPI_Fuse() = default;

BRepAlgoAPI_Fuse::BRepAlgoAPI_Fuse(const TopoDS_Shape&          S1,
                                   const TopoDS_Shape&          S2,
                                   const Message_ProgressRange& theRange)
    : BRepAlgoAPI_BooleanOperation(S1, S2, BOPAlgo_FUSE)
{
  Build(theRange);
}

BRepAlgoAPI_Fuse::BRepAlgoAPI_Fuse(const TopoDS_Shape&          S1,
                                   const TopoDS_Shape&          S2,
                                   const BOPAlgo_PaveFiller&    aDSF,
                                   const Message_ProgressRange& theRange)
    : BRepAlgoAPI_BooleanOperation(S1, S2, aDSF, BOPAlgo_FUSE)
{
  Build(theRange);
}
