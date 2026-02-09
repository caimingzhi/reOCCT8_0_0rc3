#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepAlgoAPI_BooleanOperation.hpp>
class BOPAlgo_PaveFiller;
class TopoDS_Shape;

class BRepAlgoAPI_Common : public BRepAlgoAPI_BooleanOperation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepAlgoAPI_Common();
  Standard_EXPORT ~BRepAlgoAPI_Common() override;

  Standard_EXPORT BRepAlgoAPI_Common(const BOPAlgo_PaveFiller& PF);

  Standard_EXPORT BRepAlgoAPI_Common(
    const TopoDS_Shape&          S1,
    const TopoDS_Shape&          S2,
    const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT BRepAlgoAPI_Common(
    const TopoDS_Shape&          S1,
    const TopoDS_Shape&          S2,
    const BOPAlgo_PaveFiller&    PF,
    const Message_ProgressRange& theRange = Message_ProgressRange());
};
