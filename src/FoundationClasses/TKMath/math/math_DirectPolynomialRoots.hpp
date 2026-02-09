#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_RangeError.hpp>
#include <StdFail_InfiniteSolutions.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>

class math_DirectPolynomialRoots
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_DirectPolynomialRoots(const double theA,
                                             const double theB,
                                             const double theC,
                                             const double theD,
                                             const double theE);

  Standard_EXPORT math_DirectPolynomialRoots(const double theA,
                                             const double theB,
                                             const double theC,
                                             const double theD);

  Standard_EXPORT math_DirectPolynomialRoots(const double theA,
                                             const double theB,
                                             const double theC);

  Standard_EXPORT math_DirectPolynomialRoots(const double theA, const double theB);

  bool IsDone() const;

  bool InfiniteRoots() const;

  int NbSolutions() const;

  double Value(const int theIndex) const;

  Standard_EXPORT void Dump(Standard_OStream& theStream) const;

protected:
  Standard_EXPORT void Solve(const double theA,
                             const double theB,
                             const double theC,
                             const double theD,
                             const double theE);

  Standard_EXPORT void Solve(const double theA,
                             const double theB,
                             const double theC,
                             const double theD);

  Standard_EXPORT void Solve(const double theA, const double theB, const double theC);

  Standard_EXPORT void Solve(const double theA, const double theB);

private:
  bool   myDone;
  bool   myInfiniteStatus;
  int    myNbSol;
  double myRoots[4];
};

inline bool math_DirectPolynomialRoots::IsDone() const
{
  return myDone;
}

inline bool math_DirectPolynomialRoots::InfiniteRoots() const
{
  return myInfiniteStatus;
}

inline int math_DirectPolynomialRoots::NbSolutions() const
{
  StdFail_InfiniteSolutions_Raise_if(myInfiniteStatus, " ");
  return myNbSol;
}

inline double math_DirectPolynomialRoots::Value(const int theIndex) const
{
  StdFail_InfiniteSolutions_Raise_if(myInfiniteStatus, " ");
  Standard_RangeError_Raise_if((theIndex < 1) || (theIndex > myNbSol), " ");
  return myRoots[theIndex - 1];
}

inline Standard_OStream& operator<<(Standard_OStream&                 theStream,
                                    const math_DirectPolynomialRoots& theRoots)
{
  theRoots.Dump(theStream);
  return theStream;
}
