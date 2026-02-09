#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Face.hpp>
#include <TopAbs_Orientation.hpp>
#include <BOPAlgo_BuilderArea.hpp>
#include <NCollection_BaseAllocator.hpp>

class BOPAlgo_BuilderFace : public BOPAlgo_BuilderArea
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPAlgo_BuilderFace();
  Standard_EXPORT ~BOPAlgo_BuilderFace() override;

  Standard_EXPORT BOPAlgo_BuilderFace(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  Standard_EXPORT void SetFace(const TopoDS_Face& theFace);

  Standard_EXPORT const TopoDS_Face& Face() const;

  Standard_EXPORT void Perform(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT TopAbs_Orientation Orientation() const;

protected:
  Standard_EXPORT void PerformShapesToAvoid(const Message_ProgressRange& theRange) override;

  Standard_EXPORT void PerformLoops(const Message_ProgressRange& theRange) override;

  Standard_EXPORT void PerformAreas(const Message_ProgressRange& theRange) override;

  Standard_EXPORT void PerformInternalShapes(const Message_ProgressRange& theRange) override;

  Standard_EXPORT void CheckData() override;

protected:
  TopoDS_Face        myFace;
  TopAbs_Orientation myOrientation;
};
