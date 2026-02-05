#pragma once

#include <vector>
#include <NCollection_OccAllocator.hpp>

// Defines a dynamic vector of work data.

struct IntWalk_WalkingData
{
  double ustart;
  double vstart;
  int    etat;
};

typedef std::vector<IntWalk_WalkingData, NCollection_OccAllocator<IntWalk_WalkingData>>
  IntWalk_VectorOfWalkingData;
