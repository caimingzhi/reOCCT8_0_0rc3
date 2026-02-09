#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Lin2d.hpp>
class gp_Pnt2d;

class GccAna_Pnt2dBisec
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GccAna_Pnt2dBisec(const gp_Pnt2d& Point1, const gp_Pnt2d& Point2);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool HasSolution() const;

  Standard_EXPORT gp_Lin2d ThisSolution() const;

private:
  bool     WellDone;
  bool     HasSol;
  gp_Lin2d linsol;
};
