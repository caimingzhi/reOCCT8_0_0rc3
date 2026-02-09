#pragma once

#ifndef _BVH_Constants_Header
  #define _BVH_Constants_Header

enum
{

  BVH_Constants_MaxTreeDepth = 32,

  BVH_Constants_LeafNodeSizeSingle = 1,

  BVH_Constants_LeafNodeSizeAverage = 4,

  BVH_Constants_LeafNodeSizeDefault = 5,

  BVH_Constants_LeafNodeSizeSmall = 8,

  BVH_Constants_NbBinsOptimal = 32,

  BVH_Constants_NbBinsBest = 48,
};

namespace BVH
{

  constexpr double THE_NODE_MIN_SIZE = 1e-5;
}

#endif

#include <BVH_Types.hpp>
#include <Standard_Macro.hpp>
#include <Standard_Dump.hpp>
#include <Standard_ShortReal.hpp>

#include <limits>

template <class T, int N, template <class, int> class TheDerivedBox>
class BVH_BaseBox
{
};

template <class T, int N>
class BVH_Box;

template <class T>
class BVH_BaseBox<T, 3, BVH_Box>
{
public:
  void Transform(const NCollection_Mat4<T>& theTransform)
  {
    if (theTransform.IsIdentity())
    {
      return;
    }

    BVH_Box<T, 3>* aThis = static_cast<BVH_Box<T, 3>*>(this);
    if (!aThis->IsValid())
    {
      return;
    }

    BVH_Box<T, 3> aBox = Transformed(theTransform);

    aThis->CornerMin() = aBox.CornerMin();
    aThis->CornerMax() = aBox.CornerMax();
  }

  BVH_Box<T, 3> Transformed(const NCollection_Mat4<T>& theTransform) const
  {
    using BVH_VecNt = typename BVH_Box<T, 3>::BVH_VecNt;

    const BVH_Box<T, 3>* aThis = static_cast<const BVH_Box<T, 3>*>(this);
    if (theTransform.IsIdentity())
    {
      return *aThis;
    }

    if (!aThis->IsValid())
    {
      return *aThis;
    }

    const BVH_VecNt& anOldMinPnt = aThis->CornerMin();
    const BVH_VecNt& anOldMaxPnt = aThis->CornerMax();

    const typename BVH::VectorType<T, 4>::Type aTranslation = theTransform.GetColumn(3);
    BVH_VecNt aNewMinPnt = BVH_VecNt(aTranslation.x(), aTranslation.y(), aTranslation.z());
    BVH_VecNt aNewMaxPnt = BVH_VecNt(aTranslation.x(), aTranslation.y(), aTranslation.z());

    for (int aCol = 0; aCol < 3; ++aCol)
    {
      for (int aRow = 0; aRow < 3; ++aRow)
      {
        const T aMatValue = theTransform.GetValue(aRow, aCol);
        const T anOffset1 = aMatValue * anOldMinPnt.GetData()[aCol];
        const T anOffset2 = aMatValue * anOldMaxPnt.GetData()[aCol];

        aNewMinPnt.ChangeData()[aRow] += (std::min)(anOffset1, anOffset2);
        aNewMaxPnt.ChangeData()[aRow] += (std::max)(anOffset1, anOffset2);
      }
    }

    return BVH_Box<T, 3>(aNewMinPnt, aNewMaxPnt);
  }
};

template <class T, int N>
class BVH_Box : public BVH_BaseBox<T, N, BVH_Box>
{
public:
  typedef typename BVH::VectorType<T, N>::Type BVH_VecNt;

private:
  static constexpr T minSentinel() noexcept { return (std::numeric_limits<T>::max)(); }

  static constexpr T maxSentinel() noexcept { return (std::numeric_limits<T>::lowest)(); }

public:
  constexpr BVH_Box() noexcept
      : myMinPoint(BVH_VecNt(minSentinel())),
        myMaxPoint(BVH_VecNt(maxSentinel()))
  {
  }

  constexpr BVH_Box(const BVH_VecNt& thePoint) noexcept
      : myMinPoint(thePoint),
        myMaxPoint(thePoint)
  {
  }

  constexpr BVH_Box(const BVH_VecNt& theMinPoint, const BVH_VecNt& theMaxPoint) noexcept
      : myMinPoint(theMinPoint),
        myMaxPoint(theMaxPoint)
  {
  }

public:
  constexpr void Clear() noexcept
  {
    myMinPoint = BVH_VecNt(minSentinel());
    myMaxPoint = BVH_VecNt(maxSentinel());
  }

  constexpr bool IsValid() const noexcept { return myMinPoint[0] <= myMaxPoint[0]; }

  void Add(const BVH_VecNt& thePoint);

