#pragma once

#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>

#include <BOPAlgo_Builder.hpp>

#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>

class BOPAlgo_CellsBuilder : public BOPAlgo_Builder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPAlgo_CellsBuilder();

  Standard_EXPORT BOPAlgo_CellsBuilder(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  Standard_EXPORT ~BOPAlgo_CellsBuilder() override;

  Standard_EXPORT void Clear() override;

  Standard_EXPORT void AddToResult(const NCollection_List<TopoDS_Shape>& theLSToTake,
                                   const NCollection_List<TopoDS_Shape>& theLSToAvoid,
                                   const int                             theMaterial = 0,
                                   const bool                            theUpdate   = false);

  Standard_EXPORT void AddAllToResult(const int theMaterial = 0, const bool theUpdate = false);

  Standard_EXPORT void RemoveFromResult(const NCollection_List<TopoDS_Shape>& theLSToTake,
                                        const NCollection_List<TopoDS_Shape>& theLSToAvoid);

  Standard_EXPORT void RemoveAllFromResult();

  Standard_EXPORT void RemoveInternalBoundaries();

  Standard_EXPORT const TopoDS_Shape& GetAllParts() const;

  Standard_EXPORT void MakeContainers();

protected:
  Standard_EXPORT const NCollection_List<TopoDS_Shape>* LocModified(
    const TopoDS_Shape& theS) override;

  Standard_EXPORT void PerformInternal1(const BOPAlgo_PaveFiller&    thePF,
                                        const Message_ProgressRange& theRange) override;

  Standard_EXPORT void IndexParts();

  Standard_EXPORT void FindParts(const NCollection_List<TopoDS_Shape>& theLSToTake,
                                 const NCollection_List<TopoDS_Shape>& theLSToAvoid,
                                 NCollection_List<TopoDS_Shape>&       theParts);

  Standard_EXPORT bool RemoveInternals(
    const NCollection_List<TopoDS_Shape>&                         theLS,
    NCollection_List<TopoDS_Shape>&                               theLSNew,
    const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theMapKeepBnd =
      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>());

  TopoDS_Shape myAllParts;

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                                           myIndex;
  NCollection_DataMap<int, NCollection_List<TopoDS_Shape>>                 myMaterials;
  NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher>          myShapeMaterial;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myMapModified;
};
