#pragma once

#include <BVH_BinnedBuilder.hpp>
#include <BVH_Box.hpp>

template <class T, int N>
class BVH_SpatialMedianBuilder : public BVH_BinnedBuilder<T, N, 2>
{
public:
  BVH_SpatialMedianBuilder(const int  theLeafNodeSize  = BVH_Constants_LeafNodeSizeDefault,
                           const int  theMaxTreeDepth  = BVH_Constants_MaxTreeDepth,
                           const bool theToUseMainAxis = false)
      : BVH_BinnedBuilder<T, N, 2>(theLeafNodeSize, theMaxTreeDepth, theToUseMainAxis)
  {
  }

  ~BVH_SpatialMedianBuilder() override = default;
};
