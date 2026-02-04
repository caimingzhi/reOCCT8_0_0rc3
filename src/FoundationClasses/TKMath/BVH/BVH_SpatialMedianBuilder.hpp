#pragma once


#include <BVH_BinnedBuilder.hpp>
#include <BVH_Box.hpp>

//! Performs building of BVH tree using spatial median split algorithm.
template <class T, int N>
class BVH_SpatialMedianBuilder : public BVH_BinnedBuilder<T, N, 2>
{
public:
  //! Creates spatial median split builder.
  BVH_SpatialMedianBuilder(const int  theLeafNodeSize  = BVH_Constants_LeafNodeSizeDefault,
                           const int  theMaxTreeDepth  = BVH_Constants_MaxTreeDepth,
                           const bool theToUseMainAxis = false)
      : BVH_BinnedBuilder<T, N, 2>(theLeafNodeSize, theMaxTreeDepth, theToUseMainAxis)
  {
  }

  //! Releases resources of spatial median split builder.
  ~BVH_SpatialMedianBuilder() override = default;
};

