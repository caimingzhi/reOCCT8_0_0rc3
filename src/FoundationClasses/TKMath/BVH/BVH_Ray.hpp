#pragma once

#include <BVH_Types.hpp>

#include <limits>

template <class T, int N>
class BVH_Ray
{
public:
  typedef typename BVH::VectorType<T, N>::Type BVH_VecNt;

public:
  BVH_VecNt Origin;
  BVH_VecNt Direct;
  BVH_VecNt InvDirect;

public:
  constexpr BVH_Ray(const BVH_VecNt& theOrigin, const BVH_VecNt& theDirect) noexcept
      : Origin(theOrigin),
        Direct(theDirect),
        InvDirect(computeInvDirect(theDirect))
  {
  }

  constexpr BVH_Ray() noexcept
      : Origin(BVH_VecNt()),
        Direct(BVH_VecNt()),
        InvDirect(BVH_VecNt())
  {
  }

private:
  static constexpr T invComponent(T theDir) noexcept
  {
    return (theDir != T(0)) ? (T(1) / theDir) : std::numeric_limits<T>::infinity();
  }

  static constexpr BVH_VecNt computeInvDirect(const BVH_VecNt& theDirect) noexcept
  {
    static_assert(N >= 1 && N <= 4, "BVH_Ray only supports dimensions 1 to 4");
    if constexpr (N == 1)
    {
      return BVH_VecNt(invComponent(theDirect[0]));
    }
    else if constexpr (N == 2)
    {
      return BVH_VecNt(invComponent(theDirect.x()), invComponent(theDirect.y()));
    }
    else if constexpr (N == 3)
    {
      return BVH_VecNt(invComponent(theDirect.x()),
                       invComponent(theDirect.y()),
                       invComponent(theDirect.z()));
    }
    else
    {
      return BVH_VecNt(invComponent(theDirect.x()),
                       invComponent(theDirect.y()),
                       invComponent(theDirect.z()),
                       invComponent(theDirect.w()));
    }
  }
};
