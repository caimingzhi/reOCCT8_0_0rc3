#pragma once

#include <BVH_Set.hpp>
#include <BVH_Object.hpp>

template <class T, int N>
class BVH_ObjectSet : public BVH_Set<T, N>
{
public:
  typedef NCollection_Vector<opencascade::handle<BVH_Object<T, N>>> BVH_ObjectList;

public:
  BVH_ObjectSet() = default;

  ~BVH_ObjectSet() override = default;

public:
  virtual void Clear()
  {
    for (typename BVH_ObjectList::Iterator anObjectIter(myObjects); anObjectIter.More();
         anObjectIter.Next())
    {
      anObjectIter.ChangeValue().Nullify();
    }
    myObjects.Clear();
  }

  BVH_ObjectList& Objects() { return myObjects; }

  const BVH_ObjectList& Objects() const { return myObjects; }

public:
  int Size() const override { return myObjects.Size(); }

  using BVH_Set<T, N>::Box;

  BVH_Box<T, N> Box(const int theIndex) const override { return myObjects.Value(theIndex)->Box(); }

  T Center(const int theIndex, const int theAxis) const override
  {

    return BVH::CenterAxis<T, N>::Center(myObjects.Value(theIndex)->Box(), theAxis);
  }

  void Swap(const int theIndex1, const int theIndex2) override
  {
    std::swap(myObjects.ChangeValue(theIndex1), myObjects.ChangeValue(theIndex2));
  }

protected:
  BVH_ObjectList myObjects;
};

#include <BVH_Builder.hpp>
#include <BVH_BinnedBuilder.hpp>

template <class T, int N>
class BVH_Geometry : public BVH_ObjectSet<T, N>
{
public:
  BVH_Geometry()
      : myIsDirty(false),
        myBVH(new BVH_Tree<T, N>()),

        myBuilder(new BVH_BinnedBuilder<T, N, BVH_Constants_NbBinsOptimal>(
          BVH_Constants_LeafNodeSizeSingle))
  {
  }

  BVH_Geometry(const opencascade::handle<BVH_Builder<T, N>>& theBuilder)
      : myIsDirty(false),
        myBVH(new BVH_Tree<T, N>()),
        myBuilder(theBuilder)
  {
  }

  ~BVH_Geometry() override
  {
    myBVH.Nullify();
    myBuilder.Nullify();
  }

public:
  virtual bool IsDirty() const { return myIsDirty; }

  virtual void MarkDirty() { myIsDirty = true; }

  using BVH_ObjectSet<T, N>::Box;

  BVH_Box<T, N> Box() const override
  {
    if (myIsDirty)
    {
      myBox = BVH_Set<T, N>::Box();
    }
    return myBox;
  }

  virtual const opencascade::handle<BVH_Tree<T, N>>& BVH()
  {
    if (myIsDirty)
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
    if (myIsDirty)
    {
      myBuilder->Build(this, myBVH.operator->(), Box());
      myIsDirty = false;
    }
  }

protected:
  bool                                   myIsDirty;
  opencascade::handle<BVH_Tree<T, N>>    myBVH;
  opencascade::handle<BVH_Builder<T, N>> myBuilder;

  mutable BVH_Box<T, N> myBox;
};
