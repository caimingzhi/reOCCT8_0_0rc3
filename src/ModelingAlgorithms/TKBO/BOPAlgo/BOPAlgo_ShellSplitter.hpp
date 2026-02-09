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

class BOPAlgo_ShellSplitter : public BOPAlgo_Algo
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPAlgo_ShellSplitter();
  Standard_EXPORT ~BOPAlgo_ShellSplitter() override;

  Standard_EXPORT BOPAlgo_ShellSplitter(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  Standard_EXPORT void AddStartElement(const TopoDS_Shape& theS);

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& StartElements() const;

  Standard_EXPORT void Perform(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Shells() const;

  Standard_EXPORT static void SplitBlock(BOPTools_ConnexityBlock& theCB);

protected:
  Standard_EXPORT void MakeShells(const Message_ProgressRange& theRange);

  NCollection_List<TopoDS_Shape>            myStartShapes;
  NCollection_List<TopoDS_Shape>            myShells;
  NCollection_List<BOPTools_ConnexityBlock> myLCB;
};
