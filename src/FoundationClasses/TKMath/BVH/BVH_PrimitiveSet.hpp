#pragma once

#include <BVH_Object.hpp>
#include <BVH_Builder.hpp>
#include <BVH_BinnedBuilder.hpp>

template <class T, int N>
class BVH_PrimitiveSet : public BVH_Object<T, N>, public BVH_Set<T, N>
{
protected:
  using BVH_Set<T, N>::Box;

public:
  static const int MaxTreeDepth = BVH_Constants_MaxTreeDepth;

  BVH_PrimitiveSet()
      : myBVH(new BVH_Tree<T, N>()),

        myBuilder(
          new BVH_BinnedBuilder<T, N, BVH_Constants_NbBinsBest>(BVH_Constants_LeafNodeSizeDefault,
                                                                BVH_Constants_MaxTreeDepth))
  {
  }

  BVH_PrimitiveSet(const opencascade::handle<BVH_Builder<T, N>>& theBuilder)
      : myBVH(new BVH_Tree<T, N>()),
        myBuilder(theBuilder)
  {
  }

  ~BVH_PrimitiveSet() override
  {
    myBVH.Nullify();
    myBuilder.Nullify();
  }

public:
  BVH_Box<T, N> Box() const override
  {
    if (BVH_Object<T, N>::myIsDirty)
    {
      myBox = BVH_Set<T, N>::Box();
    }
    return myBox;
  }

  virtual const opencascade::handle<BVH_Tree<T, N>>& BVH()
  {
    if (BVH_Object<T, N>::myIsDirty)
    {
      Update();
    }
    return myBVH;
  }

  virtual const opencascade::handle<BVH_Builder<T, N>>& Builder() const { return myBuilder; }

  virtual void SetBuilder(const opencascade::handle<BVH_Builder<T, N>>& theBuilder)
  {
    myBuilder = theBuilder;
  }

protected:
  virtual void Update()
  {
    if (BVH_Object<T, N>::myIsDirty)
    {
      myBuilder->Build(this, myBVH.operator->(), Box());
      BVH_Object<T, N>::myIsDirty = false;
    }
  }

protected:
  opencascade::handle<BVH_Tree<T, N>>    myBVH;
  opencascade::handle<BVH_Builder<T, N>> myBuilder;

  mutable BVH_Box<T, N> myBox;
};
