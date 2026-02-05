#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepAlgoAPI_BooleanOperation.hpp>
class BOPAlgo_PaveFiller;
class TopoDS_Shape;

//! The class provides Boolean common operation
//! between arguments and tools (Boolean Intersection).
class BRepAlgoAPI_Common : public BRepAlgoAPI_BooleanOperation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT BRepAlgoAPI_Common();
  Standard_EXPORT ~BRepAlgoAPI_Common() override;

  //! Empty constructor
  //! <PF> - PaveFiller object that is carried out
  Standard_EXPORT BRepAlgoAPI_Common(const BOPAlgo_PaveFiller& PF);

  //! Constructor with two shapes
  //! <S1>  -argument
  //! <S2>  -tool
  //! <anOperation> - the type of the operation
  //! Obsolete
  Standard_EXPORT BRepAlgoAPI_Common(
    const TopoDS_Shape&          S1,
    const TopoDS_Shape&          S2,
    const Message_ProgressRange& theRange = Message_ProgressRange());

  //! Constructor with two shapes
  //! <S1>  -argument
  //! <S2>  -tool
  //! <anOperation> - the type of the operation
  //! <PF> - PaveFiller object that is carried out
  //! Obsolete
  Standard_EXPORT BRepAlgoAPI_Common(
    const TopoDS_Shape&          S1,
    const TopoDS_Shape&          S2,
    const BOPAlgo_PaveFiller&    PF,
    const Message_ProgressRange& theRange = Message_ProgressRange());
};