  void Combine(const BVH_Box& theBox);

  constexpr const BVH_VecNt& CornerMin() const noexcept { return myMinPoint; }

  constexpr const BVH_VecNt& CornerMax() const noexcept { return myMaxPoint; }

  constexpr BVH_VecNt& CornerMin() noexcept { return myMinPoint; }

  constexpr BVH_VecNt& CornerMax() noexcept { return myMaxPoint; }

  T Area() const;

  constexpr BVH_VecNt Size() const { return myMaxPoint - myMinPoint; }

  constexpr BVH_VecNt Center() const { return (myMinPoint + myMaxPoint) * static_cast<T>(0.5); }

  inline T Center(const int theAxis) const;

  void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const
  {
    (void)theDepth;
    const int anIsValid = IsValid() ? 1 : 0;
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, anIsValid)

    constexpr int n = (N < 3) ? N : 3;
    if constexpr (n == 1)
    {
      OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myMinPoint[0])
      OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myMaxPoint[0])
    }
    else if constexpr (n == 2)
    {
      OCCT_DUMP_FIELD_VALUES_NUMERICAL(theOStream, "MinPoint", n, myMinPoint[0], myMinPoint[1])
      OCCT_DUMP_FIELD_VALUES_NUMERICAL(theOStream, "MaxPoint", n, myMaxPoint[0], myMaxPoint[1])
    }
    else if constexpr (n == 3)
    {
      OCCT_DUMP_FIELD_VALUES_NUMERICAL(theOStream,
                                       "MinPoint",
                                       n,
                                       myMinPoint[0],
                                       myMinPoint[1],
                                       myMinPoint[2])
      OCCT_DUMP_FIELD_VALUES_NUMERICAL(theOStream,
                                       "MaxPoint",
                                       n,
                                       myMaxPoint[0],
                                       myMaxPoint[1],
                                       myMaxPoint[2])
    }
  }

  bool InitFromJson(const Standard_SStream& theSStream, int& theStreamPos)
  {
    int aPos = theStreamPos;

    int                     anIsValid  = 0;
    TCollection_AsciiString aStreamStr = Standard_Dump::Text(theSStream);

    OCCT_INIT_FIELD_VALUE_INTEGER(aStreamStr, aPos, anIsValid);

    if (anIsValid == 0)
    {
      Clear();
      theStreamPos = aPos;
      return true;
    }

    constexpr int n = (N < 3) ? N : 3;
    if constexpr (n == 1)
    {
      double aMinValue, aMaxValue;
      OCCT_INIT_FIELD_VALUE_REAL(aStreamStr, aPos, aMinValue);
      OCCT_INIT_FIELD_VALUE_REAL(aStreamStr, aPos, aMaxValue);
      myMinPoint[0] = (T)aMinValue;
      myMaxPoint[0] = (T)aMaxValue;
    }
    else if constexpr (n == 2)
    {
      double aValue1, aValue2;
      OCCT_INIT_VECTOR_CLASS(aStreamStr, "MinPoint", aPos, n, &aValue1, &aValue2);
      myMinPoint[0] = (T)aValue1;
      myMinPoint[1] = (T)aValue2;

      OCCT_INIT_VECTOR_CLASS(aStreamStr, "MaxPoint", aPos, n, &aValue1, &aValue2);
      myMaxPoint[0] = (T)aValue1;
      myMaxPoint[1] = (T)aValue2;
    }
    else if constexpr (n == 3)
    {
      double aValue1, aValue2, aValue3;
      OCCT_INIT_VECTOR_CLASS(aStreamStr, "MinPoint", aPos, n, &aValue1, &aValue2, &aValue3);
      myMinPoint[0] = (T)aValue1;
      myMinPoint[1] = (T)aValue2;
      myMinPoint[2] = (T)aValue3;

      OCCT_INIT_VECTOR_CLASS(aStreamStr, "MaxPoint", aPos, n, &aValue1, &aValue2, &aValue3);
      myMaxPoint[0] = (T)aValue1;
      myMaxPoint[1] = (T)aValue2;
      myMaxPoint[2] = (T)aValue3;
    }

    for (int i = n; i < N; ++i)
    {
      myMinPoint[i] = (std::numeric_limits<T>::lowest)();
      myMaxPoint[i] = (std::numeric_limits<T>::max)();
    }

    theStreamPos = aPos;
    return true;
  }

