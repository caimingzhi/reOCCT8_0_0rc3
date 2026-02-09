#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_BuilderArea.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <Bnd_Box.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>

class BOPAlgo_BuilderSolid : public BOPAlgo_BuilderArea
{
public:
  DEFINE_STANDARD_ALLOC

public:
  Standard_EXPORT BOPAlgo_BuilderSolid();
  Standard_EXPORT ~BOPAlgo_BuilderSolid() override;

  Standard_EXPORT BOPAlgo_BuilderSolid(const occ::handle<NCollection_BaseAllocator>& theAllocator);

public:
  Standard_EXPORT void Perform(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

public:
  const NCollection_DataMap<TopoDS_Shape, Bnd_Box, TopTools_ShapeMapHasher>& GetBoxesMap() const
  {
    return myBoxes;
  }

protected:
  Standard_EXPORT void PerformShapesToAvoid(const Message_ProgressRange& theRange) override;

  Standard_EXPORT void PerformLoops(const Message_ProgressRange& theRange) override;

  Standard_EXPORT void PerformAreas(const Message_ProgressRange& theRange) override;

  Standard_EXPORT void PerformInternalShapes(const Message_ProgressRange& theRange) override;

private:
  NCollection_DataMap<TopoDS_Shape, Bnd_Box, TopTools_ShapeMapHasher> myBoxes;
};
