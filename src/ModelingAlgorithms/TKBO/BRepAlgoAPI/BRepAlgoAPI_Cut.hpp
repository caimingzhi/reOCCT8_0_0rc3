#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepAlgoAPI_BooleanOperation.hpp>
class BOPAlgo_PaveFiller;
class TopoDS_Shape;

class BRepAlgoAPI_Cut : public BRepAlgoAPI_BooleanOperation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepAlgoAPI_Cut();
  Standard_EXPORT ~BRepAlgoAPI_Cut() override;

  Standard_EXPORT BRepAlgoAPI_Cut(const BOPAlgo_PaveFiller& PF);

  Standard_EXPORT BRepAlgoAPI_Cut(const TopoDS_Shape&          S1,
                                  const TopoDS_Shape&          S2,
                                  const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT BRepAlgoAPI_Cut(const TopoDS_Shape&          S1,
                                  const TopoDS_Shape&          S2,
                                  const BOPAlgo_PaveFiller&    aDSF,
                                  const bool                   bFWD     = true,
                                  const Message_ProgressRange& theRange = Message_ProgressRange());
};
