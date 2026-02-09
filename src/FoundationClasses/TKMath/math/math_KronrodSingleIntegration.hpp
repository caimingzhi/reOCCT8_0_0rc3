#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <math_Vector.hpp>
class math_Function;

class math_KronrodSingleIntegration
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_KronrodSingleIntegration();

  Standard_EXPORT math_KronrodSingleIntegration(math_Function& theFunction,
                                                const double   theLower,
                                                const double   theUpper,
                                                const int      theNbPnts);

  Standard_EXPORT math_KronrodSingleIntegration(math_Function& theFunction,
                                                const double   theLower,
                                                const double   theUpper,
                                                const int      theNbPnts,
                                                const double   theTolerance,
                                                const int      theMaxNbIter);

  Standard_EXPORT void Perform(math_Function& theFunction,
                               const double   theLower,
                               const double   theUpper,
                               const int      theNbPnts);

  Standard_EXPORT void Perform(math_Function& theFunction,
                               const double   theLower,
                               const double   theUpper,
                               const int      theNbPnts,
                               const double   theTolerance,
                               const int      theMaxNbIter);

  bool IsDone() const;

  double Value() const;

  double ErrorReached() const;

  double AbsolutError() const;

  int OrderReached() const;

  int NbIterReached() const;

  Standard_EXPORT static bool GKRule(math_Function&     theFunction,
                                     const double       theLower,
                                     const double       theUpper,
                                     const math_Vector& theGaussP,
                                     const math_Vector& theGaussW,
                                     const math_Vector& theKronrodP,
                                     const math_Vector& theKronrodW,
                                     double&            theValue,
                                     double&            theError);

private:
  bool   myIsDone;
  double myValue;
  double myErrorReached;
  double myAbsolutError;
  int    myNbPntsReached;
  int    myNbIterReached;
};

#include <StdFail_NotDone.hpp>

inline bool math_KronrodSingleIntegration::IsDone() const
{
  return myIsDone;
}

inline double math_KronrodSingleIntegration::Value() const
{
  StdFail_NotDone_Raise_if(!myIsDone, "math_KronrodSingleIntegration");
  return myValue;
}

inline double math_KronrodSingleIntegration::ErrorReached() const
{
  StdFail_NotDone_Raise_if(!myIsDone, "math_KronrodSingleIntegration");
  return myErrorReached;
}

inline double math_KronrodSingleIntegration::AbsolutError() const
{
  StdFail_NotDone_Raise_if(!myIsDone, "math_KronrodSingleIntegration");
  return myAbsolutError;
}

inline int math_KronrodSingleIntegration::OrderReached() const
{
  StdFail_NotDone_Raise_if(!myIsDone, "math_KronrodSingleIntegration");
  return myNbPntsReached;
}

inline int math_KronrodSingleIntegration::NbIterReached() const
{
  StdFail_NotDone_Raise_if(!myIsDone, "math_KronrodSingleIntegration");
  return myNbIterReached;
}
