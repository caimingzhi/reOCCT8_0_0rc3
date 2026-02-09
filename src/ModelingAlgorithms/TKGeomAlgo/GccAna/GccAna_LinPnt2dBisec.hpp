#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
class GccInt_Bisec;
class gp_Lin2d;
class gp_Pnt2d;

class GccAna_LinPnt2dBisec
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GccAna_LinPnt2dBisec(const gp_Lin2d& Line1, const gp_Pnt2d& Point2);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT occ::handle<GccInt_Bisec> ThisSolution() const;

private:
  bool                      WellDone;
  occ::handle<GccInt_Bisec> bissol;
};
