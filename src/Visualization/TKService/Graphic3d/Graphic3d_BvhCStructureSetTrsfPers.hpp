#pragma once

#include <Graphic3d_BndBox3d.hpp>
#include <NCollection_Mat4.hpp>
#include <Standard_TypeDef.hpp>
#include <Graphic3d_WorldViewProjState.hpp>
#include <NCollection_Shared.hpp>
#include <NCollection_IndexedMap.hpp>

#ifndef _BVH_Builder3d_Header
  #define _BVH_Builder3d_Header

  #include <BVH_Builder.hpp>

typedef BVH_Builder<double, 3> BVH_Builder3d;

#endif

class Graphic3d_Camera;
class Graphic3d_CStructure;

class Graphic3d_BvhCStructureSetTrsfPers : public BVH_Set<double, 3>
{
private:
  typedef NCollection_Shared<Graphic3d_BndBox3d> HBndBox3d;

public:
  Standard_EXPORT Graphic3d_BvhCStructureSetTrsfPers(const occ::handle<BVH_Builder3d>& theBuilder);

  Standard_EXPORT int Size() const override;

  Standard_EXPORT Graphic3d_BndBox3d Box(const int theIdx) const override;

  Standard_EXPORT double Center(const int theIdx, const int theAxis) const override;

  Standard_EXPORT void Swap(const int theIdx1, const int theIdx2) override;

  Standard_EXPORT bool Add(const Graphic3d_CStructure* theStruct);

  Standard_EXPORT bool Remove(const Graphic3d_CStructure* theStruct);

  Standard_EXPORT void Clear();

  Standard_EXPORT const Graphic3d_CStructure* GetStructureById(int theId);

  const NCollection_IndexedMap<const Graphic3d_CStructure*>& Structures() const
  {
    return myStructs;
  }

  void MarkDirty() { myIsDirty = true; }

  Standard_EXPORT const opencascade::handle<BVH_Tree<double, 3>>& BVH(
    const occ::handle<Graphic3d_Camera>& theCamera,
    const NCollection_Mat4<double>&      theProjectionMatrix,
    const NCollection_Mat4<double>&      theWorldViewMatrix,
    const int                            theViewportWidth,
    const int                            theViewportHeight,
    const Graphic3d_WorldViewProjState&  theWVPState);

  const occ::handle<BVH_Builder3d>& Builder() const { return myBuilder; }

  void SetBuilder(const occ::handle<BVH_Builder3d>& theBuilder) { myBuilder = theBuilder; }

private:
  bool myIsDirty;

  opencascade::handle<BVH_Tree<double, 3>> myBVH;

  occ::handle<BVH_Builder3d> myBuilder;

  NCollection_IndexedMap<const Graphic3d_CStructure*> myStructs;

  NCollection_IndexedMap<occ::handle<HBndBox3d>> myStructBoxes;

  Graphic3d_WorldViewProjState myStructBoxesState;
};
