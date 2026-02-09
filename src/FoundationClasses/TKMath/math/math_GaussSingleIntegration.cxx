

#define No_Standard_RangeError
#define No_Standard_OutOfRange
#define No_Standard_DimensionError

#include <math.hpp>
#include <math_Function.hpp>
#include <math_GaussSingleIntegration.hpp>
#include <math_Vector.hpp>

math_GaussSingleIntegration::math_GaussSingleIntegration()
    : Done(false)
{
}

math_GaussSingleIntegration::math_GaussSingleIntegration(math_Function& F,
                                                         const double   Lower,
                                                         const double   Upper,
                                                         const int      Order)
{
  int theOrder = std::min(math::GaussPointsMax(), Order);
  Perform(F, Lower, Upper, theOrder);
}

math_GaussSingleIntegration::math_GaussSingleIntegration(math_Function& F,
                                                         const double   Lower,
                                                         const double   Upper,
                                                         const int      Order,
                                                         const double   Tol)
{
  int theOrder = std::min(math::GaussPointsMax(), Order);

  const int IterMax    = 13;
  int       NIter      = 1;
  int       NbInterval = 1;
  double    dU, OldLen, Len;

  Perform(F, Lower, Upper, theOrder);
  Len = Val;
  do
  {
    OldLen = Len;
    Len    = 0.;
    NbInterval *= 2;
    dU = (Upper - Lower) / NbInterval;
    for (int i = 1; i <= NbInterval; i++)
    {
      Perform(F, Lower + (i - 1) * dU, Lower + i * dU, theOrder);
      if (!Done)
        return;
      Len += Val;
    }
    NIter++;
  } while (fabs(OldLen - Len) > Tol && NIter <= IterMax);

  Val = Len;
}

void math_GaussSingleIntegration::Perform(math_Function& F,
                                          const double   Lower,
                                          const double   Upper,
                                          const int      Order)
{
  double      xr, xm, dx;
  int         j;
  double      F1, F2;
  bool        Ok1;
  math_Vector GaussP(1, Order);
  math_Vector GaussW(1, Order);
  Done = false;

  math::GaussPoints(Order, GaussP);
  math::GaussWeights(Order, GaussW);

  xm  = 0.5 * (Upper + Lower);
  xr  = 0.5 * (Upper - Lower);
  Val = 0.;

  int ind = Order / 2, ind1 = (Order + 1) / 2;
  if (ind1 > ind)
  {
    Ok1 = F.Value(xm, Val);
    if (!Ok1)
      return;
    Val *= GaussW(ind1);
  }

  for (j = 1; j <= ind; j++)
  {
    dx  = xr * GaussP(j);
    Ok1 = F.Value(xm - dx, F1);
    if (!Ok1)
      return;
    Ok1 = F.Value(xm + dx, F2);
    if (!Ok1)
      return;

    double FT = F1 + F2;
    Val += GaussW(j) * FT;
  }

  Val *= xr;
  Done = true;
}

void math_GaussSingleIntegration::Dump(Standard_OStream& o) const
{

  o << "math_GaussSingleIntegration ";
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
