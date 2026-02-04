#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_List.hpp>
#include <BOPTools_ConnexityBlock.hpp>
#include <BOPAlgo_Algo.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <TopoDS_Shape.hpp>
class TopoDS_Shape;

//! The class provides the splitting of the set of connected faces
//! on separate loops
class BOPAlgo_ShellSplitter : public BOPAlgo_Algo
{
public:
  DEFINE_STANDARD_ALLOC

  //! empty constructor
  Standard_EXPORT BOPAlgo_ShellSplitter();
  Standard_EXPORT ~BOPAlgo_ShellSplitter() override;

  //! constructor
  Standard_EXPORT BOPAlgo_ShellSplitter(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  //! adds a face <theS> to process
  Standard_EXPORT void AddStartElement(const TopoDS_Shape& theS);

  //! return the faces to process
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& StartElements() const;

  //! performs the algorithm
  Standard_EXPORT void Perform(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  //! returns the loops
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Shells() const;

  Standard_EXPORT static void SplitBlock(BOPTools_ConnexityBlock& theCB);

protected:
  Standard_EXPORT void MakeShells(const Message_ProgressRange& theRange);

  NCollection_List<TopoDS_Shape>            myStartShapes;
  NCollection_List<TopoDS_Shape>            myShells;
  NCollection_List<BOPTools_ConnexityBlock> myLCB;
};

