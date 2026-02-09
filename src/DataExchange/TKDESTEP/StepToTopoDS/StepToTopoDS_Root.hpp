#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class StepToTopoDS_Root
{
public:
  DEFINE_STANDARD_ALLOC

  bool IsDone() const;

  double Precision() const;

  void SetPrecision(const double preci);

  double MaxTol() const;

  void SetMaxTol(const double maxpreci);

protected:
  Standard_EXPORT StepToTopoDS_Root();

  bool done;

private:
  double myPrecision;
  double myMaxTol;
};

#include <StepToTopoDS_Root.hpp>

inline bool StepToTopoDS_Root::IsDone() const
{
  return done;
}

inline double StepToTopoDS_Root::Precision() const
{
  return myPrecision;
}

inline void StepToTopoDS_Root::SetPrecision(const double preci)
{
  myPrecision = preci;
}

inline double StepToTopoDS_Root::MaxTol() const
{
  return myMaxTol;
}

inline void StepToTopoDS_Root::SetMaxTol(const double maxpreci)
{
  myMaxTol = maxpreci;
}
