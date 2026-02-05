#pragma once

#include <NCollection_Array1.hpp>

//! Describes particle pool for using in PSO algorithm.
//! Indexes:
//! 0 <= aDimidx <= myDimensionCount - 1
struct PSO_Particle
{
  double* Position; // Data for pointers allocated within PSOParticlesPool instance.
  double* Velocity; // Not need to delete it manually.
  double* BestPosition;
  double  Distance;
  double  BestDistance;

  PSO_Particle()
  {
    Distance     = RealLast();
    BestDistance = RealLast();
    Position     = nullptr;
    Velocity     = nullptr;
    BestPosition = nullptr;
  }

  //! Compares the particles according to their distances.
  bool operator<(const PSO_Particle& thePnt) const { return Distance < thePnt.Distance; }
};

// Indexes:
// 1 <= aParticleIdx <= myParticlesCount
class math_PSOParticlesPool
{
public:
  Standard_EXPORT math_PSOParticlesPool(const int theParticlesCount, const int theDimensionCount);

  Standard_EXPORT PSO_Particle* GetParticle(const int theIdx);

  Standard_EXPORT PSO_Particle* GetBestParticle();

  Standard_EXPORT PSO_Particle* GetWorstParticle();

  Standard_EXPORT ~math_PSOParticlesPool();

private:
  NCollection_Array1<PSO_Particle> myParticlesPool;
  NCollection_Array1<double>       myMemory; // Stores particles vector data.
  int                              myParticlesCount;
  int                              myDimensionCount;
};
