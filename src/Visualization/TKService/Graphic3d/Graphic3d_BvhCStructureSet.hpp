#pragma once

#include <BVH_PrimitiveSet3d.hpp>
#include <Graphic3d_BndBox3d.hpp>
#include <NCollection_IndexedMap.hpp>

class Graphic3d_CStructure;

class Graphic3d_BvhCStructureSet : public BVH_PrimitiveSet3d
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_BvhCStructureSet, BVH_PrimitiveSet3d)
protected:
  using BVH_PrimitiveSet3d::Box;

public:
  Standard_EXPORT Graphic3d_BvhCStructureSet();

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

private:
  NCollection_IndexedMap<const Graphic3d_CStructure*> myStructs;
};
