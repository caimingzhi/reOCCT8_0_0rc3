

#define No_Standard_RangeError
#define No_Standard_OutOfRange
#define No_Standard_DimensionError

#include <math.hpp>
#include <math_GaussMultipleIntegration.hpp>
#include <math_IntegerVector.hpp>
#include <math_Matrix.hpp>
#include <math_MultipleVarFunction.hpp>
#include <math_Vector.hpp>

class IntegrationFunction
{

  math_MultipleVarFunction* Fsav;
  math_IntegerVector        Ordsav;
  int                       NVarsav;
  math_Vector               xr;
  math_Vector               xm;
  math_Matrix               GaussPoint;
  math_Matrix               GaussWeight;
  double                    Val;
  bool                      Done;

public:
  IntegrationFunction(math_MultipleVarFunction& F,
                      const int                 maxsav,
                      const int                 NVar,
                      const math_IntegerVector& Ord,
                      const math_Vector&        Lowsav,
                      const math_Vector&        Uppsav);

  double Value();
  bool   IsDone() const;
  bool   recursive_iteration(int& n, math_IntegerVector& inc);
};

IntegrationFunction::IntegrationFunction(math_MultipleVarFunction& F,
                                         const int                 maxsav,
                                         const int                 NVar,
                                         const math_IntegerVector& Ord,
                                         const math_Vector&        Lowsav,
                                         const math_Vector&        Uppsav)
    : Ordsav(1, NVar),
      xr(1, NVar),
      xm(1, NVar),
      GaussPoint(1, NVar, 1, maxsav),
      GaussWeight(1, NVar, 1, maxsav)
{

  int                i, k;
  math_IntegerVector inc(1, NVar);
  inc.Init(0);
  Fsav    = &F;
  NVarsav = NVar;
  Ordsav  = Ord;
  Done    = false;

  for (i = 1; i <= NVarsav; i++)
  {
    xm(i) = 0.5 * (Lowsav(i) + Uppsav(i));
    xr(i) = 0.5 * (Uppsav(i) - Lowsav(i));
    math_Vector GP(1, Ordsav(i)), GW(1, Ordsav(i));
    math::GaussPoints(Ordsav(i), GP);
    math::GaussWeights(Ordsav(i), GW);
    for (k = 1; k <= Ordsav(i); k++)
    {
      GaussPoint(i, k)  = GP(k);
      GaussWeight(i, k) = GW(k);
    }
  }
  Val          = 0.0;
  int  Iterdeb = 1;
  bool recur   = recursive_iteration(Iterdeb, inc);
  if (recur)
  {

    for (i = 1; i <= NVarsav; i++)
    {
      Val *= xr(i);
    }
    Done = true;
  }
}

double IntegrationFunction::Value()
{
  return Val;
}

bool IntegrationFunction::IsDone() const
{
  return Done;
}

bool IntegrationFunction::recursive_iteration(int& n, math_IntegerVector& inc)
{

  int local;
  if (n == (NVarsav + 1))
  {
    math_Vector dx(1, NVarsav);
    int         j;
    for (j = 1; j <= NVarsav; j++)
    {
      dx(j) = xr(j) * GaussPoint(j, inc(j));
    }
    double F1;
    bool   Ok = Fsav->Value(xm + dx, F1);
    if (!Ok)
    {
      return false;
    };
    double Interm = 1;
    for (j = 1; j <= NVarsav; j++)
    {
      Interm *= GaussWeight(j, inc(j));
    }
    Val += Interm * F1;
    return true;
  }

  bool OK = false;
  for (inc(n) = 1; inc(n) <= Ordsav(n); inc(n)++)
  {
    local = n + 1;
    OK    = recursive_iteration(local, inc);
  }
  return OK;
}

math_GaussMultipleIntegration::math_GaussMultipleIntegration(math_MultipleVarFunction& F,
                                                             const math_Vector&        Lower,
                                                             const math_Vector&        Upper,
                                                             const math_IntegerVector& Order)
{
  int MaxOrder = math::GaussPointsMax();

  int                i, max = 0;
  int                NVar = F.NbVariables();
  math_IntegerVector Ord(1, NVar);
  math_Vector        Lowsav(1, NVar);
  math_Vector        Uppsav(1, NVar);
  Lowsav = Lower;
  Uppsav = Upper;

  Done = false;
  for (i = 1; i <= NVar; i++)
  {
    if (Order(i) > MaxOrder)
    {
      Ord(i) = MaxOrder;
    }
    else
    {
      Ord(i) = Order(i);
    }
    if (Ord(i) >= max)
    {
      max = Ord(i);
    }
  }

  IntegrationFunction Func(F, max, NVar, Ord, Lowsav, Uppsav);
  if (Func.IsDone())
  {
    Val  = Func.Value();
    Done = true;
  }
}

void math_GaussMultipleIntegration::Dump(Standard_OStream& o) const
{

  o << "math_GaussMultipleIntegration ";
  if (Done)
  {
    o << " Status = Done \n";
    o << " Integration value = " << Val << "\n";
  }
  else
  {
    o << "Status = not Done \n";
  }
}
