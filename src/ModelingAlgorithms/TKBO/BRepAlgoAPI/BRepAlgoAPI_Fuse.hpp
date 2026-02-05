#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepAlgoAPI_BooleanOperation.hpp>
class BOPAlgo_PaveFiller;
class TopoDS_Shape;

//! The class provides Boolean fusion operation
//! between arguments and tools (Boolean Union).
class BRepAlgoAPI_Fuse : public BRepAlgoAPI_BooleanOperation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT BRepAlgoAPI_Fuse();
  Standard_EXPORT ~BRepAlgoAPI_Fuse() override;

  //! Empty constructor
  //! <PF> - PaveFiller object that is carried out
  Standard_EXPORT BRepAlgoAPI_Fuse(const BOPAlgo_PaveFiller& PF);

  //! Constructor with two shapes
  //! <S1>  -argument
  //! <S2>  -tool
  //! <anOperation> - the type of the operation
  //! Obsolete
  Standard_EXPORT BRepAlgoAPI_Fuse(const TopoDS_Shape&          S1,
                                   const TopoDS_Shape&          S2,
                                   const Message_ProgressRange& theRange = Message_ProgressRange());

  //! Constructor with two shapes
  //! <S1>  -argument
  //! <S2>  -tool
  //! <anOperation> - the type of the operation
  //! <PF> - PaveFiller object that is carried out
  //! Obsolete
  Standard_EXPORT BRepAlgoAPI_Fuse(const TopoDS_Shape&          S1,
                                   const TopoDS_Shape&          S2,
                                   const BOPAlgo_PaveFiller&    aDSF,
                                   const Message_ProgressRange& theRange = Message_ProgressRange());
};