public:
  constexpr bool IsOut(const BVH_Box<T, N>& theOther) const
  {
    if (!theOther.IsValid())
      return true;

    return IsOut(theOther.myMinPoint, theOther.myMaxPoint);
  }

  constexpr bool IsOut(const BVH_VecNt& theMinPoint, const BVH_VecNt& theMaxPoint) const
  {
    if (!IsValid())
      return true;

    for (int i = 0; i < N; ++i)
    {
      if (myMinPoint[i] > theMaxPoint[i] || myMaxPoint[i] < theMinPoint[i])
        return true;
    }
    return false;
  }

  constexpr bool Contains(const BVH_Box<T, N>& theOther, bool& hasOverlap) const
  {
    hasOverlap = false;
    if (!theOther.IsValid())
      return false;

    return Contains(theOther.myMinPoint, theOther.myMaxPoint, hasOverlap);
  }

  constexpr bool Contains(const BVH_VecNt& theMinPoint,
                          const BVH_VecNt& theMaxPoint,
                          bool&            hasOverlap) const
  {
    hasOverlap = false;
    if (!IsValid())
      return false;

    bool isInside = true;
    for (int i = 0; i < N; ++i)
    {
      hasOverlap = (myMinPoint[i] <= theMaxPoint[i] && myMaxPoint[i] >= theMinPoint[i]);
      if (!hasOverlap)
        return false;
      isInside = isInside && (myMinPoint[i] <= theMinPoint[i] && myMaxPoint[i] >= theMaxPoint[i]);
    }
    return isInside;
  }

  constexpr bool IsOut(const BVH_VecNt& thePoint) const
  {
    if (!IsValid())
      return true;

    for (int i = 0; i < N; ++i)
    {
      if (thePoint[i] < myMinPoint[i] || thePoint[i] > myMaxPoint[i])
        return true;
    }
    return false;
  }

protected:
  BVH_VecNt myMinPoint;
  BVH_VecNt myMaxPoint;
};

namespace BVH
{

  template <class T, int N>
  struct CenterAxis
  {

    static inline T Center(const BVH_Box<T, N>& theBox, const int theAxis)
    {
      return (theBox.CornerMin()[theAxis] + theBox.CornerMax()[theAxis]) * static_cast<T>(0.5);
    }
  };

  template <class T, int N>
  struct SurfaceCalculator
  {
    static inline T Area(const typename BVH_Box<T, N>::BVH_VecNt& theSize)
    {
      if constexpr (N == 1)
      {

        return std::abs(theSize[0]);
      }
      else if constexpr (N == 2)
      {
        const T anArea = std::abs(theSize.x() * theSize.y());
        if (anArea < std::numeric_limits<T>::epsilon())
        {
          return std::abs(theSize.x()) + std::abs(theSize.y());
        }
        return anArea;
      }
      else
      {

        const T anArea = (std::abs(theSize.x() * theSize.y()) + std::abs(theSize.x() * theSize.z())
                          + std::abs(theSize.z() * theSize.y()))
                         * static_cast<T>(2.0);
        if (anArea < std::numeric_limits<T>::epsilon())
        {
          return std::abs(theSize.x()) + std::abs(theSize.y()) + std::abs(theSize.z());
        }
        return anArea;
      }
    }
  };

  template <class T, int N>
  struct BoxMinMax
  {
    typedef typename BVH::VectorType<T, N>::Type BVH_VecNt;

    static inline void CwiseMin(BVH_VecNt& theVec1, const BVH_VecNt& theVec2)
    {
      for (int i = 0; i < N; ++i)
      {
        theVec1[i] = (std::min)(theVec1[i], theVec2[i]);
      }
    }

    static inline void CwiseMax(BVH_VecNt& theVec1, const BVH_VecNt& theVec2)
    {
      for (int i = 0; i < N; ++i)
      {
        theVec1[i] = (std::max)(theVec1[i], theVec2[i]);
      }
    }
  };
} // namespace BVH

template <class T, int N>
void BVH_Box<T, N>::Add(const BVH_VecNt& thePoint)
{
  BVH::BoxMinMax<T, N>::CwiseMin(myMinPoint, thePoint);
  BVH::BoxMinMax<T, N>::CwiseMax(myMaxPoint, thePoint);
}

template <class T, int N>
void BVH_Box<T, N>::Combine(const BVH_Box& theBox)
{
  if (theBox.IsValid())
  {
    BVH::BoxMinMax<T, N>::CwiseMin(myMinPoint, theBox.myMinPoint);
    BVH::BoxMinMax<T, N>::CwiseMax(myMaxPoint, theBox.myMaxPoint);
  }
}

template <class T, int N>
T BVH_Box<T, N>::Area() const
{
  return !IsValid() ? static_cast<T>(0.0)
                    : BVH::SurfaceCalculator<T, N>::Area(myMaxPoint - myMinPoint);
}

template <class T, int N>
T BVH_Box<T, N>::Center(const int theAxis) const
{
  return BVH::CenterAxis<T, N>::Center(*this, theAxis);
}
