#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Lin2d.hpp>
class GccInt_Bisec;

class GccAna_CircLin2dBisec
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GccAna_CircLin2dBisec(const gp_Circ2d& Circle, const gp_Lin2d& Line);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbSolutions() const;

  Standard_EXPORT occ::handle<GccInt_Bisec> ThisSolution(const int Index) const;

private:
  bool      WellDone;
  int       NbrSol;
  gp_Circ2d circle;
  gp_Lin2d  line;
};
