#pragma once

#include <NCollection_Array1.hpp>

struct PSO_Particle
{
  double* Position;
  double* Velocity;
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

  bool operator<(const PSO_Particle& thePnt) const { return Distance < thePnt.Distance; }
};

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
  NCollection_Array1<double>       myMemory;
  int                              myParticlesCount;
  int                              myDimensionCount;
};
