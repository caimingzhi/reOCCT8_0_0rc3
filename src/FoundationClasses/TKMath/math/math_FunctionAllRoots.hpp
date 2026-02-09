#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
class math_FunctionWithDerivative;
class math_FunctionSample;

class math_FunctionAllRoots
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_FunctionAllRoots(math_FunctionWithDerivative& F,
                                        const math_FunctionSample&   S,
                                        const double                 EpsX,
                                        const double                 EpsF,
                                        const double                 EpsNul);

  bool IsDone() const;

  int NbIntervals() const;

  void GetInterval(const int Index, double& A, double& B) const;

  void GetIntervalState(const int Index, int& IFirst, int& ILast) const;

  int NbPoints() const;

  double GetPoint(const int Index) const;

  int GetPointState(const int Index) const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  bool                         done;
  NCollection_Sequence<double> pdeb;
  NCollection_Sequence<double> pfin;
  NCollection_Sequence<double> piso;
  NCollection_Sequence<int>    ideb;
  NCollection_Sequence<int>    ifin;
  NCollection_Sequence<int>    iiso;
};

#include <StdFail_NotDone.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>

inline bool math_FunctionAllRoots::IsDone() const
{
  return done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_FunctionAllRoots& F)
{
  F.Dump(o);
  return o;
}

inline int math_FunctionAllRoots::NbIntervals() const
{
  StdFail_NotDone_Raise_if(!done, " ");
  return pdeb.Length();
}

inline void math_FunctionAllRoots::GetInterval(const int Index, double& A, double& B) const
{
  StdFail_NotDone_Raise_if(!done, " ");
  A = pdeb.Value(Index);
  B = pfin.Value(Index);
}

inline void math_FunctionAllRoots::GetIntervalState(const int Index, int& IFirst, int& ILast) const
{
  StdFail_NotDone_Raise_if(!done, " ");
  IFirst = ideb.Value(Index);
  ILast  = ifin.Value(Index);
}

inline int math_FunctionAllRoots::NbPoints() const
{
  StdFail_NotDone_Raise_if(!done, " ");
  return piso.Length();
}

inline double math_FunctionAllRoots::GetPoint(const int Index) const
{
  StdFail_NotDone_Raise_if(!done, " ");
  return piso.Value(Index);
}

inline int math_FunctionAllRoots::GetPointState(const int Index) const
{
  StdFail_NotDone_Raise_if(!done, " ");
  return iiso.Value(Index);
}
