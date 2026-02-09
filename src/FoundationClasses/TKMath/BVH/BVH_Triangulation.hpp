#pragma once

#include <BVH_PrimitiveSet.hpp>

template <class T, int N>
class BVH_Triangulation : public BVH_PrimitiveSet<T, N>
{
public:
  typedef typename BVH::VectorType<T, N>::Type BVH_VecNt;

public:
  BVH_Triangulation() = default;

  BVH_Triangulation(const opencascade::handle<BVH_Builder<T, N>>& theBuilder)
      : BVH_PrimitiveSet<T, N>(theBuilder)
  {
  }

  ~BVH_Triangulation() override = default;

public:
  typename BVH::ArrayType<T, N>::Type Vertices;

  BVH_Array4i Elements;

public:
  int Size() const override { return BVH::Array<int, 4>::Size(Elements); }

  using BVH_PrimitiveSet<T, N>::Box;

  BVH_Box<T, N> Box(const int theIndex) const override
  {
    const BVH_Vec4i& anIndex = BVH::Array<int, 4>::Value(Elements, theIndex);

    const BVH_VecNt& aPoint0 = BVH::Array<T, N>::Value(Vertices, anIndex.x());
    const BVH_VecNt& aPoint1 = BVH::Array<T, N>::Value(Vertices, anIndex.y());
    const BVH_VecNt& aPoint2 = BVH::Array<T, N>::Value(Vertices, anIndex.z());

    BVH_VecNt aMinPoint(aPoint0), aMaxPoint(aPoint0);

    BVH::BoxMinMax<T, N>::CwiseMin(aMinPoint, aPoint1);
    BVH::BoxMinMax<T, N>::CwiseMin(aMinPoint, aPoint2);
    BVH::BoxMinMax<T, N>::CwiseMax(aMaxPoint, aPoint1);
    BVH::BoxMinMax<T, N>::CwiseMax(aMaxPoint, aPoint2);
    return BVH_Box<T, N>(aMinPoint, aMaxPoint);
  }

  T Center(const int theIndex, const int theAxis) const override
  {
    const BVH_Vec4i& anIndex = BVH::Array<int, 4>::Value(Elements, theIndex);

    const BVH_VecNt& aPoint0 = BVH::Array<T, N>::Value(Vertices, anIndex.x());
    const BVH_VecNt& aPoint1 = BVH::Array<T, N>::Value(Vertices, anIndex.y());
    const BVH_VecNt& aPoint2 = BVH::Array<T, N>::Value(Vertices, anIndex.z());
    return (BVH::VecComp<T, N>::Get(aPoint0, theAxis) + BVH::VecComp<T, N>::Get(aPoint1, theAxis)
            + BVH::VecComp<T, N>::Get(aPoint2, theAxis))
           * static_cast<T>(1.0 / 3.0);
  }

  void Swap(const int theIndex1, const int theIndex2) override
  {
    BVH_Vec4i& anIndices1 = BVH::Array<int, 4>::ChangeValue(Elements, theIndex1);
    BVH_Vec4i& anIndices2 = BVH::Array<int, 4>::ChangeValue(Elements, theIndex2);
    std::swap(anIndices1, anIndices2);
  }
};
