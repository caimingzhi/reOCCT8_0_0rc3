#pragma once

#include <math_MultipleVarFunction.hpp>
#include <math_Vector.hpp>

class math_PSOParticlesPool;

class math_PSO
{
public:
  Standard_EXPORT math_PSO(math_MultipleVarFunction* theFunc,
                           const math_Vector&        theLowBorder,
                           const math_Vector&        theUppBorder,
                           const math_Vector&        theSteps,
                           const int                 theNbParticles = 32,
                           const int                 theNbIter      = 100);

  Standard_EXPORT void Perform(const math_Vector& theSteps,
                               double&            theValue,
                               math_Vector&       theOutPnt,
                               const int          theNbIter = 100);

  Standard_EXPORT void Perform(math_PSOParticlesPool& theParticles,
                               int                    theNbParticles,
                               double&                theValue,
                               math_Vector&           theOutPnt,
                               const int              theNbIter = 100);

private:
  void performPSOWithGivenParticles(math_PSOParticlesPool& theParticles,
                                    int                    theNbParticles,
                                    double&                theValue,
                                    math_Vector&           theOutPnt,
                                    const int              theNbIter = 100);

  math_MultipleVarFunction* myFunc;
  math_Vector               myLowBorder;
  math_Vector               myUppBorder;
  math_Vector               mySteps;
  int                       myN;
  int                       myNbParticles;
  int                       myNbIter;
};
