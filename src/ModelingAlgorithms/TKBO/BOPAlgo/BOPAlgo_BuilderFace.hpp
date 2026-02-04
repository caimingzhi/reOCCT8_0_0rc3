#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Face.hpp>
#include <TopAbs_Orientation.hpp>
#include <BOPAlgo_BuilderArea.hpp>
#include <NCollection_BaseAllocator.hpp>

//! The algorithm to build new faces from the given faces and
//! set of edges lying on this face.
//!
//! The algorithm returns the following Error statuses:
//! - *BOPAlgo_AlertNullInputShapes* - in case the given face is a null shape.
//!
class BOPAlgo_BuilderFace : public BOPAlgo_BuilderArea
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPAlgo_BuilderFace();
  Standard_EXPORT ~BOPAlgo_BuilderFace() override;

  Standard_EXPORT BOPAlgo_BuilderFace(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  //! Sets the face generatix
  Standard_EXPORT void SetFace(const TopoDS_Face& theFace);

  //! Returns the face generatix
  Standard_EXPORT const TopoDS_Face& Face() const;

  //! Performs the algorithm
  Standard_EXPORT void Perform(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT TopAbs_Orientation Orientation() const;

protected:
  //! Collect the edges that
  //! a) are internal
  //! b) are the same and have different orientation
  Standard_EXPORT void PerformShapesToAvoid(const Message_ProgressRange& theRange) override;

  //! Build draft wires
  //! a)myLoops - draft wires that consist of
  //! boundary edges
  //! b)myLoopsInternal - draft wires that contains
  //! inner edges
  Standard_EXPORT void PerformLoops(const Message_ProgressRange& theRange) override;

  //! Build draft faces that contains boundary edges
  Standard_EXPORT void PerformAreas(const Message_ProgressRange& theRange) override;

  //! Build finalized faces with internals
  Standard_EXPORT void PerformInternalShapes(const Message_ProgressRange& theRange) override;

  Standard_EXPORT void CheckData() override;

protected:
  TopoDS_Face        myFace;
  TopAbs_Orientation myOrientation;
};

