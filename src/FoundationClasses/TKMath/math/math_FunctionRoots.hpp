#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
class math_FunctionWithDerivative;

class math_FunctionRoots
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_FunctionRoots(math_FunctionWithDerivative& F,
                                     const double                 A,
                                     const double                 B,
                                     const int                    NbSample,
                                     const double                 EpsX    = 0.0,
                                     const double                 EpsF    = 0.0,
                                     const double                 EpsNull = 0.0,
                                     const double                 K       = 0.0);

  bool IsDone() const;

  bool IsAllNull() const;

  int NbSolutions() const;

  double Value(const int Nieme) const;

  int StateNumber(const int Nieme) const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  bool                         Done;
  bool                         AllNull;
  NCollection_Sequence<double> Sol;
  NCollection_Sequence<int>    NbStateSol;
};

#include <StdFail_NotDone.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>

inline bool math_FunctionRoots::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_FunctionRoots& F)
{
  F.Dump(o);
  return o;
}

inline bool math_FunctionRoots::IsAllNull() const
{

  StdFail_NotDone_Raise_if(!Done, " ");
  return AllNull;
}

inline int math_FunctionRoots::NbSolutions() const
{

  StdFail_NotDone_Raise_if(!Done, " ");
  return Sol.Length();
}

inline double math_FunctionRoots::Value(const int Nieme) const
{

  StdFail_NotDone_Raise_if(!Done, " ");
  return Sol.Value(Nieme);
}

inline int math_FunctionRoots::StateNumber(const int Nieme) const
{

  StdFail_NotDone_Raise_if(!Done, " ");
  return NbStateSol.Value(Nieme);
}
