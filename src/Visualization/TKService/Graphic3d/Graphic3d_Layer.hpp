#pragma once

#include <Graphic3d_BvhCStructureSet.hpp>
#include <Graphic3d_BvhCStructureSetTrsfPers.hpp>
#include <Graphic3d_DisplayPriority.hpp>
#include <Graphic3d_ZLayerId.hpp>
#include <Graphic3d_ZLayerSettings.hpp>
#include <Graphic3d_RenderingParams.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_IndexedMap.hpp>

#include <array>

typedef std::array<NCollection_IndexedMap<const Graphic3d_CStructure*>,
                   Graphic3d_DisplayPriority_NB>
  Graphic3d_ArrayOfIndexedMapOfStructure;

class Graphic3d_CullingTool;

class Graphic3d_Layer : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_Layer, Standard_Transient)
public:
  Standard_EXPORT Graphic3d_Layer(Graphic3d_ZLayerId                theId,
                                  const occ::handle<BVH_Builder3d>& theBuilder);

  Standard_EXPORT ~Graphic3d_Layer() override;

  Graphic3d_ZLayerId LayerId() const { return myLayerId; }

  const occ::handle<BVH_Builder3d>& FrustumCullingBVHBuilder() const
  {
    return myBVHPrimitivesTrsfPers.Builder();
  }

  void SetFrustumCullingBVHBuilder(const occ::handle<BVH_Builder3d>& theBuilder)
  {
    myBVHPrimitivesTrsfPers.SetBuilder(theBuilder);
  }

  bool IsImmediate() const { return myLayerSettings.IsImmediate(); }

  const Graphic3d_ZLayerSettings& LayerSettings() const { return myLayerSettings; };

  Standard_EXPORT void SetLayerSettings(const Graphic3d_ZLayerSettings& theSettings);

  Standard_EXPORT void Add(const Graphic3d_CStructure* theStruct,
                           Graphic3d_DisplayPriority   thePriority,
                           bool                        isForChangePriority = false);

  Standard_EXPORT bool Remove(const Graphic3d_CStructure* theStruct,
                              Graphic3d_DisplayPriority&  thePriority,
                              bool                        isForChangePriority = false);

  int NbStructures() const { return myNbStructures; }

  int NbStructuresNotCulled() const { return myNbStructuresNotCulled; }

  int NbPriorities() const { return Graphic3d_DisplayPriority_NB; }

  Standard_EXPORT bool Append(const Graphic3d_Layer& theOther);

  const Graphic3d_ArrayOfIndexedMapOfStructure& ArrayOfStructures() const { return myArray; }

  const NCollection_IndexedMap<const Graphic3d_CStructure*>& Structures(
    Graphic3d_DisplayPriority thePriority) const
  {
    return myArray[thePriority];
  }

  Standard_EXPORT void InvalidateBVHData();

  void InvalidateBoundingBox() const
  {
    myIsBoundingBoxNeedsReset[0] = myIsBoundingBoxNeedsReset[1] = true;
  }

  Standard_EXPORT Bnd_Box BoundingBox(int                                  theViewId,
                                      const occ::handle<Graphic3d_Camera>& theCamera,
                                      int                                  theWindowWidth,
                                      int                                  theWindowHeight,
                                      bool theToIncludeAuxiliary) const;

  Standard_EXPORT double considerZoomPersistenceObjects(
    int                                  theViewId,
    const occ::handle<Graphic3d_Camera>& theCamera,
    int                                  theWindowWidth,
    int                                  theWindowHeight) const;

  Standard_EXPORT void UpdateCulling(
    int                                             theViewId,
    const Graphic3d_CullingTool&                    theSelector,
    const Graphic3d_RenderingParams::FrustumCulling theFrustumCullingState);

  bool IsCulled() const { return myNbStructuresNotCulled == 0; }

  int NbOfTransformPersistenceObjects() const { return myBVHPrimitivesTrsfPers.Size(); }

public:
  const Graphic3d_BvhCStructureSet& CullableStructuresBVH() const { return myBVHPrimitives; }

  const Graphic3d_BvhCStructureSetTrsfPers& CullableTrsfPersStructuresBVH() const
  {
    return myBVHPrimitivesTrsfPers;
  }

  const NCollection_IndexedMap<const Graphic3d_CStructure*>& NonCullableStructures() const
  {
    return myAlwaysRenderedMap;
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  Standard_EXPORT void updateBVH() const;

private:
  Graphic3d_ArrayOfIndexedMapOfStructure myArray;

  int myNbStructures;

  int myNbStructuresNotCulled;

  Graphic3d_ZLayerSettings myLayerSettings;

  Graphic3d_ZLayerId myLayerId;

  mutable Graphic3d_BvhCStructureSet myBVHPrimitives;

  mutable Graphic3d_BvhCStructureSetTrsfPers myBVHPrimitivesTrsfPers;

  mutable NCollection_IndexedMap<const Graphic3d_CStructure*> myAlwaysRenderedMap;

  bool myBVHIsLeftChildQueuedFirst;

  mutable bool myIsBVHPrimitivesNeedsReset;

  mutable bool myIsBoundingBoxNeedsReset[2];

  mutable Bnd_Box myBoundingBox[2];
};
