#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BOPAlgo_BOP.hpp>
#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Map.hpp>
class TopoDS_Shape;
class TopoDS_Face;

class BRepFeat_Builder : public BOPAlgo_BOP
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFeat_Builder();
  Standard_EXPORT ~BRepFeat_Builder() override;

  Standard_EXPORT void Clear() override;

  Standard_EXPORT void Init(const TopoDS_Shape& theShape);

  Standard_EXPORT void Init(const TopoDS_Shape& theShape, const TopoDS_Shape& theTool);

  Standard_EXPORT void SetOperation(const int theFuse);

  Standard_EXPORT void SetOperation(const int theFuse, const bool theFlag);

  Standard_EXPORT void PartsOfTool(NCollection_List<TopoDS_Shape>& theLT);

  Standard_EXPORT void KeepParts(const NCollection_List<TopoDS_Shape>& theIm);

  Standard_EXPORT void KeepPart(const TopoDS_Shape& theS);

  Standard_EXPORT void PerformResult(
    const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT void RebuildFaces();

  Standard_EXPORT void RebuildEdge(
    const TopoDS_Shape&                                           theE,
    const TopoDS_Face&                                            theF,
    const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theME,
    NCollection_List<TopoDS_Shape>&                               aLEIm);

  Standard_EXPORT void CheckSolidImages();

  Standard_EXPORT void FillRemoved();

  Standard_EXPORT void FillRemoved(const TopoDS_Shape&                                     theS,
                                   NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theM);

protected:
  Standard_EXPORT void Prepare() override;

  Standard_EXPORT void FillIn3DParts(
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& theDraftSolids,
    const Message_ProgressRange&                                              theRange) override;

  bool CheckArgsForOpenSolid() override { return false; }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myShapes;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myRemoved;
  int                                                    myFuse;
};
