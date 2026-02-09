#pragma once

#include <BVH_Box.hpp>

#include <Standard_Macro.hpp>

class BVH_Properties : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(BVH_Properties, Standard_Transient)
public:
  Standard_EXPORT ~BVH_Properties() override = 0;
};

template <class T, int N>
class BVH_Transform : public BVH_Properties
{
public:
  typedef typename BVH::MatrixType<T, N>::Type BVH_MatNt;

public:
  BVH_Transform() = default;

  BVH_Transform(const BVH_MatNt& theTransform)
      : myTransform(theTransform)
  {
  }

  ~BVH_Transform() override = default;

  const BVH_MatNt& Transform() const { return myTransform; }

  void SetTransform(const BVH_MatNt& theTransform);

  const BVH_MatNt& Inversed() const { return myTransformInversed; }

  BVH_Box<T, N> Apply(const BVH_Box<T, N>& theBox) const;

protected:
  BVH_MatNt myTransform;
  BVH_MatNt myTransformInversed;
};

namespace BVH
{
  template <class T, int N>
  struct MatrixOp
  {
  };

  template <class T>
  struct MatrixOp<T, 4>
  {
    typedef typename BVH::MatrixType<T, 4>::Type BVH_Mat4t;

    static void Inverse(const BVH_Mat4t& theIn, BVH_Mat4t& theOut) { theIn.Inverted(theOut); }

    typedef typename BVH::VectorType<T, 4>::Type BVH_Vec4t;

    static BVH_Vec4t Multiply(const BVH_Mat4t& theMat, const BVH_Vec4t& theVec)
    {
      BVH_Vec4t aOut = theMat * theVec;
      return aOut * static_cast<T>(1.0 / aOut.w());
    }
  };

  template <class T, int N>
  struct UnitVector
  {
  };

  template <class T>
  struct UnitVector<T, 2>
  {
    typedef typename BVH::VectorType<T, 2>::Type BVH_Vec2t;

    static BVH_Vec2t DX() { return BVH_Vec2t(static_cast<T>(1.0), static_cast<T>(0.0)); }

    static BVH_Vec2t DY() { return BVH_Vec2t(static_cast<T>(0.0), static_cast<T>(1.0)); }

    static BVH_Vec2t DZ() { return BVH_Vec2t(static_cast<T>(0.0), static_cast<T>(0.0)); }
  };

  template <class T>
  struct UnitVector<T, 3>
  {
    typedef typename BVH::VectorType<T, 3>::Type BVH_Vec3t;

    static BVH_Vec3t DX()
    {
      return BVH_Vec3t(static_cast<T>(1.0), static_cast<T>(0.0), static_cast<T>(0.0));
    }

    static BVH_Vec3t DY()
    {
      return BVH_Vec3t(static_cast<T>(0.0), static_cast<T>(1.0), static_cast<T>(0.0));
    }

    static BVH_Vec3t DZ()
    {
      return BVH_Vec3t(static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(1.0));
    }
  };

  template <class T>
  struct UnitVector<T, 4>
  {
    typedef typename BVH::VectorType<T, 4>::Type BVH_Vec4t;

    static BVH_Vec4t DX()
    {
      return BVH_Vec4t(static_cast<T>(1.0),
                       static_cast<T>(0.0),
                       static_cast<T>(0.0),
                       static_cast<T>(0.0));
    }

    static BVH_Vec4t DY()
    {
      return BVH_Vec4t(static_cast<T>(0.0),
                       static_cast<T>(1.0),
                       static_cast<T>(0.0),
                       static_cast<T>(0.0));
    }

    static BVH_Vec4t DZ()
    {
      return BVH_Vec4t(static_cast<T>(0.0),
                       static_cast<T>(0.0),
                       static_cast<T>(1.0),
                       static_cast<T>(0.0));
    }
  };
} // namespace BVH

template <class T, int N>
void BVH_Transform<T, N>::SetTransform(const BVH_MatNt& theTransform)
{
  myTransform = theTransform;
  BVH::MatrixOp<T, N>::Inverse(myTransform, myTransformInversed);
}

template <class T, int N>
BVH_Box<T, N> BVH_Transform<T, N>::Apply(const BVH_Box<T, N>& theBox) const
{
  typename BVH_Box<T, N>::BVH_VecNt aSize = theBox.Size();

  BVH_Box<T, N> aBox;
  for (int aX = 0; aX <= 1; ++aX)
  {
    for (int aY = 0; aY <= 1; ++aY)
    {
      for (int aZ = 0; aZ <= 1; ++aZ)
      {
        typename BVH_Box<T, N>::BVH_VecNt aCorner =
          theBox.CornerMin() + BVH::UnitVector<T, N>::DX() * aSize * static_cast<T>(aX)
          + BVH::UnitVector<T, N>::DY() * aSize * static_cast<T>(aY)
          + BVH::UnitVector<T, N>::DZ() * aSize * static_cast<T>(aZ);

        aBox.Add(BVH::MatrixOp<T, N>::Multiply(myTransform, aCorner));
      }
    }
  }

  return aBox;
}
