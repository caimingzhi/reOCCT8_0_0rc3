#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_Operation.hpp>
#include <BRepAlgoAPI_BuilderAlgo.hpp>
class BOPAlgo_PaveFiller;
class TopoDS_Shape;

//! The root API class for performing Boolean Operations on arbitrary shapes.
//!
//! The arguments of the operation are divided in two groups - *Objects* and *Tools*.
//! Each group can contain any number of shapes, but each shape should be valid
//! in terms of *BRepCheck_Analyzer* and *BOPAlgo_ArgumentAnalyzer*.
//! The algorithm builds the splits of the given arguments using the intersection
//! results and combines the result of Boolean Operation of given type:
//! - *FUSE* - union of two groups of objects;
//! - *COMMON* - intersection of two groups of objects;
//! - *CUT* - subtraction of one group from the other;
//! - *SECTION* - section edges and vertices of all arguments;
//!
//! The rules for the arguments and type of the operation are the following:
//! - For Boolean operation *FUSE* all arguments should have equal dimensions;
//! - For Boolean operation *CUT* the minimal dimension of *Tools* should not be
//!   less than the maximal dimension of *Objects*;
//! - For Boolean operation *COMMON* the arguments can have any dimension.
//! - For Boolean operation *SECTION* the arguments can be of any type.
//!
//! Additionally to the errors of the base class the algorithm returns
//! the following Errors:
//! - *BOPAlgo_AlertBOPNotSet* - in case the type of Boolean Operation is not set.
class BRepAlgoAPI_BooleanOperation : public BRepAlgoAPI_BuilderAlgo
{
public:
  DEFINE_STANDARD_ALLOC

public: //! @name Constructors
  //! Empty constructor
  Standard_EXPORT BRepAlgoAPI_BooleanOperation();

  //! Constructor with precomputed intersections of arguments.
  Standard_EXPORT BRepAlgoAPI_BooleanOperation(const BOPAlgo_PaveFiller& thePF);

public: //! @name Setting/getting arguments
  //! Returns the first argument involved in this Boolean operation.
  //! Obsolete
  const TopoDS_Shape& Shape1() const { return myArguments.First(); }

  //! Returns the second argument involved in this Boolean operation.
  //! Obsolete
  const TopoDS_Shape& Shape2() const { return myTools.First(); }

  //! Sets the Tool arguments
  void SetTools(const NCollection_List<TopoDS_Shape>& theLS) { myTools = theLS; }

  //! Returns the Tools arguments
  const NCollection_List<TopoDS_Shape>& Tools() const { return myTools; }

public: //! @name Setting/Getting the type of Boolean operation
  //! Sets the type of Boolean operation
  void SetOperation(const BOPAlgo_Operation theBOP) { myOperation = theBOP; }

  //! Returns the type of Boolean Operation
  BOPAlgo_Operation Operation() const { return myOperation; }

public: //! @name Performing the operation
  //! Performs the Boolean operation.
  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

protected: //! @name Constructors
  //! Constructor to perform Boolean operation on only two arguments.
  //! Obsolete
  Standard_EXPORT BRepAlgoAPI_BooleanOperation(const TopoDS_Shape&     theS1,
                                               const TopoDS_Shape&     theS2,
                                               const BOPAlgo_Operation theOperation);

  //! Constructor to perform Boolean operation on only two arguments
  //! with precomputed intersection results.
  //! Obsolete
  Standard_EXPORT BRepAlgoAPI_BooleanOperation(const TopoDS_Shape&       theS1,
                                               const TopoDS_Shape&       theS2,
                                               const BOPAlgo_PaveFiller& thePF,
                                               const BOPAlgo_Operation   theOperation);

protected:                                    //! @name Fields
  NCollection_List<TopoDS_Shape> myTools;     //!< Tool arguments of operation
  BOPAlgo_Operation              myOperation; //!< Type of Boolean Operation
};
