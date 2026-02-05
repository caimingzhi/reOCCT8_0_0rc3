#include <BOPAlgo_PaveFiller.hpp>
#include <BRepAlgoAPI_Cut.hpp>
#include <TopoDS_Shape.hpp>

//=================================================================================================

BRepAlgoAPI_Cut::BRepAlgoAPI_Cut()

{
  myOperation = BOPAlgo_CUT;
}

//=================================================================================================

BRepAlgoAPI_Cut::BRepAlgoAPI_Cut(const BOPAlgo_PaveFiller& aPF)
    : BRepAlgoAPI_BooleanOperation(aPF)
{
  myOperation = BOPAlgo_CUT;
}

//=================================================================================================

BRepAlgoAPI_Cut::~BRepAlgoAPI_Cut() = default;

//=================================================================================================

BRepAlgoAPI_Cut::BRepAlgoAPI_Cut(const TopoDS_Shape&          S1,
                                 const TopoDS_Shape&          S2,
                                 const Message_ProgressRange& theRange)
    : BRepAlgoAPI_BooleanOperation(S1, S2, BOPAlgo_CUT)
{
  Build(theRange);
}

//=================================================================================================

BRepAlgoAPI_Cut::BRepAlgoAPI_Cut(const TopoDS_Shape&          S1,
                                 const TopoDS_Shape&          S2,
                                 const BOPAlgo_PaveFiller&    aDSF,
                                 const bool                   bFWD,
                                 const Message_ProgressRange& theRange)
    : BRepAlgoAPI_BooleanOperation(S1, S2, aDSF, (bFWD) ? BOPAlgo_CUT : BOPAlgo_CUT21)
{
  Build(theRange);
}
