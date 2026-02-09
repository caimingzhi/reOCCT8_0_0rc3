#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <gp_Circ2d.hpp>
class GccInt_Bisec;

class GccAna_Circ2dBisec
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GccAna_Circ2dBisec(const gp_Circ2d& Circ1, const gp_Circ2d& Circ2);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbSolutions() const;

  Standard_EXPORT occ::handle<GccInt_Bisec> ThisSolution(const int Index) const;

private:
  bool      WellDone;
  int       NbrSol;
  int       intersection;
  bool      sameradius;
  gp_Circ2d circle1;
  gp_Circ2d circle2;
};
