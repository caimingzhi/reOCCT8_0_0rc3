#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Real.hpp>
class GccInt_Bisec;

class GccAna_CircPnt2dBisec
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GccAna_CircPnt2dBisec(const gp_Circ2d& Circle1, const gp_Pnt2d& Point2);

  Standard_EXPORT GccAna_CircPnt2dBisec(const gp_Circ2d& Circle1,
                                        const gp_Pnt2d&  Point2,
                                        const double     Tolerance);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbSolutions() const;

  Standard_EXPORT occ::handle<GccInt_Bisec> ThisSolution(const int Index) const;

private:
  Standard_EXPORT void DefineSolutions();

  bool      WellDone;
  int       NbrSol;
  gp_Circ2d circle;
  gp_Pnt2d  point;
  int       theposition;
  double    myTolerance;
};
