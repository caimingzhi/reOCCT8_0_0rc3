#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepAlgoAPI_BuilderAlgo.hpp>

//! The class contains API level of the **Splitter** algorithm,
//! which allows splitting a group of arbitrary shapes by the
//! other group of arbitrary shapes.
//! The arguments of the operation are divided on two groups:
//! *Objects* - shapes that will be split;
//! *Tools*   - shapes by which the *Objects* will be split.
//! The result of the operation contains only the split parts
//! of the shapes from the group of *Objects*.
//! The split parts of the shapes from the group of *Tools* are excluded
//! from the result.
//! The shapes can be split by the other shapes from the same group
//! (in case these shapes are interfering).
//!
//! The class is a General Fuse based algorithm. Thus, all options
//! of the General Fuse algorithm such as Fuzzy mode, safe processing mode,
//! parallel processing mode, gluing mode and history support are also
//! available in this algorithm.
//! There is no requirement on the existence of the *Tools* shapes.
//! And if there are no *Tools* shapes, the result of the splitting
//! operation will be equivalent to the General Fuse result.
//!
//! The algorithm returns the following Error statuses:
//! - 0 - in case of success;
//! - *BOPAlgo_AlertTooFewArguments*    - in case there is no enough arguments for the
//! operation;
//! - *BOPAlgo_AlertIntersectionFailed* - in case the Intersection of the arguments has failed;
//! - *BOPAlgo_AlertBuilderFailed*      - in case the Building of the result has failed.
class BRepAlgoAPI_Splitter : public BRepAlgoAPI_BuilderAlgo
{
public:
  DEFINE_STANDARD_ALLOC

public: //! @name Constructors
  //! Empty constructor
  Standard_EXPORT BRepAlgoAPI_Splitter();

  //! Constructor with already prepared intersection tool - PaveFiller
  Standard_EXPORT BRepAlgoAPI_Splitter(const BOPAlgo_PaveFiller& thePF);

public: //! @name Setters/Getters for the Tools
  //! Sets the Tool arguments
  void SetTools(const NCollection_List<TopoDS_Shape>& theLS) { myTools = theLS; }

  //! Returns the Tool arguments
  const NCollection_List<TopoDS_Shape>& Tools() const { return myTools; }

public: //! @name Performing the operation
  //! Performs the Split operation.
  //! Performs the intersection of the argument shapes (both objects and tools)
  //! and splits objects by the tools.
  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

protected:                                //! @name Fields
  NCollection_List<TopoDS_Shape> myTools; //!< Tool arguments of the operation
};
