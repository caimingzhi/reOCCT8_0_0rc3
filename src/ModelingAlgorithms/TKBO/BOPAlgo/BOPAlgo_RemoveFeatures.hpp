#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_BuilderShape.hpp>
#include <BRepTools_History.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Map.hpp>

class BOPAlgo_RemoveFeatures : public BOPAlgo_BuilderShape
{
public:
  DEFINE_STANDARD_ALLOC

public:
  BOPAlgo_RemoveFeatures()

    = default;

public:
  void SetShape(const TopoDS_Shape& theShape) { myInputShape = theShape; }

  const TopoDS_Shape& InputShape() const { return myInputShape; }

  void AddFaceToRemove(const TopoDS_Shape& theFace) { myFacesToRemove.Append(theFace); }

  void AddFacesToRemove(const NCollection_List<TopoDS_Shape>& theFaces)
  {
    NCollection_List<TopoDS_Shape>::Iterator it(theFaces);
    for (; it.More(); it.Next())
      myFacesToRemove.Append(it.Value());
  }

  const NCollection_List<TopoDS_Shape>& FacesToRemove() const { return myFacesToRemove; }

public:
  Standard_EXPORT void Perform(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

public:
  void Clear() override
  {
    BOPAlgo_BuilderShape::Clear();
    myInputShape.Nullify();
    myShape.Nullify();
    myFacesToRemove.Clear();
    myFeatures.Clear();
    myInputsMap.Clear();
  }

protected:
  Standard_EXPORT void CheckData() override;

  Standard_EXPORT void PrepareFeatures(const Message_ProgressRange& theRange);

  Standard_EXPORT void RemoveFeatures(const Message_ProgressRange& theRange);

  Standard_EXPORT void RemoveFeature(
    const TopoDS_Shape&                                                  theFeature,
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theSolids,
    const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&        theFeatureFacesMap,
    const bool                                                           theHasAdjacentFaces,
    const NCollection_IndexedDataMap<TopoDS_Shape,
                                     NCollection_List<TopoDS_Shape>,
                                     TopTools_ShapeMapHasher>&           theAdjFaces,
    const occ::handle<BRepTools_History>&                                theAdjFacesHistory,
    const bool                                                           theSolidsHistoryNeeded,
    const Message_ProgressRange&                                         theRange);

  Standard_EXPORT void UpdateHistory(const Message_ProgressRange& theRange);

  Standard_EXPORT void SimplifyResult(const Message_ProgressRange& theRange);

  Standard_EXPORT void PostTreat();

  Standard_EXPORT void fillPIConstants(const double     theWhole,
                                       BOPAlgo_PISteps& theSteps) const override;

protected:
  TopoDS_Shape                   myInputShape;
  NCollection_List<TopoDS_Shape> myFacesToRemove;

  NCollection_List<TopoDS_Shape> myFeatures;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myInputsMap;
};
