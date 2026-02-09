#pragma once

#include <BVH_Box.hpp>

template <class T, int N>
class BVH_Builder;

class BVH_TreeBaseTransient : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(BVH_TreeBaseTransient, Standard_Transient)
protected:
  BVH_TreeBaseTransient() {}

  virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const
  {
    (void)theOStream;
    (void)theDepth;
  }

  virtual void DumpNode(const int theNodeIndex, Standard_OStream& theOStream, int theDepth) const
  {
    (void)theNodeIndex;
    (void)theOStream;
    (void)theDepth;
  }
};

template <class T, int N>
class BVH_TreeBase : public BVH_TreeBaseTransient
{
  friend class BVH_Builder<T, N>;

public:
  typedef typename BVH_Box<T, N>::BVH_VecNt BVH_VecNt;

public:
  BVH_TreeBase()
      : myDepth(0)
  {
  }

  ~BVH_TreeBase() override = default;

  int Depth() const { return myDepth; }

  int Length() const { return BVH::Array<int, 4>::Size(myNodeInfoBuffer); }

public:
  BVH_VecNt& MinPoint(const int theNodeIndex)
  {
    return BVH::Array<T, N>::ChangeValue(myMinPointBuffer, theNodeIndex);
  }

  BVH_VecNt& MaxPoint(const int theNodeIndex)
  {
    return BVH::Array<T, N>::ChangeValue(myMaxPointBuffer, theNodeIndex);
  }

  const BVH_VecNt& MinPoint(const int theNodeIndex) const
  {
    return BVH::Array<T, N>::Value(myMinPointBuffer, theNodeIndex);
  }

  const BVH_VecNt& MaxPoint(const int theNodeIndex) const
  {
    return BVH::Array<T, N>::Value(myMaxPointBuffer, theNodeIndex);
  }

  int& BegPrimitive(const int theNodeIndex)
  {
    return BVH::Array<int, 4>::ChangeValue(myNodeInfoBuffer, theNodeIndex).y();
  }

  int& EndPrimitive(const int theNodeIndex)
  {
    return BVH::Array<int, 4>::ChangeValue(myNodeInfoBuffer, theNodeIndex).z();
  }

  int BegPrimitive(const int theNodeIndex) const
  {
    return BVH::Array<int, 4>::Value(myNodeInfoBuffer, theNodeIndex).y();
  }

  int EndPrimitive(const int theNodeIndex) const
  {
    return BVH::Array<int, 4>::Value(myNodeInfoBuffer, theNodeIndex).z();
  }

  int NbPrimitives(const int theNodeIndex) const
  {
    return EndPrimitive(theNodeIndex) - BegPrimitive(theNodeIndex) + 1;
  }

  int& Level(const int theNodeIndex)
  {
    return BVH::Array<int, 4>::ChangeValue(myNodeInfoBuffer, theNodeIndex).w();
  }

  int Level(const int theNodeIndex) const
  {
    return BVH::Array<int, 4>::Value(myNodeInfoBuffer, theNodeIndex).w();
  }

  bool IsOuter(const int theNodeIndex) const
  {
    return BVH::Array<int, 4>::Value(myNodeInfoBuffer, theNodeIndex).x() != 0;
  }

public:
  BVH_Array4i& NodeInfoBuffer() { return myNodeInfoBuffer; }

  const BVH_Array4i& NodeInfoBuffer() const { return myNodeInfoBuffer; }

  typename BVH::ArrayType<T, N>::Type& MinPointBuffer() { return myMinPointBuffer; }

  typename BVH::ArrayType<T, N>::Type& MaxPointBuffer() { return myMaxPointBuffer; }

  const typename BVH::ArrayType<T, N>::Type& MinPointBuffer() const { return myMinPointBuffer; }

  const typename BVH::ArrayType<T, N>::Type& MaxPointBuffer() const { return myMaxPointBuffer; }

  void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override
  {
    OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myDepth)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Length())

    for (int aNodeIdx = 0; aNodeIdx < Length(); ++aNodeIdx)
    {
      DumpNode(aNodeIdx, theOStream, theDepth);
    }
  }

  void DumpNode(const int theNodeIndex, Standard_OStream& theOStream, int theDepth) const override
  {
    OCCT_DUMP_CLASS_BEGIN(theOStream, BVH_TreeNode)

    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, theNodeIndex)

    Bnd_Box  aBndBox  = BVH::ToBndBox(MinPoint(theNodeIndex), MaxPoint(theNodeIndex));
    Bnd_Box* aPointer = &aBndBox;
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, aPointer)

    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, BegPrimitive(theNodeIndex))
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, EndPrimitive(theNodeIndex))
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Level(theNodeIndex))
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, IsOuter(theNodeIndex))
  }

public:
  BVH_Array4i myNodeInfoBuffer;

  typename BVH::ArrayType<T, N>::Type myMinPointBuffer;

  typename BVH::ArrayType<T, N>::Type myMaxPointBuffer;

  int myDepth;
};

struct BVH_QuadTree
{
};

struct BVH_BinaryTree
{
};

template <class T, int N, class Arity = BVH_BinaryTree>
class BVH_Tree
{
};
