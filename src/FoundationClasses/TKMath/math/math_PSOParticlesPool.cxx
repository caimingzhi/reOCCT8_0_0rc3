#include <math_PSOParticlesPool.hpp>
#include <algorithm>

//=================================================================================================

math_PSOParticlesPool::math_PSOParticlesPool(const int theParticlesCount,
                                             const int theDimensionCount)
    : myParticlesPool(1, theParticlesCount),
      myMemory(0,
               theParticlesCount
                   * (theDimensionCount    // Position
                      + theDimensionCount  // Velocity
                      + theDimensionCount) // BestPosition
                 - 1)
{
  myParticlesCount = theParticlesCount;
  myDimensionCount = theDimensionCount;
  myMemory.Init(0.);
  // Pointers adjusting.
  int aParIdx, aShiftIdx;
  for (aParIdx = 1; aParIdx <= myParticlesCount; ++aParIdx)
  {
    aShiftIdx                             = (theDimensionCount * 3) * (aParIdx - 1);
    myParticlesPool(aParIdx).Position     = &myMemory(aShiftIdx);
    myParticlesPool(aParIdx).Velocity     = &myMemory(aShiftIdx + theDimensionCount);
    myParticlesPool(aParIdx).BestPosition = &myMemory(aShiftIdx + 2 * theDimensionCount);
  }
}

//=================================================================================================

math_PSOParticlesPool::~math_PSOParticlesPool() = default;

//=================================================================================================

PSO_Particle* math_PSOParticlesPool::GetParticle(const int theIdx)
{
  return &myParticlesPool(theIdx);
}

//=================================================================================================

PSO_Particle* math_PSOParticlesPool::GetBestParticle()
{
  return &*std::min_element(myParticlesPool.begin(), myParticlesPool.end());
}

//=================================================================================================

PSO_Particle* math_PSOParticlesPool::GetWorstParticle()
{
  return &*std::max_element(myParticlesPool.begin(), myParticlesPool.end());
}
