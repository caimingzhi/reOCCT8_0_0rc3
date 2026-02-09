

#define No_Standard_RangeError
#define No_Standard_OutOfRange
#define No_Standard_DimensionError

#include <math.hpp>
#include <math_FunctionSet.hpp>
#include <math_GaussSetIntegration.hpp>
#include <math_Vector.hpp>
#include <Standard_NotImplemented.hpp>
#include <StdFail_NotDone.hpp>

math_GaussSetIntegration::math_GaussSetIntegration(math_FunctionSet&         F,
                                                   const math_Vector&        Lower,
                                                   const math_Vector&        Upper,
                                                   const math_IntegerVector& Order)
    : Val(1, F.NbEquations())
{

  int         NbEqua = F.NbEquations(), NbVar = F.NbVariables();
  int         i;
  bool        IsOk;
  math_Vector FVal1(1, NbEqua), FVal2(1, NbEqua), Tval(1, NbVar);

  Standard_NotImplemented_Raise_if(NbVar != 1
                                     || Order.Value(Order.Lower()) > math::GaussPointsMax(),
                                   "GaussSetIntegration ");

  Done = false;

  double      Xdeb  = Lower.Value(Lower.Lower());
  double      Xfin  = Upper.Value(Upper.Lower());
  int         Ordre = Order.Value(Order.Lower());
  double      Xm, Xr;
  math_Vector GaussP(1, Ordre), GaussW(1, Ordre);

  math::GaussPoints(Ordre, GaussP);
  math::GaussWeights(Ordre, GaussW);

  Xm = 0.5 * (Xdeb + Xfin);
  Xr = 0.5 * (Xfin - Xdeb);

  int ind = Ordre / 2, ind1 = (Ordre + 1) / 2;
  if (ind1 > ind)
  {
    Tval(1) = Xm;
    IsOk    = F.Value(Tval, Val);
    if (!IsOk)
      return;
    Val *= GaussW(ind1);
  }
  else
  {
    Val.Init(0);
  }

  for (i = 1; i <= ind; i++)
  {
    Tval(1) = Xm + Xr * GaussP(i);
    IsOk    = F.Value(Tval, FVal1);
    if (!IsOk)
      return;
    Tval(1) = Xm - Xr * GaussP(i);
    IsOk    = F.Value(Tval, FVal2);
    if (!IsOk)
      return;
    FVal1 += FVal2;
    FVal1 *= GaussW(i);
    Val += FVal1;
  }
  Val *= Xr;

  Done = true;
}

void math_GaussSetIntegration::Dump(Standard_OStream& o) const
{
  o << "math_GaussSetIntegration ";
  if (Done)
  {
    o << " Status = Done \n";
    o << "Integration Value = " << Val << "\n";
  }
  else
  {
    o << "Status = not Done \n";
  }
}
